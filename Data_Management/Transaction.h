#pragma once

#include <bits/stdc++.h>
#include "Date.h"
#include "Trie.h"

using namespace std;

struct Transaction{
    Date date;
    int source; //1 : income , 2 : expense
    Trie_node* source_id;
    Trie_node* wallet_id;
    long long amount;
    string description;

    Transaction(){
        amount = 0;
        source_id = wallet_id = nullptr;
    }

    bool operator == (const Transaction &other) const{
        if (same_date(date , other.date) == false) return false;
        if (source != other.source) return false;
        if (source_id != other.source_id) return false;
        if (wallet_id != other.wallet_id) return false;
        if (amount != other.amount) return false;
        if (description != other.description) return false;
        return true;
    }
};

