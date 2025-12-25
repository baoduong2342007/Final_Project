#include "Global.h"
#include "Recurring_Management.h"
#include "Transaction_Management.h"
#include "Data_Persistence.h"
using namespace std;

Date next_month(Date d) {
    d.month++;
    if (d.month == 13) { d.month = 1; d.year++; }
    return d;
}

void apply_recurring_transaction() {
    Date now = current_date();
    Dynamic_array<int> pos;
    for (int i = 0; i < auto_event.cur_n; i++) {
        RecurringTransaction& X = auto_event.get_val(i);
        while (compare_date(X.start_date, now) <= 0 && compare_date(X.start_date, X.end_date) <= 0) {
            Transaction tmp;
            tmp.date = X.start_date;
            tmp.source = X.source;
            tmp.source_id = X.source_id;
            tmp.wallet_id = X.wallet_id;
            tmp.amount = X.amount;
            tmp.description = X.description;
            output_date(X.start_date);
            if (valid_date(tmp.date)) just_add_transaction(tmp);
            X.start_date = next_month(X.start_date);
        }
        if (compare_date(X.start_date, X.end_date) >= 0) pos.push_back(i);
    }
    for (int i = 0; i < pos.cur_n; i++) auto_event.del(pos.get_val(i) - i);
}

void add_recurring(RecurringTransaction& X) {
    if (!X.source_id || !X.wallet_id || auto_event.exist(X)) {
        cout << RED << "=> Failed (Invalid data or Exists)\n" << BLUE;
        return;
    }
    auto_event.push_back(X);
    X.source_id->cnt_transaction++;
    X.wallet_id->cnt_transaction++;
    cout << GREEN << "=> Successful\n" << BLUE;
}

RecurringTransaction input_recurring() {
    RecurringTransaction X; string s;
    separate(); cout << "- Category (1 -> Income , 2 -> Expense) :\n";
    X.source = input_int(1, 2);
    
    separate(); cout << "- Start date :\n";
    X.start_date = input_date(false);

    separate(); cout << "- End date :\n";
    Date end_d = input_date(true);
    if (end_d.day == 0) {
        X.end_date = Date(31, 12, 9999);
        cout << CYAN << "=> Set to Indefinite\n" << BLUE;
    }
    else X.end_date = end_d;

    separate(); s = (X.source == 1) ? "Income" : "Expense";
    cout << "- " << s << " name :\n";
    s = input_string();
    X.source_id = (X.source == 1) ? income.get_id(s) : expense.get_id(s);

    separate(); cout << "- Amount :\n";
    X.amount = input_long_long(0);

    separate(); cout << "- Wallet name :\n";
    s = input_string();
    X.wallet_id = wallet.get_id(s);

    separate(); cout << "- Description :\n";
    X.description = input_string();

    return X;
}

void output_recurring_row(int id, const RecurringTransaction& R) {
    string type = (R.source == 1) ? "Income" : "Expense";
    string cat = (R.source == 1) ? income.get_string(R.source_id) : expense.get_string(R.source_id);
    string w_name = wallet.get_string(R.wallet_id);
    string start_date = to_string(R.start_date.day) + "/" + to_string(R.start_date.month) + "/" +
        to_string(R.start_date.year);
    string end_date = to_string(R.end_date.day) + "/" + to_string(R.end_date.month) + "/" +
        to_string(R.end_date.year);
    string color = (R.source == 1) ? GREEN : RED;
    
    cout << left
        << setw(5) << id
        << setw(12) << start_date
        << setw(12) << end_date
        << setw(10) << type
        << setw(15) << truncate_text(cat, 13)
        << color << right << setw(15) << format_money(R.amount) << BLUE
        << "   "
        << left << setw(15) << truncate_text(w_name, 13)
        << setw(20) << truncate_text(R.description, 18)
        << "\n";
}

void list_recurring() {
    if (auto_event.cur_n == 0) {
        cout << RED << "There are currently no recurring transactions.\n" << BLUE;
        return;
    }

    cout << CYAN << "ALL RECURRING TRANSACTIONS\n" << BLUE;
    big_separate();
    // title
    cout << YELLOW;
    cout << left << setw(5) << "ID"
        << setw(12) << "Start"
        << setw(12) << "End"
        << setw(10) << "Type"
        << setw(15) << "Category"
        << right << setw(15) << "Amount"
        << "   "
        << left << setw(15) << "Wallet"
        << setw(20) << "Desc"
        << "\n";

    cout << string(98, '-') << "\n" << BLUE;

    for (int i = 0; i < auto_event.cur_n; i++) {
        output_recurring_row(i, auto_event.get_val(i));
    }
}

void update_recurring(RecurringTransaction& R){
    separate();
    int yes_no;
    cout << GREY << "Answer: Yes = 1, No = 0\n" << BLUE;
    // Start date can only be changed if start date is in the future
    if (compare_date(R.start_date, current_date()) == 1){
        cout << "- Change start date? ";
        yes_no = input_int(0,1);
        if (yes_no == 1) {
            cout << "- New start date: ";
            R.start_date = input_date(false);
        }
    }
    // End date
    cout << "- Change end date? ";
    yes_no = input_int(0,1);
    if (yes_no == 1){
        cout << "- New end date: ";
        R.end_date = input_date(true);
    }
    // Source_id and Wallet should not be changed
    // Amount
    cout << "- Change amount? ";
    yes_no = input_int(0,1);
    if(yes_no == 1){
        cout << "- New amount:\n";
        R.amount = input_long_long(0);
    }
    // Description
    cout << "- Change description? ";
    yes_no = input_int(0,1);
    if(yes_no == 1){
        cout << "- New description:\n";
        R.description = input_string();
    }

    cout << GREEN << "=> Updated successfully\n" << BLUE;
}


void manage_recurring() {
    while (true) {
        clear_screen();
        separate();
        cout << CYAN << "Manage Recurring\n" << BLUE;
        separate();

        cout << "[0] Back\n[1] Add\n[2] Delete\n[3] List all\n[4] Update date, amount and description\n";
        int t = input_int(0, 4);

        if (t == 0) break;

        if (t == 1) {
            clear_screen();
            separate();
            cout << CYAN << "Add Recurring Transaction\n" << BLUE;
            separate();
            RecurringTransaction X = input_recurring();
            add_recurring(X);
            pause();
        }

        if (t == 2) {
            clear_screen();
            separate();
            cout << CYAN << "Delete Recurring Transaction\n" << BLUE;
            separate();
            if (auto_event.cur_n == 0) {
                cout << RED << "No recurring transactions to delete.\n" << BLUE;
            }
            else {
                cout << "ID (0-" << auto_event.cur_n - 1 << "):\n";
                int id = input_int(0, auto_event.cur_n - 1);
                auto_event.get_val(id).source_id->cnt_transaction--;
                auto_event.get_val(id).wallet_id->cnt_transaction--;
                auto_event.del(id);
                cout << GREEN << "Deleted\n" << BLUE;
            }
            pause();
        }
        if (t == 3){
            clear_screen();
            separate();
            cout << CYAN << "List all Recurring Transactions\n" << BLUE;
            separate();
            list_recurring();
            pause();
        }
        if (t == 4){
            clear_screen();
            separate();
            cout << CYAN << "Update Recurring Transaction\n" << BLUE;
            separate();
            if (auto_event.cur_n == 0) {
                cout << RED << "No recurring transactions to update.\n" << BLUE;
            }
            else {
                cout << "Enter ID " << GREY << "(-1 to cancel)" << BLUE << " : ";
                int id = input_int(-1, auto_event.cur_n - 1);
                if (id == -1){
                    cout << GREEN << "Cancelled\n" << BLUE;
                }
                else {
                    cout << YELLOW;
                    cout << left << setw(5) << "ID"
                        << setw(12) << "Start"
                        << setw(12) << "End"
                        << setw(10) << "Type"
                        << setw(15) << "Category"
                        << right << setw(15) << "Amount"
                        << "   "
                        << left << setw(15) << "Wallet"
                        << setw(20) << "Desc"
                        << "\n" << BLUE;
                    RecurringTransaction& R = auto_event.get_val(id);
                    output_recurring_row(id, R); // show the chosen recurring transaction
                    update_recurring(R);
                }
            }
            pause();
        }

        save();
    }
}
