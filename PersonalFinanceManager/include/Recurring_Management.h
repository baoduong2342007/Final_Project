#pragma once

// Apply recurring templates to generate real transactions
void apply_recurring_transaction();

RecurringTransaction input_recurring();

void add_recurring(RecurringTransaction &X);

// Recurring transaction menu (add / delete / list / search)
void manage_recurring();
