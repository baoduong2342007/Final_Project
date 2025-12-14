#include "Transaction_Management.h"
#include "Data_Persistence.h"

using namespace std;

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
        bool is_negative = false;
        if (X.source == 2){
            long long S = -X.amount;
            for (int i = 0 ; i < event.cur_n ; i++){
                Transaction Y = event.get_val(i);
                if (X.wallet_id == Y.wallet_id){
                    S += (Y.source == 1) ? +Y.amount : -Y.amount;
                    if (Y < X) continue;
                    if (S < 0) is_negative = true;
                }
            }
        }
        if (is_negative == true){
            cout << "There is not enough money to perform insert transaction\n";
            cout << "Failed\n";
        }
        else{
            for (int i = 0 ; i < event.cur_n ; i++){
                Transaction Y = event.get_val(i);
                if (X < Y){
                    pos = i;
                    break;
                }
            }
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
        bool is_negative = false;
        if (X.source == 1){
            long long S = -X.amount;
            for (int i = 0 ; i < event.cur_n ; i++){
                Transaction Y = event.get_val(i);
                if (X.wallet_id == Y.wallet_id){
                    S += (Y.source == 1) ? +Y.amount : -Y.amount;
                    if (Y < X) continue;
                    if (S < 0) is_negative = true;
                }
            }
        }
        if (is_negative == true){
            cout << "There is not enough money to delete this transaction\n";
            cout << "Failed\n";
        }
        else{
            event.del(pos);
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
    cout << "Description : "; getline(cin , X.description);
    if (t == 1) add_transaction(X);
    if (t == 2) del_transaction(X);
}

void manage_transaction(){
    int t;
    while (true){
        separate();
        cout << "0. Back\n";
        cout << "1. Income\n";
        cout << "2. Expense\n";
        cout << "Choose : "; cin >> t;
        if (t == 0) break;
        particular_transaction(t);
    }
    save();
}

