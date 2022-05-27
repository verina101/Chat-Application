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

/*

#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
//#define fre freopen("input.txt","r",stdin) , freopen("output.txt","w",stdout) ;
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
void convertDate(string s , dateTime &t){
    int size = s.size();
    vector<string>vec;
    string tmp;
    for (int i = 0; i < size; ++i) {
        if(s[i]==' '){vec.push_back(tmp);tmp.clear();}
        else tmp.push_back(s[i]);
    }
    vec.push_back(tmp);
    // day month num time year
    // Format Tue May 10 15:44:26 2022
//    cout<<s<<endl;
    t.dayName= vec[0];
    t.month  = vec[1];
    t.day    = vec[2];
    t.hours  = vec[3].substr(0,2);
    t.mins   = vec[3].substr(3,2);
    t.seconds= vec[3].substr(6,2);
    t.year   = vec[4];
}
long long numberOfMins(dateTime t){
    // get NO.Days from 00 to today's date in days
    long long totalNumberOfDays=0;
    map<string,pair<int,int>>mp;
    int days [] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
    mp["Jan"]= {31,1};
    mp["Feb"]= {28,2};
    mp["Mar"]= {31,3};
    mp["Apr"]= {30,4};
    mp["May"]= {31,5};
    mp["Jun"]= {30,6};
    mp["Jul"]= {31,7};
    mp["Aug"]= {31,8};
    mp["Sep"]= {30,9};
    mp["Oct"]= {31,10};
    mp["Nov"]= {30,11};
    mp["Dec"]= {31,12};
    totalNumberOfDays+=(stoi(t.year)*365); // years
    int start  = 1;
    int end    = mp[t.month].second;
    for (int i = start; i < end; ++i) {
        totalNumberOfDays+=days[i];
    }
    totalNumberOfDays+= stoi(t.day);
    long long totalNumberOfMin = (1ll*totalNumberOfDays*24*60)+ (stoi(t.hours)*60) + (stoi(t.mins));
    return totalNumberOfMin;
}

bool isValidStory(string s1 ){
    // it takes current time from database
    time_t now = time(0);
    dateTime t;
    char *dt = ctime(&now);
    string s2(dt);
    cout<<"current time  "<<s2<<endl;
    dateTime t1,t2;
    convertDate(s1,t1);
    convertDate(s2,t2);
    long long mins1,mins2;
    mins1=numberOfMins(t1);
    mins2=numberOfMins(t2);
    if(abs(mins1-mins2) >= 1440)return false;
    else return true;
}

    // difference between two days in mins 1440 min
    // this is my code for this problem
    string s ="Wed May 10 19:30:19 2022";
    cout<<"Saved time    "<<s<<endl;
    cout<<isValidStory(s);
//  convertDate(s,t);
//  cout<<numberOfMins(t)<<endl;
}


*/
