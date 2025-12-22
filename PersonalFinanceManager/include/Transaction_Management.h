#pragma once

#include "Global.h"

using namespace std;

void just_add_transaction(Transaction &X);

void add_transaction(Transaction &X);

Transaction input_transaction();

void output_transaction(Transaction X);

void manage_transaction();

void check_financial_health();
