#pragma once

#include <bits/stdc++.h>
#include "Transaction.h"
#include "Trie.h"
#include "Dynamic_array.h"

Trie wallet , income , expense;
Dynamic_array<Transaction> event;

void clear_all(){
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}

