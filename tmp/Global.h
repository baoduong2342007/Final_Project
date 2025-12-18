#pragma once
#include <bits/stdc++.h>
#include "Dynamic_array.h"
#include "Transaction.h"
#include "RecurringTransaction.h"
#include "Trie.h"
#include "Date.h"

using namespace std;

extern Dynamic_array<Transaction> event;
extern Dynamic_array<RecurringTransaction> auto_event;
extern Trie wallet;
extern Trie income;
extern Trie expense;

// UI
void separate();
void big_separate();
void clear_screen();
void pause();
void resetInputStream();

// Input
int input_int(int l , int r);
long long input_long_long(long long x);
string input_string();
Date input_date(bool allow_empty = false);

void clear_all();

// Dashboard
long long get_wallet_balance(Trie_node* wallet_id);
long long get_total_balance();
void show_dashboard();
