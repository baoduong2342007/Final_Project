#include <iostream>
#include <fstream>
#include <string>

#include "Recurring_Management.h"
#include "Global.h"
#include "Transaction_Management.h"

using namespace std;

// dates, help for monthly transactions
bool month_passed(Date last, Date now) {
    if (now.year > last.year) return true;
    if (now.year == last.year && now.month > last.month) return true;
    return false;
}
Date next_month(Date d) {
    d.month++;
    if (d.month == 13) {
        d.month = 1;
        d.year++;
    }
    return d;
}
bool after_end(Date d, Date end) {
    if (end.year == 0) return false; // no end
    return compare_date(d, end) > 0;
}
// auto generate transactions monthly
void apply_recurring_transactions() {
    Date now = current_date();
    for (int i = 0; i < auto_event.cur_n; i++) {
        RecurringTransaction& R = auto_event.get_val(i);
        while (month_passed(R.last_generated, now)) {
            Date gen_date = next_month(R.last_generated);
            // stop if passed end date
            if (after_end(gen_date, R.end_date)) break;
            Transaction X;
            X.date = gen_date;
            X.source = R.source;
            X.source_id = R.source_id;
            X.wallet_id = R.wallet_id;
            X.amount = R.amount;
            X.description = R.description;
            // invalid master data
            if (X.source_id == nullptr || X.wallet_id == nullptr) break;
            int before = event.cur_n;
            add_transaction(X);
            // failed (balance / duplicate)
            if (event.cur_n == before) break;
            R.last_generated = gen_date;
        }
    }
}
// string

bool contains_substring(const string& text, const string& key) {
    if (key.empty()) return true;
    return text.find(key) != string::npos;
}
// add, delete, list all, search

void add_recurring() {
    RecurringTransaction R;
    string s;
    cout << "1) Income  2) Expense : ";
    cin >> R.source;
    cout << "Start ";
    input_date(R.start_date);
    R.last_generated = R.start_date;
    cout << "End date (day month year, year = 0 for no end): ";
    cin >> R.end_date.day >> R.end_date.month >> R.end_date.year;
    cout << "Category name: ";
    cin.ignore();
    getline(cin, s);
    R.source_id = (R.source == 1) ? income.get_id(s) : expense.get_id(s);
    cout << "Wallet name: ";
    getline(cin, s);
    R.wallet_id = wallet.get_id(s);
    cout << "Amount: ";
    cin >> R.amount;
    cout << "Description: ";
    cin.ignore();
    getline(cin, R.description);
    if (R.source_id == nullptr || R.wallet_id == nullptr || R.amount < 0) {
        cout << "Invalid recurring transaction\n";
        return;
    }
    auto_event.push_back(R);
    cout << "Recurring transaction added\n";
}
void delete_recurring() {
    int id;
    cout << "Enter recurring number to delete: ";
    cin >> id;
    if (id < 0 || id >= auto_event.cur_n) {
        cout << "Invalid number\n";
        return;
    }
    auto_event.del(id);
    cout << "Recurring transaction deleted\n";
}
void list_recurring() {
    for (int i = 0; i < auto_event.cur_n; i++) {
        RecurringTransaction& R = auto_event.get_val(i);
        cout << i << ") ";
        cout << (R.source == 1 ? "Income" : "Expense") << "\n";

        cout << "   Start ";
        output_date(R.start_date);

        if (R.end_date.year == 0)
            cout << "   End   none\n";
        else {
            cout << "   End   ";
            output_date(R.end_date);
        }

        cout << "   Amount      : " << R.amount << "\n";
        cout << "   Wallet      : " << wallet.get_string(R.wallet_id) << "\n";
        cout << "   Description : " << R.description << "\n";
    }
}
void search_recurring_by_description() {
    string key;
    cout << "Search keyword: ";
    cin.ignore();
    getline(cin, key);
    bool found = false;

    for (int i = 0; i < auto_event.cur_n; i++) {
        RecurringTransaction& R = auto_event.get_val(i);

        if (contains_substring(R.description, key)) {
            found = true;
            cout << i << ") ";
            cout << (R.source == 1 ? "Income" : "Expense") << "\n";
            cout << "   Start ";
            output_date(R.start_date);
            if (R.end_date.year == 0)
                cout << "   End   none\n";
            else {
                cout << "   End   ";
                output_date(R.end_date);
            }
            cout << "   Amount      : " << R.amount << "\n";
            cout << "   Wallet      : " << wallet.get_string(R.wallet_id) << "\n";
            cout << "   Description : " << R.description << "\n";
        }
    }
    if (!found) {
        cout << "No recurring transaction matches \"" << key << "\"\n";
    }
}

// main menu manage

void manage_recurring() {
    int t;
    while (true) {
        separate();
        cout << "0. Back\n";
        cout << "1. Add recurring transaction\n";
        cout << "2. Delete recurring transaction\n";
        cout << "3. List all recurring transactions\n";
        cout << "4. Search recurring by name (description)\n";
        cout << "Choose: ";
        cin >> t;
        if (t == 0) break;
        if (t == 1) add_recurring();
        if (t == 2) delete_recurring();
        if (t == 3) list_recurring();
        if (t == 4) search_recurring_by_description();
    }
}
