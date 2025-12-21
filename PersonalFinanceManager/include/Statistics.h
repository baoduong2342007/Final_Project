#pragma once

#include "Date.h"
#include "Transaction.h"

class Statistics {
public:
    // Check if date d is in [from, to]
    bool inRange(Date d, Date from, Date to);

    // Total income / expense / net in a date range
    void incomeExpenseSummary(Date from, Date to);

    // Overview of a year
    void yearlyOverview(int year);
    void incomeBySource(int year);
    void expenseBySource(int year);

    // Peak / bottom months
    void peakIncomeMonth();
    void bottomIncomeMonth();
    void peakExpenseMonth();
    void bottomExpenseMonth();

    // Valuable transactions
    Transaction mostValuableIncome(Date from, Date to);
    Transaction mostValuableExpense(Date from, Date to);
    void list_valuable_transactions(long long amount);
};
