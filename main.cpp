#include <iostream>
#include "include/sqlite3.h"
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>

static int createDB(const char*);
static int createTable(const char*, const char*);

int main()
{
    std::string database_name = "sqLite_test.db";
    std::string table_file = "sql_make.txt";
     std::string sql_string = "CREATE TABLE IF NOT EXISTS characterTable("
	 	"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
	 	"NAME      TEXT NOT NULL, "
	 	"Race     TEXT NOT NULL, "
	 	"MaxHitpoints       INT  NOT NULL, "
	 	"CurrentHitpoints   INT NOT NULL, "
	 	"ArmorClass    INT NOT NULL, "
         "MovementSpeed INTEGER NOT NULL,"
    ");";
    sqlite3 *db;

    if(std::filesystem::exists(database_name))
    {
        std::cout << database_name << " Exists!" << std::endl;
    }
    //else
    {
        std::cout << database_name << " does not exists" << std::endl;
        createDB(database_name.c_str());
        std::fstream table_create_stream (table_file, std::fstream::in);
        std::string sql_line;
        std::string sql_string;
        std::stringstream create_string_stream;
        while(getline(table_create_stream, sql_line))
        {
            sql_string += sql_line;
            if (sql_line == "    );")
            {
                break;
            }
            //getline(create_string_stream, sql_string,';');
        }
        createTable(database_name.c_str(), create_string_stream.str().c_str());

    }
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