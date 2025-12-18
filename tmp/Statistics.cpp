#include "Statistics.h"

using namespace std;

// --- HELPERS ---
bool in_range(Date d, Date from, Date to) {
    return (compare_date(d, from) >= 0 && compare_date(d, to) <= 0);
}

void print_transaction_short(Transaction& t) {
    cout << "   - "; output_date(t.date);
    cout << " | " << t.amount;

    string w_name = "Unknown";
    if(t.wallet_id) w_name = wallet.get_string(t.wallet_id);
    cout << " | Wallet: " << w_name;

    string s_name = "Unknown";
    if(t.source == 1 && t.source_id) s_name = income.get_string(t.source_id);
    else if(t.source == 2 && t.source_id) s_name = expense.get_string(t.source_id);
    cout << " | Source: " << s_name << "\n";
}

// --- FEATURES ---

// 1. Summary Range
void stats_range_summary() {
    clear_screen(); separate(); cout << "SUMMARY BY DATE RANGE\n"; separate();
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
    separate();
    cout << "REPORT (" << from.day << "/" << from.month << "/" << from.year
         << " - " << to.day << "/" << to.month << "/" << to.year << ")\n";
    cout << "Total Income : " << inc << "\n";
    cout << "Total Expense: " << exp << "\n";
    cout << "Net Balance  : " << inc - exp << "\n";
    pause();
}

// 2. Yearly Overview
void stats_yearly_overview() {
    clear_screen(); separate(); cout << "YEARLY OVERVIEW\n"; separate();
    cout << "Enter Year: "; int year = input_int(1900, 3000);

    long long inc = 0, exp = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.date.year == year) {
            if (t.source == 1) inc += t.amount;
            else exp += t.amount;
        }
    }
    separate();
    cout << "STATISTICS FOR YEAR " << year << "\n";
    cout << "Total Income : " << inc << "\n";
    cout << "Total Expense: " << exp << "\n";
    cout << "Net Balance  : " << inc - exp << "\n";
    pause();
}

// 3 & 4. By Source/Category
void stats_by_source(int source_type) {
    clear_screen(); separate();
    cout << (source_type == 1 ? "INCOME BY SOURCE" : "EXPENSE BY CATEGORY") << "\n";
    separate();
    cout << "Enter Year: "; int year = input_int(1900, 3000);

    Trie* data_trie = (source_type == 1) ? &income : &expense;

    Dynamic_array<Trie_node*> nodes = data_trie->get_arr_id();
    int n = nodes.cur_n;

    if (n == 0) {
        cout << "=> No categories found!\n";
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

    separate();
    cout << "BREAKDOWN FOR YEAR " << year << ":\n";
    Dynamic_array<string> names = data_trie->get_arr_string();
    bool has_data = false;
    for (int i = 0; i < n; i++) {
        if (sums[i] > 0) {
            cout << "- " << names.get_val(i) << ": " << sums[i] << "\n";
            has_data = true;
        }
    }
    if(!has_data) cout << "(No transactions recorded)\n";

    delete[] sums;
    nodes.clear_all();
    names.clear_all();
    pause();
}

// 5. List valuable
void stats_list_valuable() {
    clear_screen(); separate(); cout << "LIST HIGH VALUE TRANSACTIONS\n"; separate();
    cout << "Minimum Amount: "; long long limit = input_long_long(0);

    separate();
    cout << "Transactions >= " << limit << ":\n";
    int cnt = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction& t = event.get_val(i);
        if (t.amount >= limit) {
            print_transaction_short(t);
            cnt++;
        }
    }
    if (cnt == 0) cout << "(None found)\n";
    pause();
}

// 6. Peak / Bottom
void stats_peak_bottom() {
    clear_screen(); separate(); cout << "PEAK / BOTTOM ANALYSIS\n"; separate();
    cout << "Type: [1] Income   [2] Expense\n"; int type = input_int(1, 2);
    cout << "Mode: [1] Peak (Max) [2] Bottom (Min)\n"; int mode = input_int(1, 2);

    long long (*cache)[13] = new long long[3001][13];

    // Init 0
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
        cout << "=> No data available.\n";
        delete[] cache; pause(); return;
    }

    long long target_val = (mode == 1) ? -1 : LLONG_MAX;
    int res_m = 0, res_y = 0;

    for(int y=1900; y<=3000; y++){
        for(int m=1; m<=12; m++){
            long long val = cache[y][m];
            if(val > 0) {
                if(mode == 1) { // Peak
                    if(val > target_val) { target_val = val; res_y = y; res_m = m; }
                } else { // Bottom
                    if(val < target_val) { target_val = val; res_y = y; res_m = m; }
                }
            }
        }
    }

    separate();
    string s_type = (type == 1) ? "Income" : "Expense";
    string s_mode = (mode == 1) ? "Peak (Highest)" : "Bottom (Lowest)";

    if(res_y != 0) {
        cout << s_mode << " " << s_type << " Month: "
             << res_m << "/" << res_y << "\n";
        cout << "Total Amount: " << target_val << "\n";
    } else {
        cout << "=> No transactions found.\n";
    }

    delete[] cache;
    pause();
}

// 7. Most valuable in range
void stats_most_valuable_in_range() {
    clear_screen(); separate(); cout << "HIGHEST SINGLE TRANSACTION\n"; separate();
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

    separate();
    if (idx != -1) {
        cout << "Found Transaction:\n";
        Transaction& res = event.get_val(idx);
        output_date(res.date);
        cout << "Amount: " << res.amount << "\n";
        cout << "Wallet: " << (res.wallet_id ? wallet.get_string(res.wallet_id) : "N/A") << "\n";
        string src = (type == 1) ? income.get_string(res.source_id) : expense.get_string(res.source_id);
        cout << "Source: " << src << "\n";
        cout << "Note  : " << res.description << "\n";
    } else {
        cout << "=> No transaction found in this range.\n";
    }
    pause();
}
