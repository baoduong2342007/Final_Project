#include <bits/stdc++.h>
#include "Dynamic_array.h"
#include "Transaction.h"
#include "Trie.h"
#include "Date.h"

using namespace std;

Dynamic_array<Transaction> event;
Trie wallet , income , expense;

void clear_all(){
    event.clear_all();
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}

void separate(){
    cout << "===============================================================\n";
}

//======================================================================================

void particular_data(Trie &data , string name){
    separate();
    int t; string s;
    cout << "0. Back\n";
    cout << "1. Insert " << name << "\n";
    cout << "2. Delete " << name << "\n";
    cout << "Choose : "; cin >> t;
    if (t == 0) return;
    cout << "Name : "; cin.ignore(); getline(cin , s);
    if (t == 1){
        if (data.exist(s) == true){
            cout << "This " << name << " has already existed\n";
            cout << "Failed\n";
        }
        else{
            cout << "Successful\n";
            data.ins(s);
        }
        return;
    }
    if (t == 2){
        if (data.exist(s) == false){
            cout << "This " << name << " does not exist\n";
            cout << "Failed\n";
        }
        else{
            if (data.get_id(s)->cnt_transaction > 0){
                cout << "There exist transactions have this " << name << "\n";
                cout << "Failed\n";
            }
            else{
                cout << "Successful\n";
                data.del(s);
            }
        }
        return;
    }
}

void manage_master_data(){
    int t;
    while (true){
        separate();
        cout << "0. Back\n";
        cout << "1. Wallet\n";
        cout << "2. Income\n";
        cout << "3. Expense\n";
        cout << "Choose : "; cin >> t;
        if (t == 0) return;
        if (t == 1) particular_data(wallet , "wallet");
        if (t == 2) particular_data(income , "income");
        if (t == 3) particular_data(expense , "expense");
    }
}

//======================================================================================

void add_transaction(Transaction &X){
    string name = (X.source == 1) ? "Income" : "Expense";
    if (X.source_id == nullptr || X.wallet_id == nullptr){
        cout << "The " << name << " or wallet do not exist\n";
        cout << "Failed\n";
        return;
    }
    if (X.amount < 0){
        cout << "The amount must >= 0\n";
        cout << "Failed\n";
        return;
    }
    int pos = event.find_pos(X);
    if (pos != event.cur_n){
        cout << "This transaction has already existed\n";
        cout << "Failed\n";
    }
    else{
        long long S = -X.amount;
        bool is_negative = false;
        if (X.source == 2){
            for (int i = 0 ; i < event.cur_n ; i++){
                Transaction Y = event.get_val(i);
                if (X.wallet_id == Y.wallet_id && compare_date(X.date , Y.date) >= 0){
                    if (Y.source == 1) S += Y.amount; else S -= Y.amount;
                }
            }
            is_negative = (S < 0);
        }
        if (is_negative == true){
            cout << "There is not enough money to perform insert transaction\n";
            cout << "Failed\n";
        }
        else{
            event.ins(pos , X);
            X.source_id->cnt_transaction++;
            X.wallet_id->cnt_transaction++;
            cout << "Successful\n";
        }
    }
}

void del_transaction(Transaction &X){
    string name = (X.source == 1) ? "Income" : "Expense";
    if (X.source_id == nullptr || X.wallet_id == nullptr){
        cout << "The " << name << " or wallet do not exist\n";
        cout << "Failed\n";
        return;
    }
    if (X.amount < 0){
        cout << "The amount must >= 0\n";
        cout << "Failed\n";
        return;
    }
    int pos = event.find_pos(X);
    if (pos == event.cur_n){
        cout << "This transaction does not exist\n";
        cout << "Failed\n";
    }
    else{
        long long S = -X.amount;
        bool is_negative = false;
        if (X.source == 1){
            for (int i = 0 ; i < event.cur_n ; i++){
                Transaction Y = event.get_val(i);
                if (X.wallet_id == Y.wallet_id && compare_date(X.date , Y.date) >= 0){
                    if (Y.source == 1) S += Y.amount; else S -= Y.amount;
                }
            }
            is_negative = (S < 0);
        }
        if (is_negative == true){
            cout << "There is not enough money to delete this transaction\n";
            cout << "Failed\n";
        }
        else{
            event.del(pos , X);
            X.source_id->cnt_transaction--;
            X.wallet_id->cnt_transaction--;
            cout << "Successful\n";
        }
    }
}

void particular_transaction(int source){
    separate();
    int t; string s , name = (source == 1) ? "Income" : "Expense";
    Transaction X;
    cout << "0. Back\n";
    cout << "1. Insert transaction\n";
    cout << "2. Delete transaction\n";
    cout << "Choose : "; cin >> t;
    if (t == 0) return;
    //
    X.source = source;
    //
    input_date(X.date);
    //
    cout << name << " name : "; cin.ignore(); getline(cin , s);
    X.source_id = (source == 1) ? income.get_id(s) : expense.get_id(s);
    //
    cout << "Amount : "; cin >> X.amount;
    //
    cout << "Wallet name : "; cin.ignore(); getline(cin , s);
    X.wallet_id = wallet.get_id(s);
    //
    cout << "Description : "; cin.ignore(); getline(cin , X.description);
    if (t == 1) add_transaction(X);
    if (t == 2) del_transaction(X);
}

void update_transaction(){
    int t;
    while (true){
        separate();
        cout << "0. Back\n";
        cout << "1. Income\n";
        cout << "2. Expense\n";
        cout << "Choose : "; cin >> t;
        if (t == 0) return;
        particular_transaction(t);
    }
}

//==========================================================================================

int main(){
    int t;
    while (true){
        separate();
        cout << "0) Exit the program\n";
        cout << "1) Manage master data\n";
        cout << "2) Update transaction\n";
        cout << "Choose : "; cin >> t;
        if (t == 0){
            break;
        }
        if (t == 1) manage_master_data();
        if (t == 2) update_transaction();
    }
    clear_all();
    return 0;
}
