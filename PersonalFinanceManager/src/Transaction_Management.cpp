#include "Transaction_Management.h"
#include "Data_Persistence.h"

using namespace std;

void just_add_transaction(Transaction& X) {
    if (X.source_id == nullptr) return;
    if (X.wallet_id == nullptr) return;
    int pos = event.find_pos(X);
    if (pos == event.cur_n) return;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction Y = event.get_val(i);
        if (X < Y) {
            pos = i;
            break;
        }
    }
    event.ins(pos, X);
    X.source_id->cnt_transaction++;
    X.wallet_id->cnt_transaction++;
}

void add_transaction(Transaction& X) {
    bool check = true;

    if (X.source_id == nullptr) {
        check = false;
        cout << RED;
        if (X.source == 1) {
            cout << "=> This income does not exist\n";
        }
        else {
            cout << "=> This expense does not exist\n";
        }
        cout << BLUE;
    }

    if (X.wallet_id == nullptr) {
        check = false;
        cout << RED << "=> This wallet does not exist\n" << BLUE;
    }

    int pos = event.find_pos(X);
    if (pos != event.cur_n) {
        check = false;
        cout << RED << "=> This transaction already exists\n" << BLUE;
    }

    if (check == false) {
        cout << RED << "=> Failed\n" << BLUE;
    }
    else {
        for (int i = 0; i < event.cur_n; i++) {
            Transaction Y = event.get_val(i);
            if (X < Y) {
                pos = i;
                break;
            }
        }
        event.ins(pos, X);
        X.source_id->cnt_transaction++;
        X.wallet_id->cnt_transaction++;
        cout << GREEN << "=> Successful\n" << BLUE;
    }
}

Transaction input_transaction() {
    Transaction X; string s;

    cout << "- Category type (1 -> Income , 2 -> Expense) :\n";
    X.source = input_int(1, 2);
    separate();

    cout << "- Date (day/month/year) :\n";
    X.date = input_date();
    separate();

    s = (X.source == 1) ? "Income" : "Expense";
    cout << "- " << s << " name :\n";
    s = input_string();
    X.source_id = (X.source == 1) ? income.get_id(s) : expense.get_id(s);
    separate();

    cout << "- Amount :\n";
    X.amount = input_long_long(0);
    separate();

    cout << "- Wallet name :\n";
    s = input_string();
    X.wallet_id = wallet.get_id(s);
    separate();

    cout << "- Description :\n";
    X.description = input_string();

    return X;
}

void output_transaction(Transaction X) {
    string s;

    cout << "- Category type (1 -> Income , 2 -> Expense) :\n";
    cout << ">> " << X.source << "\n";
    separate();

    cout << "- Date (day/month/year) :\n";
    cout << ">> "; output_date(X.date);
    separate();

    s = (X.source == 1) ? "Income" : "Expense";
    cout << "- " << s << " name :\n";
    s = (X.source == 1) ? income.get_string(X.source_id) : expense.get_string(X.source_id);
    cout << ">> " << s << "\n";
    separate();

    cout << "- Amount :\n";
    cout << ">> " << X.amount << "\n";
    separate();

    cout << "- Wallet name :\n";
    s = wallet.get_string(X.wallet_id);
    cout << ">> " << s << "\n";
    separate();

    cout << "- Description :\n";
    cout << ">> " << X.description << "\n";
}

void manage_transaction() {
    while (true) {
        clear_screen();
        separate();
        cout << CYAN << "Manage Transactions\n";
        separate();
        cout << "[0] Back\n";
        cout << "[1] Add transaction\n";
        cout << "[2] Delete transaction\n";
        cout << "[3] List transaction (by date)\n";
        cout << "[4] List all transaction\n";
        separate();

        int t = input_int(0, 4);
        if (t == 0) break;

        if (t == 1) {
            clear_screen();
            separate();
            cout << CYAN << "Add transaction\n";
            separate();
            cout << "[0] Back\n";
            cout << "[1] Continue\n";
            separate();

            int t = input_int(0, 1);
            if (t == 1) {
                Transaction X = input_transaction();
                add_transaction(X);
                pause();
            }
        }

        if (t == 2) {
            clear_screen();
            separate();
            cout << CYAN << "Delete transaction\n";
            separate();
            cout << "[0] Back\n";
            cout << "[1] Continue\n";
            separate();

            int t = input_int(0, 1);
            if (t == 1) {
                if (event.cur_n == 0) {
                    cout << RED << "=> There is no transaction\n";
                    cout << "=> Failed\n" << BLUE;
                }
                else {
                    cout << "- ID of transaction (ID from 0 to " << event.cur_n - 1 << ") :\n";
                    int id = input_int(0, INT_MAX);
                    if (0 <= id && id < event.cur_n) {
                        event.del(id);
                        cout << GREEN << "=> Successful\n" << BLUE;
                    }
                    else {
                        cout << RED << "=> Invalid input!\n";
                        cout << "=> Failed\n" << BLUE;
                    }
                }
                pause();
            }
        }

        if (t == 3) {
            clear_screen();
            separate();
            cout << CYAN << "List transaction (by date)\n";
            separate();
            cout << "- Date (day/month/year) :\n";

            Date date = input_date();
            big_separate();

            int l = 0, r = event.cur_n - 1, st = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (compare_date(event.get_val(mid).date, date) >= 0) {
                    r = mid - 1;
                    if (same_date(event.get_val(mid).date, date)) st = l;
                }
                else {
                    l = mid + 1;
                }
            }

            if (st != -1) {
                while (st < event.cur_n && same_date(event.get_val(st).date, date)) {
                    cout << "- ID : " << st << "\n";
                    output_transaction(event.get_val(st));
                    big_separate();
                    st++;
                }
            }
            else {
                cout << RED << "There is no transaction in ";
                output_date(date);
                cout << BLUE;
            }
            pause();
        }

        if (t == 4){
            if (event.cur_n == 0){
                cout << RED << "There is no transaction\n";
                cout << BLUE;
            }
            else{
                for (int i = 0 ; i < event.cur_n ; i++){
                    cout << "- ID : " << i << "\n";
                    output_transaction(event.get_val(i));
                    big_separate();
                }
            }
            pause();
        }

        save();
    }
}
