#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;
struct dateTime{
    string day;
    string month;
    string year;
    string dayName;
    string hours;
    string mins;
    string seconds;
};
class DateTime
{
public:
    DateTime();
    void convertDate(string s , dateTime &t);
    long long numberOfMins(dateTime t);
    bool isValidStory(string s1);

};

#endif // DATETIME_H
