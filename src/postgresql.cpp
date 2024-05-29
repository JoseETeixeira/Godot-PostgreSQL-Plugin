#include "postgresql.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

PostgreSQL::PostgreSQL()
{
    conn = nullptr;
}

PostgreSQL::~PostgreSQL()
{
    close_db();
}

void PostgreSQL::connect_db(const String &host, int port, const String &dbname, const String &user, const String &password)
{
    String conninfo = "host=" + host + " port=" + itos(port) + " dbname=" + dbname + " user=" + user + " password=" + password;
    conn = PQconnectdb(conninfo.utf8().get_data());

    if (PQstatus(conn) != CONNECTION_OK)
    {
        UtilityFunctions::print("Connection to database failed: " + String(PQerrorMessage(conn)));
        close_db();
    }
    else
    {
        UtilityFunctions::print("Connected to database successfully.");
    }
}

void PostgreSQL::close_db()
{
    if (conn)
    {
        PQfinish(conn);
        conn = nullptr;
    }
}

Array PostgreSQL::query(const String &sql)
{
    Array result;

    if (!conn)
    {
        UtilityFunctions::print("No database connection.");
        return result;
    }

    PGresult *res = PQexec(conn, sql.utf8().get_data());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        UtilityFunctions::print("Query failed: " + String(PQerrorMessage(conn)));
        PQclear(res);
        return result;
    }

    int nrows = PQntuples(res);
    int nfields = PQnfields(res);

    for (int i = 0; i < nrows; i++)
    {
        Dictionary row;
        for (int j = 0; j < nfields; j++)
        {
            String field_name = String(PQfname(res, j));
            String field_value = String(PQgetvalue(res, i, j));
            row[field_name] = field_value;
        }
        result.append(row);
    }

    PQclear(res);
    return result;
}

void PostgreSQL::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("connect_db", "host", "port", "dbname", "user", "password"), &PostgreSQL::connect_db);
    ClassDB::bind_method(D_METHOD("close_db"), &PostgreSQL::close_db);
    ClassDB::bind_method(D_METHOD("query", "sql"), &PostgreSQL::query);
}
