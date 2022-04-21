#include <sqlite3.h>
#include "Data.h"

using namespace std;

Data::Data() {
	sqlite3* DB;
	int Exit = sqlite3_open(dir, &DB);
	sqlite3_close(DB);
}

void Data::CreateTables() {
	vector<pair<string, string>> tables(NumberOfTables, make_pair("UnNamed", ""));

	tables[0].first = "USER";
	tables[0].second = "CREATE TABLE IF NOT EXISTS " + tables[0].first + "("
		"UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"FirstName  TEXT NOT NULL, "
		"LastName   TEXT NOT NULL, "
		"ProfilePicture  TEXT NOT NULL, "
		"Description  TEXT NOT NULL, "
		"Password     TEXT NOT NULL, "
		"PHONENUMBER  TEXT NOT NULL UNIQUE, "
		"Visibility   TEXT NOT NULL);";

	
	tables[1].first  = "ChatRoom";
	tables[1].second = "CREATE TABLE IF NOT EXISTS " + tables[1].first + "("
		"RoomID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Name   TEXT NOT NULL);";


	tables[2].first = "ChatRoomInfo";
	tables[2].second =
		"CREATE TABLE IF NOT EXISTS " + tables[2].first + "("
		"AdminName  TEXT  NOT NULL,"
		"ChatRoomID INTEGER  NOT NULL ,"
		"NumberOfParticipants  TEXT,"
		"RoomType   TEXT NOT NULL,"
		"PRIMARY KEY (AdminName,ChatRoomID),"
		"FOREIGN KEY (ChatRoomID) REFERENCES ChatRoom (RoomID));";
		
	tables[3].first = "Message";
	tables[3].second =
		"CREATE TABLE IF NOT EXISTS " + tables[3].first + "("
		"SenderId  INTEGER NOT NULL ,"
		"ChatRoomID INTEGER  NOT NULL ,"
		"SenderName  TEXT NOT NULL ,"
		"Text        TEXT NOT NULL,"
		"IsDeleted   TEXT NOT NULL,"
		"FOREIGN KEY (SenderId) REFERENCES USER (UserID),"
		"FOREIGN KEY (ChatRoomID) REFERENCES ChatRoom (RoomID));";

	// **************************************************************** //

	for (int i = 0; i < NumberOfTables; i++) {
		cerr << tables[i].first << ": ";
		CreateTable(tables[i].second);
	}
}

void Data::CreateTable(string& SQL) {
	sqlite3* DB;
	char* messageError;
	try
	{
		int exit = 0;
		exit = sqlite3_open(dir, &DB);
		exit = sqlite3_exec(DB, SQL.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "*** Error in createTable function ***\n";
			sqlite3_free(messageError);
		}
		else
			cout << "*** Table created Successfully ***\n";
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}
}

void Data::InsertData(string& TableName, string& Columns, string& values) {
	//  Columns must be in this format = (Column1, Column2, Column3, Column4, Column5, ColumnN)
	//	values must be in this format and same order as columns =  ('1213', 'A', 'B', '12', '123', 'N')

	sqlite3* DB;
	char* messageError;
	int Exit = sqlite3_open(dir, &DB);

	string SQL = "INSERT INTO " + TableName + Columns + "VALUES" + values + ";";

	Exit = sqlite3_exec(DB, SQL.c_str(), NULL, 0, &messageError);
	if (Exit != SQLITE_OK) {
		cerr << "*** Error in InsertData function ***\n";
		sqlite3_free(messageError);
	}
	else {
		cerr << "*** Records Inserted Successfully ***\n";
	}
}

vector<map<string, string>> Data::SelectData(string& TableName, string& Columns) {
	//	columns must be in this format = (column1, column2, column3, columnN)
	Rows.clear();
	sqlite3* DB;
	char* messageError;
	int Exit = sqlite3_open(dir, &DB);

	string SQL = "SELECT " + Columns + " FROM " + TableName;

	Exit = sqlite3_exec(DB, SQL.c_str(), CallBack, NULL, &messageError);

	if (Exit != SQLITE_OK) {
		cerr << "*** Error in SelectData function ***\n";
		sqlite3_free(messageError);
	}
	else {
		cerr << "*** Records Selected Successfully ***\n";
	}
	return Rows;
}

int Data::CallBack(void* NotUsed, int argc, char** argv, char** azColumnName) {
	map<string, string> Row;
	for (int i = 0; i < argc; i++) {
		Row[azColumnName[i]] = argv[i];
		//	cerr << azColumnName[i] << ": " << argv[i] << "\n";
	}

	Rows.push_back(Row);
	return 0;
}

void Data::UpdateData(string& TableName, string& UpdatedColumn, string& Condition) {
	//	UPDATE table SET column = newvalue WHERE column = Condition
	//	in condition all values must be between ' '
	sqlite3* DB;
	char* messageError;
	int Exit = sqlite3_open(dir, &DB);

	string SQL = "UPDATE " + TableName + " SET " + UpdatedColumn + Condition;

	Exit = sqlite3_exec(DB, SQL.c_str(), NULL, 0, &messageError);

	if (Exit != SQLITE_OK) {
		cerr << "*** Error in UpdateData function ***\n";
		sqlite3_free(messageError);
	}
	else {
		cerr << "*** Records Updated Successfully ***\n";
	}
}

void Data::DeleteData(string& TableName, string& Condition) {
	//	in condition all values must be between ' '
	sqlite3* DB;
	char* messageError;
	int Exit = sqlite3_open(dir, &DB);

	string SQL = "DELETE FROM " + TableName + " " + Condition;

	Exit = sqlite3_exec(DB, SQL.c_str(), NULL, 0, &messageError);

	if (Exit != SQLITE_OK) {
		cerr << "*** Error in DeleteData function ***\n";
		sqlite3_free(messageError);
	}
	else {
		cerr << "*** Records Deleted Successfully ***\n";
	}
}