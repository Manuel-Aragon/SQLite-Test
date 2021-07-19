#include <iostream>
#include "sqlite3.h"

int main()
{
    std::cout << "Hello World" << std::endl;
    std::cout << "Sqlite version: " << sqlite3_libversion() << std::endl;
    sqlite3 *db;
    sqlite3_open(
        "sqLite_test.db",   /* Database filename (UTF-8) */
        &db       /* OUT: SQLite db handle */
    );
    
}