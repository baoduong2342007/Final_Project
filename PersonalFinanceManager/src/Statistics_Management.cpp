#include <iostream>
#include "../include/Statistics_Management.h"
#include "../include/Statistics.h"
#include "../include/Global.h"

using namespace std;

void manage_statistics() {
    while (true) {
        clear_screen();
        separate();
        cout << CYAN << "STATISTICS MENU\n";
        separate();
        cout << "[0] Back\n";
        cout << "[1] Income / Expense summary (Date Range)\n";
        cout << "[2] Yearly overview\n";
        cout << "[3] List Income by Source (Yearly)\n";
        cout << "[4] List Expense by Category (Yearly)\n";
        cout << "[5] List transactions >= Amount\n";
        cout << "[6] Peak / Bottom month in history\n";
        cout << "[7] Highest value transaction (Date Range)\n";
        separate();

        int t = input_int(0, 7);

        if (t == 0) break;
        if (t == 1) stats_range_summary();
        if (t == 2) stats_yearly_overview();
        if (t == 3) stats_by_source(1); // 1 = Income
        if (t == 4) stats_by_source(2); // 2 = Expense
        if (t == 5) stats_list_valuable();
        if (t == 6) stats_peak_bottom();
        if (t == 7) stats_most_valuable_in_range();
    }
}
