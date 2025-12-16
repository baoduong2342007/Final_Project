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
    cout << flush;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Safe input

void resetInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int safe_input_int(int l , int r){
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

long long safe_input_long_long(long long x){
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

string safe_input_string(){
    cout << ">> Enter : ";
    string s; getline(cin , s);
    return s;
    resetInputStream();
}

// Clear all

void clear_all(){
    event.clear_all();
    wallet.clear_all();
    income.clear_all();
    expense.clear_all();
}
