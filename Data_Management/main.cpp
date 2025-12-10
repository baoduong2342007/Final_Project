#include <bits/stdc++.h>
#include "Global.h"

using namespace std;

void show_menu(){
    cout << "Menu : \n";
    cout << "0) Exit\n";
    cout << "1) Add or del wallet\n";
    cout << "2) Add or del income\n";
    cout << "3) Add or del expense\n";
}

int main(){
    int choice;
    while (true){
        show_menu();
        cin >> choice;
        if (choice == 1){
            cout << "0) Do nothing\n";
            cout << "1) Add\n";
            cout << "2) Del\n";
            string s; int t;
            cin >> t;
            if (t == 1){
                cout << "Name of string : ";
                cin >> s;
                wallet.ins(s);
            }
            if (t == 2){
                cout << "Name of string : ";
                cin >> s;
                if (wallet.exist(s) == false){
                    cout << "Name does not exist\n";
                }
                else{
                    wallet.del(s);
                }
            }
        }
        //Income voi Expense tuong tu the, tui hoi luoi code :)))))
        if (choice == 0) break;
    }
    clear_all();
    return 0;
}
