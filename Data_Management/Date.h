#pragma once

#include <bits/stdc++.h>

using namespace std;

struct Date{
    int day , month , year;

    Date(){
        day = month = year = 0;
    }
};

void input_date(Date &X);

void output_date(Date &X);

Date current_date();

bool is_leap_year(Date X);

bool same_date(Date X , Date Y);

int compare_date(Date X , Date Y);


