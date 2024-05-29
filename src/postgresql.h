#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <libpq-fe.h>

using namespace godot;

class PostgreSQL : public Node
{
    GDCLASS(PostgreSQL, Node)

private:
    PGconn *conn;

public:
    PostgreSQL();
    ~PostgreSQL();

    void connect_db(String host, int port, String dbname, String user, String password);
    void close_db();
    Array query(String sql);

protected:
    static void _bind_methods();
};

#endif // POSTGRESQL_H
