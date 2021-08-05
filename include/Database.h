#include "sqlite3.h"
#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <sstream>


class Database
{
private:
    Database();
    ~Database();
    struct Deleter {    //custom deleter for smart pointer sqlite3
        void operator()(sqlite3* a_sqlite3);
    };
    sqlite3* getHandle() const noexcept
    {
        return m_sqlite3.get();
    }

    //member variables
    std::string m_name;
    std::string m_message;
    int m_exit_code;
    std::unique_ptr<sqlite3, Deleter> m_sqlite3;
public:
    Database(const Database &) = delete;    //delete assignment operator
    Database & operator = (const Database &) = delete;  //delete assignment operator
    static Database& Get()      //get instance of Database
    {
        static auto db = Database();
        return db;
    }

    void open(const std::string& a_name);
    void initialize(const std::string& a_name, const std::string& a_initialization_file);
    void execute(const std::string& a_sql);    //middle man to execute sql statements
    void close();
    std::string getPath() const{return m_name;};
    std::string getMessage() const {return m_message;};
    int getExitCode() const {return m_exit_code;};
};