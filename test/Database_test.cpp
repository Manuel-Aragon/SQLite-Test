 #include <gtest/gtest.h>
 #include "../include/Database.h"
 #include <iostream>
 
const std::string database_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/test.db";
const std::string init_file_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/sql_make.txt";

TEST(CreateDatabase, areMembersInitialized)
{
    Database::Get().initialize(database_path, init_file_path);
    EXPECT_EQ(Database::Get().getExitCode(), SQLITE_OK);
    EXPECT_EQ(Database::Get().getMessage(),"Database created successfully.");
    EXPECT_EQ(Database::Get().getPath(),database_path);
}