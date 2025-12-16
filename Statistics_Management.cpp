#include <iostream>
#include "Statistics_Management.h"
#include "Statistics.h"
#include "Global.h"

using namespace std;

void manage_statistics() {
    Statistics st;
    int t;
    while (true) {
        separate();
        cout << "STATISTICS MENU\n";
        cout << "0. Back\n";
        cout << "1. Income / Expense summary (date range)\n";
        cout << "2. Yearly overview\n";
        cout << "3. List income by source in a year\n";
        cout << "4. List expense by category in a year\n";
        cout << "5. List transactions with amount at least given amount\n";
        cout << "6. Peak / bottom of income / expense in history\n";
        cout << "7. Most valuable income / expense (date range)\n";
        cout << "Choose: ";
        cin >> t;
        if (t == 0) break;
        if (t == 1) {
            Date from, to;
            cout << "From ";
            input_date(from);
            cout << "To ";
            input_date(to);
            st.incomeExpenseSummary(from, to);
        }
        if (t == 2) {
            int year;
            cout << "Year: ";
            cin >> year;
            st.yearlyOverview(year);
        }
        if (t == 3) {
            int year;
            cout << "Year: ";
            cin >> year;
            st.incomeBySource(year);
        }
        if (t == 4) {
            int year;
            cout << "Year: ";
            cin >> year;
            st.expenseBySource(year);
        }
        if (t == 5) {
            long long amount;
            cout << "Minimum amount: ";
            cin >> amount;
            st.list_valuable_transactions(amount);
        }
        if (t == 6) {
            int type, mode;
            separate();
            cout << "1) Income\n";
            cout << "2) Expense\n";
            cout << "Choose type: ";
            cin >> type;
            cout << "1) Peak\n";
            cout << "2) Bottom\n";
            cout << "Choose mode: ";
            cin >> mode;
            if (type == 1 && mode == 1) st.peakIncomeMonth();
            if (type == 1 && mode == 2) st.bottomIncomeMonth();
            if (type == 2 && mode == 1) st.peakExpenseMonth();
            if (type == 2 && mode == 2) st.bottomExpenseMonth();
        }
        if (t == 7) {
            Date from, to;
            cout << "From ";
            input_date(from);
            cout << "To ";
            input_date(to);
            int type;
            cout << "1) Income\n";
            cout << "2) Expense\n";
            cout << "Choose type: ";
            cin >> type;
            Transaction res;
            if (type == 1) {
                res = st.mostValuableIncome(from, to);
                if (res.amount == 0) {
                    cout << "No income transaction found\n";
                }
                else {
                    cout << "Most valuable income:\n";
                    output_date(res.date);
                    cout << "Amount: " << res.amount << "\n";
                    cout << "Wallet: " << wallet.get_string(res.wallet_id) << "\n";
                    cout << "Source: " << income.get_string(res.source_id) << "\n";
                }
            }
            else {
                res = st.mostValuableExpense(from, to);
                if (res.amount == 0) {
                    cout << "No expense transaction found\n";
                }
                else {
                    cout << "Most valuable expense:\n";
                    output_date(res.date);
                    cout << "Amount: " << res.amount << "\n";
                    cout << "Wallet: " << wallet.get_string(res.wallet_id) << "\n";
                    cout << "Category: " << expense.get_string(res.source_id) << "\n";
                }
            }
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
