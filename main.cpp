#include <iostream>
#include "include/sqlite3.h"
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>

static int createDB(const char*);
static int createTable(const char*, const char*);
static int insertData(const char*,const char*);
static int updateData(const char*,const char*);
static int deleteData(const char*, const char*);
static int callback(void*, int, char**, char**);
static int selectData(const char*, const char*);

int main()
{
    std::string database_name = "sqLite_test.db";
    std::string table_file = "sql_make.txt";
    sqlite3 *db;
	std::string sql_string;
    std::fstream table_create_stream(table_file, std::fstream::in);

    if(std::filesystem::exists(database_name))
    {
        std::cout << database_name << " Exists!" << std::endl;
        sqlite3_open(database_name.c_str(), &db);
    }
    else
    {
        std::cout << database_name << " does not exists" << std::endl;
        createDB(database_name.c_str());
        while (getline(table_create_stream, sql_string, ';'))
        {
            sql_string.push_back(';');
            createTable(database_name.c_str(), sql_string.c_str());
        }
		table_create_stream.close();
    }
	std::string sql_querey = "SELECT * FROM characterTable;";

	selectData(database_name.c_str(), sql_querey.c_str());

}

static int createDB(const char* name)
{
    sqlite3 *db;
    int exit =0;
    exit = sqlite3_open(name, &db);
    sqlite3_close(db);
    std::cout << "Database " << name << " created!" << std::endl;
    return 0;
}
static int createTable(const char* name, const char* sql)
{
    sqlite3 *db;
    char* messageError;
    try
	{
		int exit = 0;
		exit = sqlite3_open(name, &db);
		// An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here //
		exit = sqlite3_exec(db, sql, NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl;
		sqlite3_close(db);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	return 0;
}

static int selectData(const char* name, const char* sql)
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(name, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql, callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return 0;
}

static int insertData(const char* name, const char* sql)
{
	sqlite3* DB;
	char* messageError;
		
	 sql = ("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");

	int exit = sqlite3_open(name, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql, NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;

	return 0;
}

static int updateData(const char* name, const char* sql)
{
	sqlite3* DB;
	char* messageError;

	sql = ("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");

	int exit = sqlite3_open(name, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql, NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in updateData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records updated Successfully!" << std::endl;

	return 0;
}

static int deleteData(const char* name, const char* sql)
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(name, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql, callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records deleted Successfully!" << std::endl;

	return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        // column name and value
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }

    std::cout << std::endl;

    return 0;
}