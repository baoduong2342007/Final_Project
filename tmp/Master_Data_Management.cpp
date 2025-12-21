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
    cout << "[3] Edit\n";
    cout << "[4] Show list\n";
    separate();
    //
    int t; string s;
    t = input_int(0 , 4);
    if (t == 0) return;
    //
    if (t == 1){
        clear_screen();
        separate();
        cout << "Insert : " << name << "\n";
        separate();
        //
        cout << "- Name :\n";
        s = input_string();
        //
        if (data.exist(s) == true){
            cout << "=> This " << name << " already exists\n";
            cout << "=> Failed\n";
        }
        else{
            cout << "=> Successful\n";
            data.ins(s);
        }
        pause();
    }
    //
    if (t == 2){
        clear_screen();
        separate();
        cout << "Delete : " << name << "\n";
        separate();
        //
        cout << "- Name :\n";
        s = input_string();
        //
        if (data.exist(s) == false){
            cout << "=> This " << name << " does not exist\n";
            cout << "=> Failed\n";
        }
        else{
            if (data.get_id(s)->cnt_transaction > 0){
                cout << "=> There exist transactions have this " << name << "\n";
                cout << "=> Failed\n";
            }
            else{
                cout << "=> Successful\n";
                data.del(s);
            }
        }
        pause();
    }
    if (t == 3){
        clear_screen();
        separate();
        cout << "Edit : " << name << "\n";
        separate();
        string s;
        cout << "- Old name :\n";
        s = input_string();
        if (data.exist(s) == false){
            cout << "=> The old name does not exist\n";
            cout << "=> Failed\n";
        }
        else{
            Trie_node* old_id = data.get_id(s);
            cout << "- New name :\n";
            s = input_string();
            bool keep_doing = true;
            if (data.exist(s) == true){
                cout << "=> The new name already exist\n";
                cout << "=> Do you still want to change???\n";
                cout << "[0] No\n";
                cout << "[1] Yes\n";
                int t = input_int(0 , 1);
                if (t == 0) keep_doing = false;
            }
            else{
                data.ins(s);
            }
            if (keep_doing == true){
                Trie_node* new_id = data.get_id(s);
                for (int i = 0 ; i < event.cur_n ; i++){
                    Transaction &X = event.get_val(i);
                    if (X.source_id == old_id) X.source_id = new_id;
                    if (X.wallet_id == old_id) X.wallet_id = new_id;
                }
                for (int i = 0 ; i < auto_event.cur_n ; i++){
                    RecurringTransaction &X = auto_event.get_val(i);
                    if (X.source_id == old_id) X.source_id = new_id;
                    if (X.wallet_id == old_id) X.wallet_id = new_id;
                }
                new_id->cnt_transaction += old_id->cnt_transaction;
                old_id->cnt_transaction = 0;
                s = data.get_string(old_id);
                data.del(s);
                cout << "=> Successful\n";
            }
            else{
                cout << "=> Cancelled\n";
            }
        }
        pause();
    }
    if (t == 4){
        clear_screen();
        separate();
        cout << "List of : " << name << "\n";
        separate();
        Dynamic_array<string> arr = data.get_arr_string();
        for (int i = 0 ; i < arr.cur_n ; i++) cout << i << ") " << arr.get_val(i) << "\n";
        arr.clear_all();
        pause();
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
        save();
    }
}

