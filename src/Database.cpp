#include "../include/Database.h"

Database::Database()//TO-DO: add paramater for logging class
{
}
Database::~Database()
{
	close();
}

//Deleter function for sqlite3 sma rt pointer
void Database::Deleter::operator()(sqlite3* a_db)
{
    const int ret = sqlite3_close(a_db);
}

void Database::initialize(const std::string& a_name, const std::string& a_initialization_file)
{
	bool exists = std::filesystem::exists(a_name);		//determine if database with argument name has been created
	if (exists){
		m_message = "Database already exists.";
		m_exit_code = -1;
		return;
	}
	open(a_name);
    std::ifstream init_stream(a_initialization_file, std::ifstream::in);
    if (init_stream.is_open()){
		std::stringstream str_stream;
		str_stream << str_stream.rdbuf();
		std::string sql_string = str_stream.str();
		execute(sql_string);
		if (m_exit_code != SQLITE_OK)
		{
			m_message = "Error when initializing database";
		}
		else
		{
			m_message = "Database created successfully.";
		}
		m_message = sql_string;
	}
	else{
		m_message = "Error: Could not open file: " + a_name;
	}
}

void Database::execute(const std::string& a_sql)
{
	char* error_message;
	// An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here //
	m_exit_code = sqlite3_exec(getHandle(), a_sql.c_str(), nullptr, nullptr, &error_message);
	if (m_exit_code != SQLITE_OK) {
		m_message = "Error in execute function: ";
		m_message.append(error_message);
		sqlite3_free(error_message); //free memory anytime an error message is produced
	}
	else
	{
		m_message = "SQL sucessfully evaluated";
	}
	
}

void Database::open(const std::string& a_name) {
	sqlite3* handle = nullptr;							//create database connection handle
	int code = sqlite3_open(a_name.c_str(), &handle);	//try to open database
	if (code != SQLITE_OK){
		m_message = "Database " + a_name + " was not created.";
	}
	else
	{
		m_name = a_name;
		m_sqlite3.reset(handle);						//smart pointer takes ownership of handle
	}
}

void Database::close() {
	sqlite3_close(getHandle());
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