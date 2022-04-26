#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QDebug>
#include <QtSql>
#include <QVector>
#include <QString>
using namespace std;

static QSqlDatabase DB;
class Data {
    static const int NumberOfTables = 9;

public:
    Data();
    static void CreateTables();
    static void CreateTable(string& SQL);
    static void InsertData(string& TableName, string& Columns, string& values);
    static vector<vector<QString>> SelectData(string& TableName, string& Columns, string& Condition);
    static void UpdateData(string& TableName, string& UpdatedColumn, string& Condition);
    static void DeleteData(string& TableName, string& Condition);
    static void DisplayData (vector<vector<QString>>& vec);

};
#endif // DATA_H
