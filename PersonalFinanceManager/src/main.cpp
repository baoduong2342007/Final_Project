#include "../include/Global.h"
#include "../include/Data_Persistence.h"
#include "../include/Master_Data_Management.h"
#include "../include/Transaction_Management.h"
#include "../include/Recurring_Management.h"
#include "../include/Statistics_Management.h"

using namespace std;

int main(){
    load();
    apply_recurring_transaction();
    save();
    cout << BLUE;
    while (true){
        check_financial_health();
        clear_screen();
        separate(); cout << CYAN << "PERSONAL FINANCE MANAGER \n" << BLUE;
        big_separate();
        show_dashboard();
        separate();
        cout << "[0] Exit & Save\n";
        cout << "[1] Manage Master Data\n";
        cout << "[2] Manage Transactions\n";
        cout << "[3] Manage Recurring\n";
        cout << "[4] Statistics & Reports\n";
        separate();
        int t = input_int(0 , 4);
        if (t == 0) break;
        if (t == 1) manage_master_data();
        if (t == 2) manage_transaction();
        if (t == 3) {
            manage_recurring();
            apply_recurring_transaction();
            save();
        }
        if (t == 4) manage_statistics();
    }
    save();
    clear_all();
    cout << RESET;
    return 0;
}
