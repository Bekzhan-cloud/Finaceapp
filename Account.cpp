#include "Account.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <locale>
#include "UI.h"
#include <iomanip> 

int Account::nextId = 1;

Account::Account(const string& name, double initialBalance)
    : name(name), balance(initialBalance), id(nextId++) {}

Account::Account(int id, const string& name, double balance)
    : id(id), name(name), balance(balance) {}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "На счёт '" << name << "' добавлено " << fixed << setprecision(2) << amount << " руб." << endl;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Снято " << fixed << setprecision(2) << amount << " руб. со счёта '" << name << "'" << endl;
        return true;
    }
    else {
        cout << "Недостаточно средств." << endl;
        return false;
    }
}

void Account::display() const {
    cout << "[ID: " << id << "] " << name << " | Баланс: " << fixed << setprecision(2) << balance << " руб." << endl;
}

double Account::getBalance() const { return balance; }
string Account::getName() const { return name; }
int Account::getId() const { return id; }

string Account::toString() const {
    stringstream ss;
    ss << id << ";" << name << ";" << fixed << setprecision(2) << balance;
    return ss.str();
}

void Account::setNextId(int id) {
    nextId = id;
}
