// Date.cpp
#include "date.h"

Date current_date(){
    //
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_time_t);
    //
    Date ans;
    ans.day = local_tm->tm_mday;
    ans.month = local_tm->tm_mon + 1;
    ans.year = local_tm->tm_year + 1900;
    return ans;
}

void input_date(Date &X){
    cout << "Date : "; cin >> X.day >> X.month >> X.year;
}

void output_date(Date &X){
    cout << "Date : " << X.day << " " << X.month << " " << X.year << "\n";
}

bool is_leap_year(Date X){
    if (X.year % 4 != 0) return false;
    if (X.year % 100 == 0){
        return (X.year % 400 == 0);
    }
    return true;
}

bool same_date(Date X , Date Y){
    return (X.day == Y.day && X.month == Y.month && X.year == Y.year);
}

int compare_date(Date X , Date Y){
    if (same_date(X , Y) == true) return 0;
    if (X.year != Y.year){
        return (X.year < Y.year) ? -1 : +1;
    }
    if (X.month != Y.month){
        return (X.month < Y.month) ? -1 : +1;
    }
    return (X.day < Y.day) ? -1 : +1;
}


