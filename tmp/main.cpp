#include <bits/stdc++.h>
#include "Global.h"
#include "Data_Persistence.h"
#include "Master_Data_Management.h"
#include "Transaction_Management.h"

using namespace std;

int main(){
    load();
    while (true){
        clear_screen();
        separate();
        cout << "PERSONAL FINANCE MANAGER \n";
        separate();
        cout << "[0] Exit & Save\n";
        cout << "[1] Manage Master Data\n";
        cout << "[2] Manage Transactions\n";
        separate();
        int t = input_int(0 , 2);
        if (t == 0) break;
        if (t == 1) manage_master_data();
        if (t == 2) manage_transaction();
    }
    save();
    clear_all();
    return 0;
}
