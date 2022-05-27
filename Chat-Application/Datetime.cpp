#include "Datetime.h"

DateTime::DateTime(){

}

void DateTime::convertDate(string s , dateTime &t){
    int size = s.size();
    //cout<<s.size()<<endl;
    vector<string>vec;
    string tmp="";
    for (int i = 0; i < size; ++i) {
        if(s[i]==' '){vec.push_back(tmp);tmp.clear();}
        else tmp.push_back(s[i]);
    }
    vec.push_back(tmp);
    tmp.clear();
    vector<string>time;
    for(int i =0; i < vec[3].size();i++){
        if(vec[3][i]==':'){
            time.push_back(tmp);
            tmp.clear();
        }
        else{
            tmp.push_back(vec[3][i]);
        }
    }
    time.push_back(tmp);
    t.dayName= vec[0];
    t.month  = vec[1];
    t.day    = vec[2];
    t.hours  = time[0];
    t.mins   = time[1];
    t.seconds= time[2];
    t.year   = vec[4];
    vec.clear();
    time.clear();
}


long long DateTime::numberOfMins(dateTime t){
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
    totalNumberOfDays+=(stol(t.year, nullptr, 10)*365); // years
    int start  = 1;
    int end    = mp[t.month].second;
    for (int i = start; i < end; ++i) {
        totalNumberOfDays+=days[i];
    }
    totalNumberOfDays+= stol(t.day, nullptr, 10);
    long long totalNumberOfMin = (1ll*totalNumberOfDays*24*60)+ (stol(t.hours, nullptr, 10)*60) + (stol(t.mins, nullptr, 10));
    return totalNumberOfMin;
}


bool DateTime::isValidStory(string s1 ){
    // it takes current time from database
    time_t now = time(0);
    dateTime t;
    char *dt = ctime(&now);
    string s2=(string)ctime(&now);
    // string s2(dt);
    cout<<"Current time  "<<s2<<endl;
    cout<<"Saved   time  "<<s1<<endl;
    dateTime t1,t2;
    convertDate(s1,t1);
    convertDate(s2,t2);
    long long mins1,mins2;
    mins1=numberOfMins(t1);
    mins2=numberOfMins(t2);
    if(abs(mins1-mins2) >= 1440)return false;
    else return true;
}











