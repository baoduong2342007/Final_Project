#pragma once
#include "Global.h"

// Helper
bool in_range(Date d, Date from, Date to);

// 1. Income / Expense summary (date range)
void stats_range_summary();

// 2. Yearly overview
void stats_yearly_overview();

// 3 & 4. List income/expense by source in a year
void stats_by_source(int source_type); // 1 = Income, 2 = Expense

// 5. List transactions with amount at least given amount
void stats_list_valuable();

// 6. Peak / bottom of income / expense in history
void stats_peak_bottom();

// 7. Most valuable income / expense (date range)
void stats_most_valuable_in_range();
