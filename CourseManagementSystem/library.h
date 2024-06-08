#pragma once
#include<bits/stdc++.h>
using namespace std;
#define numCsvCols 7
    struct Date {
        int day, month, year;
        bool operator!=(const Date& other) const {
            return (day != other.day || month != other.month || year != other.year);
        }
    };

