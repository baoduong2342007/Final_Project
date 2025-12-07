#pragma once

#include <bits/stdc++.h>

using namespace std;

struct Date{
    int day , month , year;
};

void input_date_from_console(Date &X);

void output_date_to_consle(Date X);

bool is_leap_year(Date X);

Date current_Date();

bool same_Date(Date X , Date Y);

int compare_date(Date X , Date Y);

