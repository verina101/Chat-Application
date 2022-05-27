#include "constantdata.h"

constantdata::constantdata()
{

}

string constantdata::phoneNumber="01234567895";
void constantdata::setphoneNumber(string phone){
    phoneNumber=phone;
}

string constantdata::getphoneNumber(){
    return phoneNumber;
}
