#include "Global.h"
using namespace std;

Dynamic_array<Transaction> event;
Dynamic_array<RecurringTransaction> auto_event;
Trie wallet;
Trie income;
Trie expense;

void separate(){ cout << YELLOW << "==========================================\n" << BLUE; }
void big_separate(){ cout << YELLOW << "====================================================================\n" << BLUE; }

void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << GREY << "=> Press Enter to continue...\n" << BLUE;
    cin.get();
}

string format_money(long long money) {
    string s = to_string(abs(money));
    int insertPosition = s.length() - 3;
    while (insertPosition > 0) {
        s.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    if (money < 0) return "-" + s;
    return s + " VND";
}

string truncate_text(string s, int width) {
    if ((int)s.length() > width) {
        return s.substr(0, width - 3) + "...";
    }
    return s;
}

long long get_wallet_balance(Trie_node* w_id) {
    long long total = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction &t = event.get_val(i);
        if (t.wallet_id == w_id) {
            if (t.source == 1) total += t.amount;
            else total -= t.amount;
        }
    }
    return total;
}

long long get_total_balance() {
    long long total = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction &t = event.get_val(i);
        if (t.source == 1) total += t.amount;
        else total -= t.amount;
    }
    return total;
}

void show_dashboard() {
    cout << CYAN << "                  DASHBOARD                  \n";
    big_separate();

    long long total = get_total_balance();
    string color = (total >= 0) ? GREEN : RED;
    cout << " TOTAL ASSETS: " << color << format_money(total) << BLUE << "\n";

    separate();

    cout << CYAN << " WALLET DETAILS:\n" << BLUE;
    Dynamic_array<string> w_names = wallet.get_arr_string();
    Dynamic_array<Trie_node*> w_ids = wallet.get_arr_id();

    if (w_names.cur_n == 0) {
        cout << " (No wallets created yet)\n";
    } else {
        cout << left << setw(4) << "ID"
             << setw(20) << "Wallet Name"
             << right << setw(15) << "Balance" << "\n";
        cout << string(40, '-') << "\n";

        for(int i = 0; i < w_names.cur_n; i++){
            long long bal = get_wallet_balance(w_ids.get_val(i));
            string bal_color = (bal >= 0) ? GREEN : RED;

            cout << left << setw(4) << i
                 << setw(20) << truncate_text(w_names.get_val(i), 18)
                 << bal_color << right << setw(15) << format_money(bal) << BLUE << "\n";
        }
    }
}

void resetInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int input_int(int l , int r){
    int t;
    while (true){
        cout << GREY << ">> Enter : " << BLUE;
        if (cin >> t){
            if (l <= t && t <= r){ resetInputStream(); return t; }
            else { resetInputStream(); cout << RED << "Invalid (" << l << "-" << r << ")\n"; }
        } else { resetInputStream(); cout << RED << "Invalid input!\n"; }
    }
}

long long input_long_long(long long x){
    long long t;
    while (true){
        cout << GREY << ">> Enter : " << BLUE;
        if (cin >> t){
            if (t >= x){ resetInputStream(); return t; }
            else { resetInputStream(); cout << "Invalid (>= " << x << ")\n"; }
        } else { resetInputStream(); cout << "Invalid input!\n"; }
    }
}

string input_string(){
    cout << GREY << ">> Enter : " << BLUE;
    string s; getline(cin , s);
    return s;
}

Date input_date(bool allow_empty){
    string s; Date X;
    while (true){
        cout << GREY << (allow_empty ? ">> Enter (dd/mm/yyyy) or Enter to skip: " : ">> Enter (dd/mm/yyyy): ") << BLUE;
        s.clear(); getline(cin , s);

        if (allow_empty && s.empty()) return Date();

        bool check = true;
        int n = int(s.size());
        int cnt = 0;
        for (int i=0; i<n; i++) if (s[i] == '/') cnt++;

        if (cnt != 2) check = false;
        else{
            int x = -1 , y = -1;
            for (int i=0; i<n; i++) if (s[i] == '/') { if(x==-1) x=i; else y=i; }

            if(x == 0 || y == x+1 || y == n-1) check = false;
            else {
                X.day=0; for (int i=0; i<x; i++) if(isdigit(s[i])) X.day=X.day*10+(s[i]-'0'); else check=false;
                X.month=0; for (int i=x+1; i<y; i++) if(isdigit(s[i])) X.month=X.month*10+(s[i]-'0'); else check=false;
                X.year=0; for (int i=y+1; i<n; i++) if(isdigit(s[i])) X.year=X.year*10+(s[i]-'0'); else check=false;
            }
        }
        if (check && valid_date(X)) return X;
        cout << RED << "=> Invalid date!\n" << BLUE;
    }
}

void clear_all(){
    event.clear_all();
    auto_event.clear_all();
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}
