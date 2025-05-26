#include "Kopilka.h"
#include "AccountManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
Kopilka::Kopilka(const string& filename) : balance(0.0), filename(filename) {
    load();
}

void Kopilka::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        save();
    }
}

bool Kopilka::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        save();
        return true;
    }
    return false;
}

double Kopilka::getBalance() const {
    return balance;
}

void Kopilka::display() const {
    cout << "Баланс копилки: " << fixed << setprecision(2) << balance << " сомы.\n";
}

void Kopilka::save() const {
    ofstream file(filename);
    if (file.is_open()) {
        file << balance;
    }
}

void Kopilka::load() {
    ifstream file(filename);
    if (file.is_open()) {
        file >> balance;
    }
}

// Перевод с банковского счета в копилку
bool Kopilka::transferFromAccount(AccountManager& accountMgr, int accountId, double amount) {
    if (amount <= 0) return false;
    if (accountMgr.withdrawFromAccount(accountId, amount)) {
        deposit(amount);
        cout << "Переведено " << amount << " сом. со счета #" << accountId << " в копилку.\n";
        return true;
    } else {
        cout << "Недостаточно средств на счете или неверный счет.\n";
        return false;
    }
}

// Перевод из копилки на банковский счет
bool Kopilka::transferToAccount(AccountManager& accountMgr, int accountId, double amount) {
    if (amount <= 0) return false;
    if (withdraw(amount)) {
        if (accountMgr.depositToAccount(accountId, amount)) {
            cout << "Переведено " << amount << " coм. из копилки на счет #" << accountId << ".\n";
            return true;
        } else {
            
            deposit(amount);
            cout << "Ошибка зачисления на счет. Операция отменена.\n";
            return false;
        }
    } else {
        cout << "Недостаточно средств в копилке.\n";
        return false;
    }
}