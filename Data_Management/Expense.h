#pragma once

#include <bits/stdc++.h>
#include "Date.h"

using namespace std;

struct Expense{
    string name;
    Date date;
    long long amount;
    string description;

    Expense(){
        amount = 0;
        name.clear();
        description.clear();
    }
};

void input_expense(Expense &X);

void output_expense(Expense &X);


