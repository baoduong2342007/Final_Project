#include "Transaction_Management.h"
#include "Data_Persistence.h"

using namespace std;

void print_table_header() {
    cout << YELLOW;
    cout << left << setw(5) << "ID"
         << setw(12) << "Date"
         << setw(10) << "Type"
         << setw(15) << "Category"
         << right << setw(15) << "Amount"
         << "   "
         << left << setw(15) << "Wallet"
         << setw(20) << "Desc" << "\n";
    cout << string(95, '-') << "\n" << BLUE;
}

void print_table_row(int id, Transaction &t) {
    string type = (t.source == 1) ? "Income" : "Expense";

    string cat_name = "N/A";
    if (t.source == 1 && t.source_id) cat_name = income.get_string(t.source_id);
    else if (t.source == 2 && t.source_id) cat_name = expense.get_string(t.source_id);

    string w_name = (t.wallet_id) ? wallet.get_string(t.wallet_id) : "N/A";

    string date_str = to_string(t.date.day) + "/" + to_string(t.date.month) + "/" + to_string(t.date.year);

    string color = (t.source == 1) ? GREEN : RED;

    cout << left << setw(5) << id
         << setw(12) << date_str
         << setw(10) << type
         << setw(15) << truncate_text(cat_name, 13)
         << color << right << setw(15) << format_money(t.amount) << BLUE
         << "   "
         << left << setw(15) << truncate_text(w_name, 13)
         << setw(20) << truncate_text(t.description, 18) << "\n";
}

void just_add_transaction(Transaction& X) {
    if (X.source_id == nullptr) return;
    if (X.wallet_id == nullptr) return;
    int pos = event.find_pos(X);
    if (pos != event.cur_n) return;
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
        if (X.source == 1) cout << "=> This income source does not exist\n";
        else cout << "=> This expense category does not exist\n";
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

    if (!check) {
        cout << RED << "=> Failed\n" << BLUE;
    } else {
        int insert_pos = event.cur_n;
        for (int i = 0; i < event.cur_n; i++) {
            Transaction Y = event.get_val(i);
            if (X < Y) {
                insert_pos = i;
                break;
            }
        }
        event.ins(insert_pos, X);
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
    cout << "- Type: " << ((X.source == 1) ? "Income" : "Expense") << "\n";
    cout << "- Date: " << X.date.day << "/" << X.date.month << "/" << X.date.year << "\n";

    s = (X.source == 1) ? "Income" : "Expense";
    string cat = (X.source == 1) ? income.get_string(X.source_id) : expense.get_string(X.source_id);
    cout << "- " << s << ": " << cat << "\n";

    cout << "- Amount: " << format_money(X.amount) << "\n";
    cout << "- Wallet: " << wallet.get_string(X.wallet_id) << "\n";
    cout << "- Desc: " << X.description << "\n";
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
            separate(); cout << CYAN << "Add transaction\n"; separate();
            cout << "[0] Back\n[1] Continue\n";
            if (input_int(0, 1) == 1) {
                Transaction X = input_transaction();
                add_transaction(X);
                pause();
            }
        }

        if (t == 2) {
            clear_screen();
            separate(); cout << CYAN << "Delete transaction\n"; separate();
            cout << "[0] Back\n[1] Continue\n";
            if (input_int(0, 1) == 1) {
                if (event.cur_n == 0) {
                    cout << RED << "=> No transactions to delete\n" << BLUE;
                } else {
                    cout << "- Enter ID to delete (0-" << event.cur_n - 1 << "):\n";
                    int id = input_int(0, INT_MAX);
                    if (0 <= id && id < event.cur_n) {
                        Transaction& tmp = event.get_val(id);
                        if(tmp.source_id) tmp.source_id->cnt_transaction--;
                        if(tmp.wallet_id) tmp.wallet_id->cnt_transaction--;
                        event.del(id);
                        cout << GREEN << "=> Successful\n" << BLUE;
                    } else {
                        cout << RED << "=> Invalid ID!\n" << BLUE;
                    }
                }
                pause();
            }
        }

        if (t == 3) {
            clear_screen();
            separate();
            cout << CYAN << "List Transaction (By Date)\n" << BLUE;
            separate();
            cout << "- Filter Date:\n";
            Date date = input_date();
            big_separate();

            print_table_header();

            int l = 0, r = event.cur_n - 1, st = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (compare_date(event.get_val(mid).date, date) >= 0) {
                    r = mid - 1;
                    if (same_date(event.get_val(mid).date, date)) st = mid;
                } else {
                    l = mid + 1;
                }
            }

            bool found = false;
            if (st != -1) {
                while(st > 0 && same_date(event.get_val(st-1).date, date)) st--;
                while (st < event.cur_n && same_date(event.get_val(st).date, date)) {
                    print_table_row(st, event.get_val(st));
                    st++;
                    found = true;
                }
            }

            if(!found) {
                cout << RED << "   (No transactions found on this date)\n" << BLUE;
            }
            pause();
        }

        if (t == 4){
            clear_screen();
            cout << CYAN << "ALL TRANSACTIONS\n" << BLUE;

            if (event.cur_n == 0){
                cout << RED << "=> Empty\n" << BLUE;
            } else {
                print_table_header();
                for (int i = 0 ; i < event.cur_n ; i++){
                    print_table_row(i, event.get_val(i));
                }
            }
            pause();
        }

        save();
    }
}

void check_financial_health() {
    long long total = get_total_balance();
    if (total >= 0) return;

    Date now = current_date();

    clear_screen();
    cout << RED << "\n";
    cout << "   /!\\ WARNING: NEGATIVE BALANCE DETECTED /!\\ \n";
    cout << "   ------------------------------------------ \n";
    cout << "   Current Balance: " << format_money(total) << "\n";
    cout << "   Alert: Your spending exceeds your total assets!\n\n" << BLUE;

    cout << "=> Review FINANCIAL REPORT for this month (" << now.month << "/" << now.year << ")?\n";
    cout << "[1] Yes, show details (Income & Expense)\n";
    cout << "[0] Skip\n";

    int t = input_int(0, 1);

    if (t == 1) {
        clear_screen();
        cout << CYAN << "FINANCIAL REPORT: " << now.month << "/" << now.year << "\n" << BLUE;

        bool found = false;
        long long total_inc_month = 0;
        long long total_exp_month = 0;

        print_table_header();

        for (int i = 0; i < event.cur_n; i++) {
            Transaction& trans = event.get_val(i);

            if (trans.date.month == now.month && trans.date.year == now.year) {
                print_table_row(i, trans);

                if (trans.source == 1) total_inc_month += trans.amount;
                else total_exp_month += trans.amount;

                found = true;
            }
        }

        if (!found) {
            cout << RED << "   (No transactions recorded this month)\n" << BLUE;
        } else {
            cout << string(98, '-') << "\n";
            cout << "   SUMMARY THIS MONTH:\n";
            cout << "   + Income : " << GREEN << format_money(total_inc_month) << BLUE << "\n";
            cout << "   - Expense: " << RED << format_money(total_exp_month) << BLUE << "\n";

            long long net = total_inc_month - total_exp_month;
            cout << "   = Net    : " << ((net >= 0) ? GREEN : RED) << format_money(net) << BLUE << "\n";
        }

        cout << "\n";
        pause();
    }
}
