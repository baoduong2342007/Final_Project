#pragma once

#include <bits/stdc++.h>
#include "Date.h"
#include "Trie.h"

using namespace std;

struct Transaction{
    //type +1 : income
    //type -1 : expense
    int type;
    Date date;
    long long amount;
    string description;
    Trie_node type_id , wallet_id;
};

