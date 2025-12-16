#pragma once

#include <bits/stdc++.h>
#include "Dynamic_array.h"
#include "Transaction.h"
#include "Trie.h"
#include "Date.h"

using namespace std;

extern Dynamic_array<Transaction> event;
extern Trie wallet;
extern Trie income;
extern Trie expense;

void separate();

void clear_screen();

void pause();

void resetInputStream();

int safe_input_int(int l , int r);

long long safe_input_long_long(long long x);

string safe_input_string();

void clear_all();
