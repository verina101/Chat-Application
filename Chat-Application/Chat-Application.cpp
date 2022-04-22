#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "Data.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

void PrintSelectedData(vector<map<string, string>>& vec) {
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


}