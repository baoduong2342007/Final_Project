#include "Master_Data_Management.h"
#include "Data_Persistence.h"

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
            if (data.get_id(s)->cnt_transaction > 0){
                cout << "There exist transactions have this " << name << "\n";
                cout << "Failed\n";
            }
            else{
                cout << "Successful\n";
                data.ins(s);
            }
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
        if (t == 0) break;
        if (t == 1) particular_data(wallet , "wallet");
        if (t == 2) particular_data(income , "income");
        if (t == 3) particular_data(expense , "expense");
    }
    save();
}

