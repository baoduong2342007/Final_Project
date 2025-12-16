#include "Global.h"
#include "Data_Persistence.h"
#include "Master_Data_Management.h"
#include "Transaction_Management.h"
#include "Recurring_Management.h"
#include "Statistics_Management.h"
using namespace std;

// cap nhat main sau nhe

int main(){
    load();
    apply_recurring_transactions();
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
        cout << "2) Manage transactions\n";
        cout << "3) Manage recurring transactions\n";
        cout << "4) View statistics\n";
        cout << "Choose : "; cin >> t;
        if (t == 0) break;
        if (t == 1) manage_master_data();
        if (t == 2) manage_transaction();
        if (t == 3) manage_recurring();
        if (t == 4) manage_statistics();
    }
    clear_all();
    return 0;
}
