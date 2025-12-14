#include "Global.h"

using namespace std;

Dynamic_array<Transaction> event;
Trie wallet;
Trie income;
Trie expense;

void separate(){
    cout << "====================================================================\n";
}

void clear_all(){
    event.clear_all();
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}
