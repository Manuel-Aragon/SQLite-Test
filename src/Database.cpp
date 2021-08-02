#include "../include/Database.h"

Database::Database(const std::string a_name, const std::string a_initialization_file) : m_file_path{a_name}//TO-DO: add paramater for logging class
{
    try
    {
    	bool exist = std::filesystem::exists(a_name);		//determine if database with argument name has been created
		sqlite3* handle = nullptr;							//create database connection handle
        int code = sqlite3_open(a_name.c_str(), &handle);	//try to open database
		m_sqlite3.reset(handle);							//smart pointer takes ownership of handle
        if (code != SQLITE_OK){								//throw error if databse was not opened
            std::string message = "Databse " + a_name + " was not created!\n";
            std::cerr << message;
        }
		if (!exist){
        initialize(a_initialization_file);		//initialize database if database has not been created yet
		}
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        //TO-DO: write error message to log file
    }
}

Database::~Database() = default;

//Deleter function for sqlite3 smart pointer
void Database::Deleter::operator()(sqlite3* a_db)
{
    const int ret = sqlite3_close(a_db); // Calling sqlite3_close() with a nullptr argument is a harmless no-op.

    // // Avoid unreferenced variable warning when build in release mode
    // (void) ret;
}

DatabaseReturn Database::initialize(const std::string a_initialization_file)
{
	DatabaseReturn return_value = {-1, "Error opening file: " + a_initialization_file};
    std::ifstream init_stream(a_initialization_file, std::ifstream::in);
    if (init_stream.is_open())
	{
		std::stringstream str_stream;
		str_stream << str_stream.rdbuf();
		std::string sql_string = str_stream.str();
		std::cout << sql_string;
		return_value = execute(sql_string);
	}
	return return_value;
}

DatabaseReturn Database::execute(const std::string a_sql)
{
	try
	{
		char* error_message;
		// An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here //
		int exit_code = sqlite3_exec(getHandle(), a_sql.c_str(), nullptr, nullptr, &error_message);
		if (exit_code != SQLITE_OK)
		{//does the order of whats in this block matter?
			std::cerr << "Error in execute function: "<< exit_code << error_message << '\n';
			sqlite3_free(error_message); //free memory anytime an error message is produced
		}
		return {exit_code, "Database created successfully."};
	}
	catch(const std::exception& e)
	{
		//send return to logging
		std::cerr << e.what() << '\n';
	}
}

// retrieve contents of database used by selectData()

// argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array,
// int callback(void *NotUsed, int argc, char **argv, char **azColName)
// {
// 	for (int i = 0; i < argc; i++)
// 	{
// 		// column name and value
// 		std::cout << azColName[i] << ": " << argv[i] << std::endl;
// 	}

// 	std::cout << std::endl;

// 	return 0;
// }