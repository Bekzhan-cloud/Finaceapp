#include "Budget.h"
#include <iostream>
#include <iomanip>

void Budget::setBudget(const string& category, double amount) {
    categoryBudgets[category] = amount;
    if (categoryExpenses.find(category) == categoryExpenses.end()) {
        categoryExpenses[category] = 0.0;
    }
}

double Budget::getBudget(const string& category) const {
    auto it = categoryBudgets.find(category);
    return (it != categoryBudgets.end()) ? it->second : 0.0;
}

void Budget::addExpense(const string& category, double amount) {
    categoryExpenses[category] += amount;
}

double Budget::getRemainingBudget(const string& category) const {
    double budget = getBudget(category);
    double expenses = categoryExpenses.at(category);
    return budget - expenses;
}

bool Budget::isBudgetExceeded(const string& category) const {
    return getRemainingBudget(category) < 0;
}

void Budget::displayBudgets() const {
    cout << setw(20) << "Категория" << setw(15) << "Бюджет" << setw(15) << "Расходы" << setw(15) << "Остаток" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto& pair : categoryBudgets) {
        const string& category = pair.first;
        double budget = pair.second;
        double expenses = categoryExpenses.at(category);
        double remaining = budget - expenses;
        cout << setw(20) << category << setw(15) << budget << setw(15) << expenses << setw(15) << remaining << endl;
    }
}