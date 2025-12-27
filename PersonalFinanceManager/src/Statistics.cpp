#include "Statistics.h"
#include <iomanip>

using namespace std;

bool in_range(Date d, Date from, Date to) {
    return (compare_date(d, from) >= 0 && compare_date(d, to) <= 0);
}

void stats_range_summary() {
    clear_screen();
    separate(); cout << CYAN << "      SUMMARY REPORT (BY DATE RANGE)      \n" << BLUE; separate();
    cout << "From Date:\n"; Date from = input_date();
    cout << "To Date:\n";   Date to = input_date();

    long long inc = 0, exp = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (in_range(t.date, from, to)) {
            if (t.source == 1) inc += t.amount;
            else exp += t.amount;
        }
    }
    long long net = inc - exp;

    big_separate();
    cout << "REPORT PERIOD: " << from.day << "/" << from.month << "/" << from.year
         << " - " << to.day << "/" << to.month << "/" << to.year << "\n";
    big_separate();

    cout << left << setw(20) << "CATEGORY" << right << setw(20) << "AMOUNT (VND)" << "\n";
    cout << string(40, '-') << "\n";

    cout << left << setw(20) << "Total Income" << GREEN << right << setw(20) << format_money(inc) << BLUE << "\n";
    cout << left << setw(20) << "Total Expense" << RED << right << setw(20) << format_money(exp) << BLUE << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "NET BALANCE" << ((net >= 0) ? GREEN : RED) << right << setw(20) << format_money(net) << BLUE << "\n";

    pause();
}

void stats_yearly_overview() {
    clear_screen();
    separate(); cout << CYAN << "          YEARLY FINANCIAL OVERVIEW       \n" << BLUE; separate();
    cout << "Enter Year: "; int year = input_int(1900, 3000);

    long long inc = 0, exp = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.date.year == year) {
            if (t.source == 1) inc += t.amount;
            else exp += t.amount;
        }
    }

    long long net = inc - exp;

    big_separate();
    cout << "FINANCIAL STATEMENT FOR YEAR: " << year << "\n";
    big_separate();

    cout << left << setw(20) << "CATEGORY" << right << setw(20) << "AMOUNT (VND)" << "\n";
    cout << string(40, '-') << "\n";

    cout << left << setw(20) << "Total Income" << GREEN << right << setw(20) << format_money(inc) << BLUE << "\n";
    cout << left << setw(20) << "Total Expense" << RED << right << setw(20) << format_money(exp) << BLUE << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "NET BALANCE" << ((net >= 0) ? GREEN : RED) << right << setw(20) << format_money(net) << BLUE << "\n";

    pause();
}

void stats_by_source(int source_type) {
    clear_screen(); separate();
    cout << CYAN << (source_type == 1 ? "      INCOME BREAKDOWN (BY SOURCE)      " : "     EXPENSE BREAKDOWN (BY CATEGORY)    ") << "\n" << BLUE;
    separate();
    cout << "Enter Year: "; int year = input_int(1900, 3000);

    Trie* data_trie = (source_type == 1) ? &income : &expense;
    Dynamic_array<Trie_node*> nodes = data_trie->get_arr_id();
    int n = nodes.cur_n;

    if (n == 0) {
        cout << RED << "=> No categories found!\n" << BLUE;
        nodes.clear_all(); pause(); return;
    }

    long long* sums = new long long[n];
    for(int i=0; i<n; i++) sums[i] = 0;

    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.source == source_type && t.date.year == year && t.source_id != nullptr) {
            if(t.source_id->id >= 0 && t.source_id->id < n) {
                sums[t.source_id->id] += t.amount;
            }
        }
    }

    big_separate();
    cout << "DETAILED REPORT FOR YEAR: " << year << "\n";
    big_separate();

    cout << left << setw(5) << "ID" << setw(30) << "Name" << right << setw(20) << "Total Amount" << "\n";
    cout << string(60, '-') << "\n";

    Dynamic_array<string> names = data_trie->get_arr_string();
    bool has_data = false;
    for (int i = 0; i < n; i++) {
        if (sums[i] > 0) {
            cout << left << setw(5) << i
                 << setw(30) << truncate_text(names.get_val(i), 28)
                 << right << setw(20) << format_money(sums[i]) << "\n";
            has_data = true;
        }
    }
    if(!has_data) cout << RED << "   (No transactions recorded)\n" << BLUE;

    delete[] sums;
    nodes.clear_all();
    names.clear_all();
    pause();
}

void stats_list_valuable() {
    clear_screen(); separate(); cout << CYAN << "   HIGH VALUE TRANSACTIONS LIST   \n" << BLUE; separate();
    cout << "Minimum Amount: "; long long limit = input_long_long(0);

    cout << "\n";
    cout << YELLOW;
    cout << left << setw(12) << "Date"
         << setw(10) << "Type"
         << setw(15) << "Category"
         << right << setw(15) << "Amount"
         << "   "
         << left << setw(20) << "Desc" << "\n";
    cout << string(75, '-') << "\n" << BLUE;

    int cnt = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.amount >= limit) {
            string type = (t.source == 1) ? "Income" : "Expense";
            string cat_name = "N/A";
            if (t.source == 1 && t.source_id) cat_name = income.get_string(t.source_id);
            else if (t.source == 2 && t.source_id) cat_name = expense.get_string(t.source_id);

            string date_str = to_string(t.date.day) + "/" + to_string(t.date.month) + "/" + to_string(t.date.year);
            string color = (t.source == 1) ? GREEN : RED;

            cout << left << setw(12) << date_str
                 << setw(10) << type
                 << setw(15) << truncate_text(cat_name, 13)
                 << color << right << setw(15) << format_money(t.amount) << BLUE
                 << "   "
                 << left << setw(20) << truncate_text(t.description, 18) << "\n";
            cnt++;
        }
    }
    if (cnt == 0) cout << RED << "   (No transactions found)\n" << BLUE;
    pause();
}

void stats_peak_bottom() {
    clear_screen(); separate(); cout << CYAN << "    PEAK / BOTTOM MONTH ANALYSIS    \n" << BLUE; separate();
    cout << "Type: [1] Income   [2] Expense\n"; int type = input_int(1, 2);
    cout << "Mode: [1] Peak (Max) [2] Bottom (Min)\n"; int mode = input_int(1, 2);

    long long (*cache)[13] = new long long[3001][13];

    for(int y=0; y<=3000; y++)
        for(int m=0; m<=12; m++) cache[y][m] = 0;

    bool has_data = false;
    for(int i=0; i<event.cur_n; i++){
        Transaction& t = event.get_val(i);
        if(t.source == type && t.date.year >= 1900 && t.date.year <= 3000){
            cache[t.date.year][t.date.month] += t.amount;
            has_data = true;
        }
    }

    if(!has_data){
        cout << RED << "=> No data available.\n" << BLUE;
        delete[] cache; pause(); return;
    }

    long long target_val = (mode == 1) ? -1 : 9223372036854775807LL;
    int res_m = 0, res_y = 0;

    for(int y=1900; y<=3000; y++){
        for(int m=1; m<=12; m++){
            long long val = cache[y][m];
            if(val > 0) {
                if(mode == 1) {
                    if(val > target_val) { target_val = val; res_y = y; res_m = m; }
                } else {
                    if(val < target_val) { target_val = val; res_y = y; res_m = m; }
                }
            }
        }
    }

    big_separate();
    string s_type = (type == 1) ? "Income" : "Expense";
    string s_mode = (mode == 1) ? "HIGHEST (PEAK)" : "LOWEST (BOTTOM)";

    if(res_y != 0) {
        cout << " RESULT: " << s_mode << " " << s_type << " MONTH\n";
        cout << string(40, '-') << "\n";
        cout << " Month: " << res_m << "/" << res_y << "\n";
        cout << " Total: " << format_money(target_val) << "\n";
    } else {
        cout << RED << "=> No transactions found.\n" << BLUE;
    }

    delete[] cache;
    pause();
}

void stats_most_valuable_in_range() {
    clear_screen(); separate(); cout << CYAN << "   HIGHEST VALUE TRANSACTION (RANGE)   \n" << BLUE; separate();
    cout << "From Date:\n"; Date from = input_date();
    cout << "To Date:\n";   Date to = input_date();
    cout << "Type: [1] Income   [2] Expense\n"; int type = input_int(1, 2);

    long long max_val = -1;
    int idx = -1;

    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.source == type && in_range(t.date, from, to)) {
            if (t.amount > max_val) {
                max_val = t.amount;
                idx = i;
            }
        }
    }

    big_separate();
    if (idx != -1) {
        Transaction& res = event.get_val(idx);
        cout << GREEN << " FOUND RECORD:\n" << BLUE;
        cout << " - Date:   " << res.date.day << "/" << res.date.month << "/" << res.date.year << "\n";
        cout << " - Amount: " << format_money(res.amount) << "\n";
        cout << " - Wallet: " << (res.wallet_id ? wallet.get_string(res.wallet_id) : "N/A") << "\n";
        string src = (type == 1) ? income.get_string(res.source_id) : expense.get_string(res.source_id);
        cout << " - Source: " << src << "\n";
        cout << " - Note:   " << res.description << "\n";
    } else {
        cout << RED << "=> No transaction found in this range.\n" << BLUE;
    }
    pause();
}


