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
    size_t pos = fileDirection.rfind('/') + 1;
    if(pos == string::npos){
        pos = 0;
    }
    if (dotPosition != std::string::npos) {
        return fileDirection.substr(pos, dotPosition - pos);
    }
}
string fullNameSchoolYear(string shortNameYear){
    string fullName = "20" + shortNameYear.substr(0,2) + "-20" + to_string(stoi(shortNameYear.substr(0,2))+1);
    return fullName;
}
string splitYearandSemesterfromFile(const string& fileDirection, string& nameYear,string& nameSemester){
    string nameClass  = splitNameClassFromFile(fileDirection); // lấy mã lớp ra
    nameYear = fullNameSchoolYear(nameClass.substr(0,2));
    nameSemester = nameClass.substr(2,1);
    return nameClass;
}

