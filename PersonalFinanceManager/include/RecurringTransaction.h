#pragma once

#include "Date.h"
#include "Trie.h"
#include <string>

using namespace std;

struct RecurringTransaction {
    Date start_date;
    Date end_date; // year == 0 -> no end
    Date last_generated;
    int source;  // 1 = income, 2 = expense
    Trie_node* source_id;
    Trie_node* wallet_id;
    long long amount;
    string description;
    // init
    RecurringTransaction() {
        source = 0;
        source_id = wallet_id = nullptr;
        amount = 0;
        end_date.year = 0; // default: no end
    }
};
