#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "Data.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

void printselected(vector<map<string, string>>& vec) {
	for (auto it : vec) {
		for (auto itt : it) {
			cout << itt.first << " " << itt.second << "\n";
		}
		cout << "\n";
	}
}

int main() {

	Data test; // create your database 
	test.CreateTables(); // create all tables

	string tablename = "CHATROOM";
	string columns = "(Name, DESCREPTION)";
	string values = "('Kebol3dewya', 'ht3ml eh ya w7sh')";
	test.InsertData(tablename, columns, values);


	columns = "(Name, DESCREPTION)";
	values = "('AdelShakal', '6 ela tlt')";
	test.InsertData(tablename, columns, values);


	string newval = "Name = 'haaaey'";
	string cond = "WHERE ID = '1'";
	test.UpdateData(tablename, newval, cond);


	cond = "WHERE ID = '1'";
	test.DeleteData(tablename, cond);

	string selectcol = "*";
	vector<map<string, string>> vec = test.SelectData(tablename, selectcol);
	printselected(vec);

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
//   testinp project 