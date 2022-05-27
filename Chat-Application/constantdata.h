#ifndef CONSTANTDATA_H
#define CONSTANTDATA_H
#include<string>
using namespace std;

class constantdata
{
    static string phoneNumber;
public:
    constantdata();
    static void   setphoneNumber(string name);
    static string getphoneNumber();
};

#endif // CONSTANTDATA_H
