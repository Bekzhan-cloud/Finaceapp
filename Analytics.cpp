#include "Analytics.h"
#include "Transaction.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include <filesystem>

// Вспомогательная функция сравнения дат в формате "YYYY-MM-DD"
static bool isDateInRange(const string& date, const string& start, const string& end) {
    return (date >= start && date <= end);
}

void Analytics::showSummary(const TransactionManager& transactionMgr) const {
    double totalIncome = 0, totalExpense = 0;
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        Transaction* t = Transaction::fromString(line);
        if (t->getType() == "доход")
            totalIncome += t->getAmount();
        else
            totalExpense += t->getAmount();
        delete t;
    }
    cout << "\n--- Общая аналитика ---\n";
    cout << "Суммарные доходы:  " << fixed << setprecision(2) << totalIncome << endl;
    cout << "Суммарные расходы: " << fixed << setprecision(2) << totalExpense << endl;
    cout << "Баланс:            " << fixed << setprecision(2) << (totalIncome - totalExpense) << endl;
}

void Analytics::showSummaryPeriod(const TransactionManager& transactionMgr, const string& start, const string& end) const {
    double totalIncome = 0, totalExpense = 0;
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        Transaction* t = Transaction::fromString(line);
        string date = t->getDate();
        if (isDateInRange(date, start, end)) {
            if (t->getType() == "доход")
                totalIncome += t->getAmount();
            else
                totalExpense += t->getAmount();
        }
        delete t;
    }
    cout << "\n--- Общая аналитика за период " << start << " - " << end << " ---\n";
    cout << "Суммарные доходы:  " << fixed << setprecision(2) << totalIncome << endl;
    cout << "Суммарные расходы: " << fixed << setprecision(2) << totalExpense << endl;
    cout << "Баланс:            " << fixed << setprecision(2) << (totalIncome - totalExpense) << endl;
}

void Analytics::showCategoryStats(const TransactionManager& transactionMgr) const {
    map<string, double> incomeByCategory, expenseByCategory;
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        Transaction* t = Transaction::fromString(line);
        if (t->getType() == "доход")
            incomeByCategory[t->getCategory()] += t->getAmount();
        else
            expenseByCategory[t->getCategory()] += t->getAmount();
        delete t;
    }
    cout << "\n--- Доходы по категориям ---\n";
    for (const auto& pair : incomeByCategory)
        cout << pair.first << ": " << fixed << setprecision(2) << pair.second << endl;
    cout << "\n--- Расходы по категориям ---\n";
    for (const auto& pair : expenseByCategory)
        cout << pair.first << ": " << fixed << setprecision(2) << pair.second << endl;
}

void Analytics::showCategoryStatsPeriod(const TransactionManager& transactionMgr, const string& start, const string& end) const {
    map<string, double> incomeByCategory, expenseByCategory;
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        Transaction* t = Transaction::fromString(line);
        string date = t->getDate();
        if (isDateInRange(date, start, end)) {
            if (t->getType() == "доход")
                incomeByCategory[t->getCategory()] += t->getAmount();
            else
                expenseByCategory[t->getCategory()] += t->getAmount();
        }
        delete t;
    }
    cout << "\n--- Доходы по категориям за период " << start << " - " << end << " ---\n";
    for (const auto& pair : incomeByCategory)
        cout << pair.first << ": " << fixed << setprecision(2) << pair.second << endl;
    cout << "\n--- Расходы по категориям за период " << start << " - " << end << " ---\n";
    for (const auto& pair : expenseByCategory)
        cout << pair.first << ": " << fixed << setprecision(2) << pair.second << endl;
}