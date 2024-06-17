#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>
using namespace std;
#define numCsvCols 7
#define defaultUserName  "_admin_hcmus";
#define defaultPassWord  "admin@_-";
#define defaultPassWordStudent "helloworld"

struct Date {
int day, month, year;
bool operator!=(const Date& other) const ;
};
string normalizeDateOfBirth(string s);
Date stringToDate(const string& sDate);
string dateToString(const Date& date);
string splitNameClassFromFile(const string& fileDirection);
string fullNameSchoolYear(string shortNameYear); // trả về năm học đầy đủ từ năm học theo hai số đầu // ex 23->2023-2024
string splitYearandSemesterfromFile(const string& fileDirection, string& nameYear,string& nameSemester); // hàm trả về năm và kì từ mã lớp của một khóa học
