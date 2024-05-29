extends Node

var connection = null

func _init():
	pass

func connect_to_database(host, port, dbname, user, password):
	connection = PostgreSQL.connect(host, port, dbname, user, password)
	if connection:
		print("Connected to PostgreSQL database successfully.")
	else:
		print("Failed to connect to PostgreSQL database.")

func create(table, data):
	if connection:
		var query = "INSERT INTO " + table + " ("
		var values = " VALUES ("
		for key in data.keys():
			query += key + ","
			values += "'" + str(data[key]) + "',"
		query = query.substr(0, query.length() - 1) + ")"
		values = values.substr(0, values.length() - 1) + ")"
		query += values + ";"
		connection.query(query)
		print("Record created successfully.")
	else:
		print("No database connection.")

func read(table, condition):
	if connection:
		var query = "SELECT * FROM " + table
		if condition != "":
			query += " WHERE " + condition + ";"
		else:
			query += ";"
		var result = connection.query(query)
		return result
	else:
		print("No database connection.")
		return null

func update(table, data, condition):
	if connection:
		var query = "UPDATE " + table + " SET "
		for key in data.keys():
			query += key + "='" + str(data[key]) + "',"
		query = query.substr(0, query.length() - 1)
		if condition != "":
			query += " WHERE " + condition + ";"
		else:
			query += ";"
		connection.query(query)
		print("Record updated successfully.")
	else:
		print("No database connection.")

func delete(table, condition):
	if connection:
		var query = "DELETE FROM " + table
		if condition != "":
			query += " WHERE " + condition + ";"
		else:
			query += ";"
		connection.query(query)
		print("Record deleted successfully.")
	else:
		print("No database connection.")
