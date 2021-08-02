 #include <gtest/gtest.h>
 #include "../include/Database.h"
 
 const std::string database_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/test.db";
 const std::string init_file_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/sql_make.txt";


TEST(CreateDatabase, areMembersInitialized)
{
    EXPECT_NO_FATAL_FAILURE(Database::create(database_path, init_file_path));
    //EXPECT_EQ(Database::get(),database_path);
}