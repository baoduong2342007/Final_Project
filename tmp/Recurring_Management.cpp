#include "Global.h"
#include "Recurring_Management.h"
#include "Transaction_Management.h"
using namespace std;

Date next_month(Date d) {
    d.month++;
    if (d.month == 13){ d.month = 1; d.year++; }
    return d;
}

void apply_recurring_transaction(){
    Date now = current_date();
    Dynamic_array<int> pos;
    for (int i = 0; i < auto_event.cur_n; i++) {
        RecurringTransaction &X = auto_event.get_val(i);
        while (compare_date(X.start_date , now) <= 0 && compare_date(X.start_date , X.end_date) <= 0){
            Transaction tmp;
            tmp.date = X.start_date;
            tmp.source = X.source;
            tmp.source_id = X.source_id;
            tmp.wallet_id = X.wallet_id;
            tmp.amount = X.amount;
            tmp.description = X.description;

            if (valid_date(tmp.date)) just_add_transaction(tmp);
            X.start_date = next_month(X.start_date);
        }
        if (compare_date(X.start_date , X.end_date) >= 0) pos.push_back(i);
    }
    for (int i = 0 ; i < pos.cur_n ; i++) auto_event.del(pos.get_val(i) - i);
}

void add_recurring(RecurringTransaction &X){
    if (!X.source_id || !X.wallet_id || auto_event.exist(X)) {
        cout << "=> Failed (Invalid data or Exists)\n"; return;
    }
    auto_event.push_back(X);
    X.source_id->cnt_transaction++;
    X.wallet_id->cnt_transaction++;
    cout << "=> Successful\n";
}

RecurringTransaction input_recurring(){
    RecurringTransaction X; string s;
    separate(); cout << "- Category (1 -> Income , 2 -> Expense) :\n";
    X.source = input_int(1 , 2);

    separate(); cout << "- Start date :\n";
    X.start_date = input_date(false);

    separate(); cout << "- End date :\n";
    Date end_d = input_date(true);
    if (end_d.day == 0) {
        // Fix: Dung constructor Date(...) thay vi { ... }
        X.end_date = Date(31, 12, 9999);
        cout << "=> Set to Indefinite\n";
    } else X.end_date = end_d;

    separate(); s = (X.source == 1) ? "Income" : "Expense";
    cout << "- " << s << " name :\n"; s = input_string();
    X.source_id = (X.source == 1) ? income.get_id(s) : expense.get_id(s);

    separate(); cout << "- Amount :\n"; X.amount = input_long_long(0);
    separate(); cout << "- Wallet name :\n"; s = input_string(); X.wallet_id = wallet.get_id(s);
    separate(); cout << "- Description :\n"; X.description = input_string();
    return X;
}

void manage_recurring() {
    while (true) {
        clear_screen(); separate(); cout << "Manage Recurring\n"; separate();
        cout << "[0] Back\n[1] Add\n[2] Delete\n[3] Apply Now\n";
        int t = input_int(0 , 3);
        if (t == 0) break;
        if (t == 1) {
             RecurringTransaction X = input_recurring();
             add_recurring(X); pause();
        }
        if (t == 2) {
             if(auto_event.cur_n == 0) cout << "Empty\n";
             else {
                 cout << "ID (0-" << auto_event.cur_n - 1 << "):\n";
                 int id = input_int(0, auto_event.cur_n - 1);
                 auto_event.get_val(id).source_id->cnt_transaction--;
                 auto_event.get_val(id).wallet_id->cnt_transaction--;
                 auto_event.del(id); cout << "Deleted\n";
             }
             pause();
        }
        if (t == 3) { apply_recurring_transaction(); cout << "Applied!\n"; pause(); }
    }
}
