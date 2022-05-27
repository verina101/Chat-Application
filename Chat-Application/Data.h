#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QDebug>
#include <QtSql>
#include <QVector>
#include <QString>
#include <QMap>
using namespace std;

static QSqlDatabase DB;
static map<string,string> myColumns;

class Data {
    static const int NumberOfTables = 9;

    static void CreateTable(string& SQL);
public:
    Data();
    static void CreateTables();
    static void InsertData(string TableName, string values);
    static vector<vector<QString>> SelectData(string TableName, string Columns, string Condition);
    static void UpdateData(string TableName, string UpdatedColumn, string Condition);
    static void DeleteData(string& TableName, string& Condition);
    static void DisplayData(vector<vector<QString>> vec);
    static string convertToValue(QString myqstr);
};
#endif // DATA_H
