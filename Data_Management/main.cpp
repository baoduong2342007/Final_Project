#include <bits/stdc++.h>
#include "Global.h"
#include "Data_Persistence.h"
#include "Master_Data_Management.h"
#include "Transaction_Management.h"

using namespace std;

int main(){
    load();
    Dynamic_array<string> A = wallet.get_arr_string();
    cout << "wallet\n";
    for (int i = 0 ; i < A.cur_n ; i++){
        cout << i << " " << A.get_val(i) << "\n";
    }
    separate();
    A = income.get_arr_string();
    cout << "income\n";
    for (int i = 0 ; i < A.cur_n ; i++){
        cout << i << " " << A.get_val(i) << "\n";
    }
    separate();
    cout << "expense\n";
    A = expense.get_arr_string();
    for (int i = 0 ; i < A.cur_n ; i++){
        cout << i << " " << A.get_val(i) << "\n";
    }
    return 0;
    int t;
    while (true){
        separate();
        cout << "0) Exit the program\n";
        cout << "1) Manage master data\n";
        cout << "2) Manage transaction\n";
        cout << "Choose : "; cin >> t;
        if (t == 0) break;
        if (t == 1) manage_master_data();
        if (t == 2) manage_transaction();
    }
    clear_all();
    return 0;
}
