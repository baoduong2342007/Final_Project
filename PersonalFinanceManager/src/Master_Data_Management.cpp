#include "Master_Data_Management.h"
#include "Data_Persistence.h"
#include <iomanip>

void particular_data(Trie& data, string name) {
    clear_screen();
    separate();
    cout << CYAN << " MASTER DATA: " << name << "\n" << BLUE;
    separate();
    cout << "[0] Back\n";
    cout << "[1] Insert new\n";
    cout << "[2] Delete\n";
    cout << "[3] Edit name\n";
    cout << "[4] Show list (Table)\n";
    separate();

    int t; string s;
    t = input_int(0, 4);
    if (t == 0) return;

    if (t == 1) {
        clear_screen();
        separate(); cout << CYAN << "Insert : " << name << "\n" << BLUE; separate();
        cout << "- Name to insert:\n";
        s = input_string();

        if (data.exist(s) == true) {
            cout << RED << "=> Already exists\n" << BLUE;
        } else {
            data.ins(s);
            cout << GREEN << "=> Successful\n" << BLUE;
        }
        pause();
    }

    if (t == 2) {
        clear_screen();
        separate(); cout << CYAN << "Delete : " << name << "\n" << BLUE; separate();
        cout << "- Name to delete:\n";
        s = input_string();

        if (data.exist(s) == false) {
            cout << RED << "=> Not found\n" << BLUE;
        } else {
            if (data.get_id(s)->cnt_transaction > 0) {
                cout << RED << "=> Cannot delete! (Used in transactions)\n" << BLUE;
            } else {
                data.del(s);
                cout << GREEN << "=> Deleted\n" << BLUE;
            }
        }
        pause();
    }
    if (t == 3) {
        clear_screen();
        separate(); cout << CYAN << "Edit : " << name << "\n" << BLUE; separate();
        cout << "- Old name:\n";
        s = input_string();
        if (data.exist(s) == false) {
            cout << RED << "=> Not found\n" << BLUE;
        } else {
            Trie_node* old_id = data.get_id(s);
            cout << "- New name:\n";
            s = input_string();

            bool process = true;
            if (data.exist(s) == true) {
                cout << YELLOW << "=> New name already exists! Merge them? [0] No [1] Yes\n" << BLUE;
                if (input_int(0, 1) == 0) process = false;
            } else {
                data.ins(s);
            }

            if (process) {
                Trie_node* new_id = data.get_id(s);

                for (int i = 0; i < event.cur_n; i++) {
                    Transaction& X = event.get_val(i);
                    if (X.source_id == old_id) X.source_id = new_id;
                    if (X.wallet_id == old_id) X.wallet_id = new_id;
                }
                for (int i = 0; i < auto_event.cur_n; i++) {
                    RecurringTransaction& X = auto_event.get_val(i);
                    if (X.source_id == old_id) X.source_id = new_id;
                    if (X.wallet_id == old_id) X.wallet_id = new_id;
                }
                new_id->cnt_transaction += old_id->cnt_transaction;
                old_id->cnt_transaction = 0;

                string old_name = data.get_string(old_id);
                data.del(old_name);
                cout << GREEN << "=> Updated successfully\n" << BLUE;
            } else {
                cout << "=> Cancelled\n";
            }
        }
        pause();
    }
    if (t == 4) {
        clear_screen();
        separate(); cout << CYAN << "List of : " << name << "\n" << BLUE; separate();

        Dynamic_array<string> arr = data.get_arr_string();
        if(arr.cur_n == 0) {
            cout << RED << " (Empty)\n" << BLUE;
        } else {
            cout << left << setw(6) << "ID" << setw(30) << "Name" << "\n";
            cout << string(40, '-') << "\n";
            for (int i = 0; i < arr.cur_n; i++) {
                cout << left << setw(6) << i << setw(30) << arr.get_val(i) << "\n";
            }
        }
        arr.clear_all();
        pause();
    }
}

void manage_master_data() {
    while (true) {
        clear_screen();
        separate();
        cout << CYAN << "Manage Master Data\n" << BLUE;
        separate();
        cout << "[0] Back\n";
        cout << "[1] Wallets (Bank, Cash...)\n";
        cout << "[2] Income Sources (Salary, Bonus...)\n";
        cout << "[3] Expense Categories (Food, Rent...)\n";
        separate();
        int t = input_int(0, 3);
        if (t == 0) break;
        if (t == 1) particular_data(wallet, "Wallet");
        if (t == 2) particular_data(income, "Income Source");
        if (t == 3) particular_data(expense, "Expense Category");
        save();
    }
}
