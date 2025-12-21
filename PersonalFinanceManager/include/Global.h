#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "Dynamic_array.h"
#include "Transaction.h"
#include "RecurringTransaction.h"
#include "Trie.h"
#include "Date.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define GREY    "\033[90m"

using namespace std;

extern Dynamic_array<Transaction> event;
extern Dynamic_array<RecurringTransaction> auto_event;
extern Trie wallet;
extern Trie income;
extern Trie expense;

void separate();
void big_separate();
void clear_screen();
void pause();
void resetInputStream();

string format_money(long long money);
string truncate_text(string s, int width);

int input_int(int l , int r);
long long input_long_long(long long x);
string input_string();
Date input_date(bool allow_empty = false);

void clear_all();

long long get_wallet_balance(Trie_node* wallet_id);
long long get_total_balance();
void show_dashboard();
