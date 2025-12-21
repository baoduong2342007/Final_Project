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
    cout << GREY << "=> Type enter to continue...\n" << BLUE;
    cin.get();
}

// Logic Dashboard
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
    cout << CYAN << "                DASHBOARD                \n";
    separate();
    cout << CYAN << " TOTAL BALANCE: " << get_total_balance() << "\n";
    separate();
    cout << CYAN << " WALLET BALANCES:\n";
    Dynamic_array<string> w_names = wallet.get_arr_string();
    Dynamic_array<Trie_node*> w_ids = wallet.get_arr_id();

    if (w_names.cur_n == 0) cout << " (No wallets created yet)\n";
    else {
        for(int i = 0; i < w_names.cur_n; i++){
            cout << " - " << w_names.get_val(i) << ": " << get_wallet_balance(w_ids.get_val(i)) << "\n";
        }
    }
    cout << BLUE;
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

        if (allow_empty && s.empty()) return Date(); // Tra ve ngay 0/0/0

        bool check = true;
        int n = int(s.size());
        int cnt = 0;
        for (int i=0; i<n; i++) if (s[i] == '/') cnt++;

        if (cnt != 2) check = false;
        else{
            int x = -1 , y = -1;
            for (int i=0; i<n; i++) if (s[i] == '/') { if(x==-1) x=i; else y=i; }
            X.day=0; for (int i=0; i<x; i++) if(isdigit(s[i])) X.day=X.day*10+(s[i]-'0'); else check=false;
            X.month=0; for (int i=x+1; i<y; i++) if(isdigit(s[i])) X.month=X.month*10+(s[i]-'0'); else check=false;
            X.year=0; for (int i=y+1; i<n; i++) if(isdigit(s[i])) X.year=X.year*10+(s[i]-'0'); else check=false;
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
