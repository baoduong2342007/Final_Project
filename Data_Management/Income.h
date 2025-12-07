#pragma once

#include <bits/stdc++.h>
#include "Date.h"

using namespace std;

struct Income{
    string name;
    Date date;
    long long amount;
    string description;

    Income(){
        amount = 0;
        name.clear();
        description.clear();
    }
};

void input_income(Income &X);

void output_income(Income &X);

