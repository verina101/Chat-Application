#pragma once
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <map>
using namespace std;

static const char* dir = "DataBase.db";
static vector<map<string, string>> Rows;

class Data {
	static const int NumberOfTables = 4;


public:
	Data();
	static void CreateTables();
	static void CreateTable(string& SQL);
	static void InsertData(string& TableName, string& Columns, string& values);
	static vector<map<string, string>> SelectData(string& TableName, string& Columns);
	static int CallBack(void* NotUsed, int argc, char** argv, char** azColumnName);
	static void UpdateData(string& TableName, string& UpdatedColumn, string& Condition);
	static void DeleteData(string& TableName, string& Condition);

};
