 #include <gtest/gtest.h>
 #include "../include/Database.h"
 #include <iostream>
 
const std::string database_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/test.db";
const std::string init_file_path = "/Users/manuelaragon/Documents/Programming/TestProjects/SQLite-Test/resources/sql_make.txt";

TEST(CreateDatabase, areMembersInitialized)
{
    std::filesystem::remove(database_path); //remove database file if it exists
    Database::Get().initialize(database_path, init_file_path);
    EXPECT_EQ(Database::Get().getPath(),database_path);
}

TEST(CreateDatabse, databaseNotInitializedWhenAlreadyExists)
{
    Database::Get().open(database_path);
    Database::Get().close();    //opens and closes to create file
    Database::Get().initialize(database_path, init_file_path);
    EXPECT_EQ("Database already exists.", Database::Get().getMessage());
    EXPECT_EQ(Database::Get().getExitCode(), -1);
}