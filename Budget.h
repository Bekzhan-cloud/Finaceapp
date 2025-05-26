#pragma once

#ifndef BUDGET_H
#define BUDGET_H

#include <string>
#include <unordered_map>
using namespace std;
class Budget {
private:
    unordered_map<string, double> categoryBudgets; // Бюджет для каждой категории
    unordered_map<string, double> categoryExpenses; // Текущие расходы по категориям

public:
    void setBudget(const string& category, double amount);
    double getBudget(const string& category) const;
    void addExpense(const string& category, double amount);
    double getRemainingBudget(const string& category) const;
    bool isBudgetExceeded(const string& category) const;
    void displayBudgets() const;
};

#endif
