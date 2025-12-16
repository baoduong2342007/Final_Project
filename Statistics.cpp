#include <iostream>
#include "Statistics.h"
#include "Global.h"

using namespace std;

// helpers

bool Statistics::inRange(Date d, Date from, Date to) {
    if (compare_date(from, to) > 0) return false;
    return compare_date(from, d) <= 0 && compare_date(d, to) <= 0;
}
static void printSummary(long long income, long long expense) {
    cout << "Total income : " << income << "\n";
    cout << "Total expense: " << expense << "\n";
    cout << "Net balance  : " << income - expense << "\n";
}

// basic summary

void Statistics::incomeExpenseSummary(Date from, Date to) {
    long long income = 0, expense = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (inRange(t.date, from, to)) {
            if (t.source == 1) income += t.amount;
            else expense += t.amount;
        }
    }
    cout << "Statistics from ";
    output_date(from);
    cout << "to ";
    output_date(to);
    printSummary(income, expense);
}
// yearly overview
void Statistics::yearlyOverview(int year) {
    long long income = 0, expense = 0;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (t.date.year == year) {
            if (t.source == 1) income += t.amount;
            else expense += t.amount;
        }
    }
    cout << "Statistics for year " << year << ":\n";
    printSummary(income, expense);
}
void Statistics::incomeBySource(int year) {
    Dynamic_array<Trie_node*> sources = income.get_arr_id();
    int n = sources.cur_n;
    if (n == 0) {
        cout << "No income sources\n";
        return;
    }
    long long* sum = new long long[n];
    for (int i = 0; i < n; i++) sum[i] = 0;
    // accumulate
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i); // loop i for transaction list, j for income list
        if (t.source == 1 && t.date.year == year) {
            for (int j = 0; j < n; j++) {
                if (sources.get_val(j) == t.source_id) {
                    sum[j] += t.amount;
                    break;
                }
            }
        }
    }
    cout << "Income by source in year " << year << ":\n";
    for (int i = 0; i < n; i++) {
        if (sum[i] > 0) {
            cout << "- "
                << income.get_string(sources.get_val(i))
                << " : " << sum[i] << "\n";
        }
    }
    delete[] sum;
    sources.clear_all();
}
void Statistics::expenseBySource(int year) {
    Dynamic_array<Trie_node*> sources = expense.get_arr_id();
    int n = sources.cur_n;
    if (n == 0) {
        cout << "No expense categories\n";
        return;
    }
    long long* sum = new long long[n];
    for (int i = 0; i < n; i++) sum[i] = 0;
    // accumulate 
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (t.source == 2 && t.date.year == year) {
            for (int j = 0; j < n; j++) {
                if (sources.get_val(j) == t.source_id) {
                    sum[j] += t.amount;
                    break;
                }
            }
        }
    }
    cout << "Expense by category in year " << year << ":\n";
    for (int i = 0; i < n; i++) {
        if (sum[i] > 0) {
            cout << "- "
                << expense.get_string(sources.get_val(i))
                << " : " << sum[i] << "\n";
        }
    }
    delete[] sum;
    sources.clear_all();
}

// peak/bottom of whole list
void Statistics::peakIncomeMonth() {
    long long best = -1;
    int bestY = 0, bestM = 0;
    for (int y = 1900; y <= 2100; y++) {
        for (int m = 1; m <= 12; m++) {
            long long sum = 0;
            bool exist = false;
            for (int i = 0; i < event.cur_n; i++) {
                Transaction t = event.get_val(i);
                if (t.date.year == y && t.date.month == m) {
                    exist = true;
                    if (t.source == 1) sum += t.amount;
                }
            }
            if (exist && sum > best) {
                best = sum;
                bestY = y;
                bestM = m;
            }
        }
    }
    // too many loops
    if (best >= 0)
        cout << "Peak income month: " << bestM << "/" << bestY
        << " with amount " << best << "\n";
    else
        cout << "No income data\n";
}
void Statistics::bottomIncomeMonth() {
    long long worst = -1;
    int worstY = 0, worstM = 0;
    for (int y = 1900; y <= 2100; y++) {
        for (int m = 1; m <= 12; m++) {
            long long sum = 0;
            bool exist = false;

            for (int i = 0; i < event.cur_n; i++) {
                Transaction t = event.get_val(i);
                if (t.date.year == y && t.date.month == m) {
                    exist = true;
                    if (t.source == 1) sum += t.amount;
                }
            }

            if (exist && (worst == -1 || sum < worst)) {
                worst = sum;
                worstY = y;
                worstM = m;
            }
        }
    }
    if (worst >= 0)
        cout << "Bottom income month: " << worstM << "/" << worstY
        << " with amount " << worst << "\n";
    else
        cout << "No income data\n";
}
void Statistics::peakExpenseMonth() {
    long long best = -1;
    int bestY = 0, bestM = 0;
    for (int y = 1900; y <= 2100; y++) {
        for (int m = 1; m <= 12; m++) {
            long long sum = 0;
            bool exist = false;

            for (int i = 0; i < event.cur_n; i++) {
                Transaction t = event.get_val(i);
                if (t.date.year == y && t.date.month == m) {
                    exist = true;
                    if (t.source == 2) sum += t.amount;
                }
            }

            if (exist && sum > best) {
                best = sum;
                bestY = y;
                bestM = m;
            }
        }
    }
    if (best >= 0)
        cout << "Peak expense month: " << bestM << "/" << bestY
        << " with amount " << best << "\n";
    else
        cout << "No expense data\n";
}
void Statistics::bottomExpenseMonth() {
    long long worst = -1;
    int worstY = 0, worstM = 0;
    for (int y = 1900; y <= 2100; y++) {
        for (int m = 1; m <= 12; m++) {
            long long sum = 0;
            bool exist = false;

            for (int i = 0; i < event.cur_n; i++) {
                Transaction t = event.get_val(i);
                if (t.date.year == y && t.date.month == m) {
                    exist = true;
                    if (t.source == 2) sum += t.amount;
                }
            }
            if (exist && (worst == -1 || sum < worst)) {
                worst = sum;
                worstY = y;
                worstM = m;
            }
        }
    }
    if (worst >= 0)
        cout << "Bottom expense month: " << worstM << "/" << worstY
        << " with amount " << worst << "\n";
    else
        cout << "No expense data\n";
}
// valuable transactions
Transaction Statistics::mostValuableIncome(Date from, Date to) {
    Transaction best;
    long long maxAmount = -1;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (t.source == 1 && inRange(t.date, from, to)) {
            if (t.amount > maxAmount) {
                maxAmount = t.amount;
                best = t;
            }
        }
    }
    return best; // amount == 0 if none found
}
Transaction Statistics::mostValuableExpense(Date from, Date to) {
    Transaction best;
    long long maxAmount = -1;
    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (t.source == 2 && inRange(t.date, from, to)) {
            if (t.amount > maxAmount) {
                maxAmount = t.amount;
                best = t;
            }
        }
    }
    return best; // amount == 0 if none found
}
void Statistics::list_valuable_transactions(long long amount) {
    bool found = false;
    cout << "Transactions with amount at least " << amount << ":\n";

    for (int i = 0; i < event.cur_n; i++) {
        Transaction t = event.get_val(i);
        if (t.amount >= amount) {
            found = true;
            cout << "----------------------------------\n";
            cout << (t.source == 1 ? "Income\n" : "Expense\n");
            output_date(t.date);
            cout << "Amount      : " << t.amount << "\n";
            cout << "Wallet      : " << wallet.get_string(t.wallet_id) << "\n";
            if (t.source == 1)
                cout << "Source      : " << income.get_string(t.source_id) << "\n";
            else
                cout << "Category    : " << expense.get_string(t.source_id) << "\n";
            cout << "Description : " << t.description << "\n";
        }
    }
    if (!found) {
        cout << "No transaction matches this condition.\n";
    }
}

