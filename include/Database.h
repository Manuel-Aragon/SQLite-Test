#include "sqlite3.h"
#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <sstream>

struct DatabaseReturn
{
	int code = 0;			     //corresponds to SQLite Result Code
	std::string message = "";   //message from function
    std::string sql_return;     //data from database
};

class Database
{
private:
    Database(const std::string a_name, const std::string a_initialization_file);
    ~Database();
    struct Deleter {    //custom deleter for smart pointer sqlite3
        void operator()(sqlite3* a_sqlite3);
    };
    DatabaseReturn initialize(const std::string a_initialization_file);    //only called when databse does not exist
    sqlite3* getHandle() const noexcept
    {
        return m_sqlite3.get();
    }

    std::string m_file_path;
    std::unique_ptr<sqlite3, Deleter> m_sqlite3;
public:
    static Database& get()
    {
        return create(nullptr, nullptr);
    }

    static Database& create(const std::string a_name, const std::string a_initialization_file)
    {
        static auto db = Database(a_name, a_initialization_file);
        return db;
    }

    DatabaseReturn execute(const std::string a_sql);    //middle man to execute sql statements
    Database(const Database &) = delete;    //delete assignment operator
    Database & operator = (const Database &) = delete;  //delete assignment operator

    //std::string getPath() const { return m_file_path; }
};

