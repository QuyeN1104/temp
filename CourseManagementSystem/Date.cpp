#include"library.h"

bool Date::operator!=(const Date& other) const {
    return (day != other.day || month != other.month || year != other.year);
}
string normalizeDateOfBirth(string s){
    string sDate = s;
    if(sDate[2] != '/'){
        sDate = "0" + sDate;
    }
    if(sDate[5] != '/'){
        sDate.insert(3,"0");
    }
    return sDate;
}
Date stringToDate(const string& sDate){
    string sdate = normalizeDateOfBirth(sDate);
    Date x;
    x.day = stoi(sdate.substr(0,2));
    x.month = stoi(sdate.substr(3,2));
    x.year = stoi(sdate.substr(6));
    return x;
}
string dateToString(const Date& date){
    string sDate = to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
    if(sDate[2] != '/'){
        sDate = "0" + sDate;
    }
    if(sDate[5] != '/'){
        sDate.insert(3,"0");
    }
    return sDate;
}
string splitNameClassFromFile(const string& fileDirection){
    size_t dotPosition = fileDirection.find('.');
    if (dotPosition != std::string::npos) {
        return fileDirection.substr(0, dotPosition);
    }
}

