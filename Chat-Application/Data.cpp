#include "Data.h"
using namespace std;

Data::Data() {
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("DataBase.db");
    bool Exit = DB.open();
    if(!Exit) {
        cerr << "Error in Data function";
        assert(0);
    }
    DB.close();
}

void Data::CreateTables() {
    vector<pair<string, string>> tables(NumberOfTables, make_pair("UnNamed", ""));

    tables[0].first = "USER";
    tables[0].second = "CREATE TABLE IF NOT EXISTS " + tables[0].first + "("
                       "UserID          INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT, "
                       "FirstName       TEXT NOT NULL, "
                       "LastName        TEXT NOT NULL, "
                       "ProfilePicture  TEXT NOT NULL, "
                       "Description     TEXT NOT NULL, "
                       "Password        TEXT NOT NULL, "
                       "PhoneNumber     TEXT NOT NULL UNIQUE, "
                       "Visibility      INTEGER NOT NULL);";
    myColumns[tables[0].first] = "(FirstName, LastName, ProfilePicture, Description, Password, PhoneNumber, Visibility)";


    tables[1].first  = "CHATROOM";
    tables[1].second = "CREATE TABLE IF NOT EXISTS " + tables[1].first + "("
                       "RoomID          INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT, "
                       "Name            TEXT NOT NULL);";
    myColumns[tables[1].first] = "(Name)";



    tables[2].first = "CHATROOMINFO";
    tables[2].second = "CREATE TABLE IF NOT EXISTS " + tables[2].first + "("
                       "ChatRoomID      INTEGER  NOT NULL, "
                       "AdminName       TEXT  NOT NULL, "
                       "NumberOfParticipants  INTEGER, "
                       "RoomType        INTEGER NOT NULL, "
                       "PRIMARY KEY (AdminName, ChatRoomID), "
                       "FOREIGN KEY (ChatRoomID) REFERENCES ChatRoom (RoomID));";
    myColumns[tables[2].first] = "(ChatRoomID, AdminName, NumberOfParticipants, RoomType)";


    tables[3].first = "MESSAGE";
    tables[3].second = "CREATE TABLE IF NOT EXISTS " + tables[3].first + "("
                       "MessageID       INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                       "SenderID        INTEGER NOT NULL, "
                       "ChatRoomID      INTEGER  NOT NULL, "
                       "SenderName      TEXT NOT NULL, "
                       "Text            TEXT NOT NULL, "
                       "IsDeleted       INTEGER NOT NULL, "
                       "FOREIGN KEY (SenderId) REFERENCES USER (UserID), "
                       "FOREIGN KEY (ChatRoomID) REFERENCES ChatRoom (RoomID));";
    myColumns[tables[3].first] = "(SenderID, ChatRoomID, SenderName, Text, IsDeleted)";


    tables[4].first = "MESSAGESTATUS";
    tables[4].second = "CREATE TABLE IF NOT EXISTS " + tables[4].first + "("
                       "MessageID        INTEGER NOT NULL, "
                       "DateTime         TEXT    NOT NULL, "
                       "NumberOfViewers  INTEGER NOT NULL, "
                       "IsSeen           INTEGER NOT NULL, "
                       "PRIMARY KEY (MessageID, DateTime), "
                       "FOREIGN KEY (MessageID) REFERENCES Message (MessageID));";
    myColumns[tables[4].first] = "(MessageID, DateTime, NumberOfViewers, IsSeen)";


    tables[5].first = "CONTACTS";
    tables[5].second = "CREATE TABLE IF NOT EXISTS " + tables[5].first + "("
                       "UserID          INTEGER  NOT NULL, "
                       "ContactID       INTEGER  NOT NULL, "
                       "PRIMARY KEY (UserID, ContactID), "
                       "FOREIGN KEY (UserID) REFERENCES USER (UserID), "
                       "FOREIGN KEY (ContactID) REFERENCES USER (UserID));";
    myColumns[tables[5].first] = "(UserID, ContactID)";



    tables[6].first = "PARTICIPATE";
    tables[6].second = "CREATE TABLE IF NOT EXISTS " + tables[6].first + "("
                       "ChatRoomID      INTEGER  NOT NULL, "
                       "UserID          INTEGER  NOT NULL, "
                       "DateTime        TEXT  NOT NULL, "
                       "PRIMARY KEY (ChatRoomID, UserID), "
                       "FOREIGN KEY (ChatRoomID) REFERENCES ChatRoom (RoomID), "
                       "FOREIGN KEY (UserID) REFERENCES USER (UserID));";
    myColumns[tables[6].first] = "(ChatRoomID, UserID, DateTime)";


    tables[7].first = "STORY";
    tables[7].second = "CREATE TABLE IF NOT EXISTS " + tables[7].first + "("
                       "StoryID          INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                       "StoryOwnerID     INTEGER  NOT NULL, "
                       "StoryOwnerName   TEXT  NOT NULL, "
                       "Text             TEXT  NOT NULL, "
                       "Image            TEXT  NOT NULL, "
                       "DateTime         TEXT  NOT NULL, "
                       "FOREIGN KEY (StoryOwnerID) REFERENCES USER (UserID));";
    myColumns[tables[7].first] = "(StoryOwnerID, StoryOwnerName, Text, Image, DateTime)";


    tables[8].first = "CANVIEW";
    tables[8].second = "CREATE TABLE IF NOT EXISTS " + tables[8].first + "("
                       "UserID          INTEGER  NOT NULL, "
                       "StoryID         INTEGER  NOT NULL, "
                       "PRIMARY KEY (UserID, StoryID), "
                       "FOREIGN KEY (UserID) REFERENCES USER (UserID), "
                       "FOREIGN KEY (StoryID) REFERENCES Story (StoryID));";
    myColumns[tables[8].first] = "(UserID, StoryID)";


    // **************************************************************** //

    for (int i = 0; i < NumberOfTables; i++) {
        cerr << tables[i].first << ": ";
        CreateTable(tables[i].second);
    }
}

void Data::CreateTable(string& SQL) {
    DB.open();

    try {
        QSqlQuery query;
        if(query.exec(QString::fromStdString(SQL))) {
          //  cerr << "*** Table created successfully ***\n";
        } else {
            cerr << "*** Error in CreateTables function ***\n";
        }
    } catch (const exception& e) {
        cerr << e.what();
    }

    DB.close();
}
//when using 'insert function', columns are ordered as in data.cpp
//do not insert values for any AUTOINCEREMENT attribute
void Data::InsertData(string TableName, string values) {
    DB.open();
    for (auto& c: TableName) c = toupper(c);

    string SQL = "INSERT INTO " + TableName + myColumns[TableName] + " VALUES " + values ;
    QSqlQuery query;
    if(query.exec(QString::fromStdString(SQL))) {
        cerr << "*** Records inserted successfully ***\n";
    }
    else {
        cerr << "*** Error in InsertData function ***\n";

    }

    DB.close();
}

vector<vector<QString>> Data::SelectData(string TableName, string Columns, string Condition) {
    //	columns must be in this format = (column1, column2, column3, columnN)
    DB.open();
    vector<vector<QString>> Rows;

    string SQL = "SELECT " + Columns + " FROM " + TableName + " " + Condition;
    QSqlQuery query;
    if(query.exec(QString::fromStdString(SQL))) {
        cerr << "*** Records selected successfully ***\n";

        while(query.next()) {
            Rows.push_back({});

            for(int i = 0; i < 10; i++) {
                QString qCol = query.value(i).toString();
                if(qCol != "") {
                    Rows.back().push_back(qCol);
                }
            }
        }
    }
    else {
        cerr << "*** Error in SelectData function ***\n";
    }

    DB.close();
    return Rows;
}

void Data::UpdateData(string TableName, string UpdatedColumn, string Condition) {
    //	UPDATE (TableName) SET (UpdatedColumn) WHERE (Condition)
    DB.open();

    string SQL = "UPDATE " + TableName + " SET " + UpdatedColumn + " " + Condition;
    QSqlQuery query;
    if(query.exec(QString::fromStdString(SQL))) {
        cerr << "*** Records updated successfully ***\n";
    }
    else {
        cerr << "*** Error in UpdateData function ***\n";
    }

    DB.close();
}

void Data::DeleteData(string& TableName, string& Condition) {
    DB.open();

    string SQL = "DELETE FROM " + TableName + " " + Condition;
    QSqlQuery query;
    if(query.exec(QString::fromStdString(SQL))) {
        cerr << "*** Records deleted successfully ***\n";
    }
    else {
        cerr << "*** Error in DeleteData function ***\n";
    }

    DB.close();
}

void Data::DisplayData(vector<vector<QString>> vec) {
    for (auto row : vec) {
        for (auto col : row) {
            cerr << col.toStdString() << (col == row.back() ? " " : " | ");
        }
        cerr << "\n";
    }
}

string Data::convertToValue(QString myqstr) {
    return ("'" + myqstr + "'").toStdString();
}
