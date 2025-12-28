#pragma once

#include "Date.h"
#include "Trie.h"

using namespace std;

struct RecurringTransaction {
    Date start_date; // internal 
    Date display_start; // UI date
    Date end_date; // end_date = 0 0 0 => no limit
    int source;  // 1 = income, 2 = expense
    Trie_node* source_id;
    Trie_node* wallet_id;
    long long amount;
    string description;
    // init
    RecurringTransaction(){
        display_start = start_date = end_date = Date();
        source_id = wallet_id = nullptr;
        amount = 0;
    }

    bool operator == (const RecurringTransaction &other) const{
        if (same_date(display_start, other.display_start) == false) return false;
        if (same_date(end_date , other.end_date) == false) return false;
        if (source != other.source) return false;
        if (source_id != other.source_id) return false;
        if (wallet_id != other.wallet_id) return false;
        if (amount != other.amount) return false;
        if (description != other.description) return false;
        return true;
    }
};
