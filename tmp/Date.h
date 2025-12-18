#pragma once
#include <bits/stdc++.h>
using namespace std;

const int day_of_month[12] = {31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};

struct Date{
    int day , month , year;

    Date(){
        day = month = year = 0;
    }

    Date(int d, int m, int y) {
        day = d; month = m; year = y;
    }
};

bool valid_date(Date X);

void output_date(Date &X);

Date current_date();

bool is_leap_year(Date X);

bool same_date(Date X , Date Y);

int compare_date(Date X , Date Y);
