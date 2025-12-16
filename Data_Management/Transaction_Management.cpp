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
    int t; string s , name = (source == 1) ? "Income" : "Expense";
    //
    clear_screen();
    separate();
    cout << "Transaction : " << name << "\n";
    separate();
    cout << "[0]. Back\n";
    cout << "[1]. Insert\n";
    cout << "[2]. Delete\n";
    separate();
    //
    Transaction X;
    t = safe_input_int(0 , 2);
    if (t == 0) return;
    //
    X.source = source;
    //
    input_date(X.date);
    //
    cout << "- " << name << " name :\n";
    s = safe_input_string();
    X.source_id = (source == 1) ? income.get_id(s) : expense.get_id(s);
    //
    cout << "- Amount :\n";
    X.amount = safe_input_long_long(0);
    //
    cout << "- Wallet name :\n";
    s = safe_input_string();
    X.wallet_id = wallet.get_id(s);
    //
    cout << "- Description :\n";
    X.description = safe_input_string();
    pause();
    //
    if (t == 1) add_transaction(X);
    if (t == 2) del_transaction(X);
}

void manage_transaction(){
    while (true){
        clear_screen();
        separate();
        cout << "Manage Transactions\n";
        separate();
        cout << "[0] Back\n";
        cout << "[1] Income\n";
        cout << "[2] Expense\n";
        separate();
        int t = safe_input_int(0 , 2);
        if (t == 0) break;
        particular_transaction(t);
    }
}

