#include "Master_Data_Management.h"
#include "Data_Persistence.h"

void particular_data(Trie &data , string name){
    clear_screen();
    separate();
    cout << "Current data : " << name << "\n";
    separate();
    cout << "[0] Back\n";
    cout << "[1] Insert\n";
    cout << "[2] Delete\n";
    separate();
    int t; string s;
    t = input_int(0 , 2);
    if (t == 0) return;
    if (t == 1){
        clear_screen();
        separate();
        cout << "Insert : " << name << "\n";
        separate();
        cout << "- Name :\n";
        s = input_string();
        if (data.exist(s) == true){
            cout << "=> This " << name << " already exists\n";
        }
        else{
            cout << "=> Successful\n";
            data.ins(s);
        }
        pause();
        return;
    }
    if (t == 2){
        clear_screen();
        separate();
        cout << "Delete : " << name << "\n";
        separate();
        cout << "- Name :\n";
        s = input_string();
        if (data.exist(s) == false){
            cout << "This " << name << " does not exist => Failed\n";
        }
        else{
            if (data.get_id(s)->cnt_transaction > 0){
                cout << "=> There exist transactions have this " << name << " => Failed\n";
            }
            else{
                cout << "=> Successful\n";
                data.del(s);
            }
        }
        pause();
        return;
    }
}

void manage_master_data(){
    while (true){
        clear_screen();
        separate();
        cout << "Manage Master Data\n";
        separate();
        cout << "[0] Back\n";
        cout << "[1] Wallet\n";
        cout << "[2] Income\n";
        cout << "[3] Expense\n";
        separate();
        int t = input_int(0 , 3);
        if (t == 0) break;
        if (t == 1) particular_data(wallet , "wallet");
        if (t == 2) particular_data(income , "income");
        if (t == 3) particular_data(expense , "expense");
    }
}

