#include "Global.h"

using namespace std;

Dynamic_array<Transaction> event;
Trie wallet;
Trie income;
Trie expense;

//UI

void separate(){
    cout << "==========================================\n";
}

void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "=> Type enter to continue...\n";
    cin.get();
}

// Safe input

void resetInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int input_int(int l , int r){
    int t;
    while (true){
        cout << ">> Enter : ";
        if (cin >> t){
            if (l <= t && t <= r){
                resetInputStream();
                return t;
            }
            else{
                resetInputStream();
                cout << "Invalid input! Please enter an integer number from " << l << " to " << r << ".\n";
                cout << "=> Try again :\n";
            }
        }
        else{
            resetInputStream();
            cout << "Invalid input! Please enter an integer number from " << l << " to " << r << ".\n";
            cout << "=> Try again :\n";
        }
    }
}

long long input_long_long(long long x){
    long long t;
    while (true){
        cout << ">> Enter : ";
        if (cin >> t){
            if (t >= x){
                resetInputStream();
                return t;
            }
            else{
                resetInputStream();
                cout << "Invalid input! Please enter an integer number from >= " << x << ".\n";
                cout << "=> Try again :\n";
            }
        }
        else{
            resetInputStream();
            cout << "Invalid input! Please enter an integer number from >= " << x << ".\n";
            cout << "=> Try again :\n";
        }
    }
}

string input_string(){
    cout << ">> Enter : ";
    string s; getline(cin , s);
    return s;
}

Date input_date(){
    //format day/month/year
    string s;
    Date X;
    while (true){
        cout << ">> Enter : ";
        s.clear(); getline(cin , s);
        //
        bool check = true;
        int n = int(s.size());
        int cnt = 0; // number of '/'
        for (int i = 0 ; i < n ; i++){
            if (s[i] == '/') cnt++;
        }
        //
        if (cnt != 2) check = false;
        else{
            int x = -1 , y = -1;
            for (int i = 0 ; i < n ; i++){
                if (s[i] == '/'){
                    if (x == -1) x = i; else y = i;
                }
            }
            // day
            X.day = 0;
            for (int i = 0 ; i < x ; i++){
                if ('0' <= s[i] && s[i] <= '9'){
                    X.day = X.day * 10 + (s[i] - '0');
                }
                else{
                    check = false;
                    break;
                }
            }
            // month
            X.month = 0;
            for (int i = x + 1 ; i < y ; i++){
                if ('0' <= s[i] && s[i] <= '9'){
                    X.month = X.month * 10 + (s[i] - '0');
                }
                else{
                    check = false;
                    break;
                }
            }
            // year
            for (int i = y + 1 ; i < n ; i++){
                if ('0' <= s[i] && s[i] <= '9'){
                    X.year = X.year * 10 + (s[i] - '0');
                }
                else{
                    check = false;
                    break;
                }
            }
        }
        if (valid_date(X) == false) check = false;
        if (check == false){
            cout << "=> Invalid input! Please enter the correct format.\n";
            cout << "=> Try again\n";
        }
        else{
            return X;
        }
    }
}

// Clear all

void clear_all(){
    event.clear_all();
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}
