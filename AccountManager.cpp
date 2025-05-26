#include "AccountManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <locale>
#include <codecvt>
using namespace std;

AccountManager::AccountManager(const string& filename) : filename(filename) {
    loadAccounts();
}

void AccountManager::loadAccounts() {
    ifstream file(filename, ios::binary);
    char bom[3] = {0};
    file.read(bom, 3);
    if (!(bom[0] == char(0xEF) && bom[1] == char(0xBB) && bom[2] == char(0xBF))) {
        file.seekg(0);
    }
    string line;
    int maxId = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, balanceStr;

        getline(ss, idStr, ';');
        getline(ss, name, ';');
        getline(ss, balanceStr);

        int id = stoi(idStr);
        double balance = stod(balanceStr);

        accounts.emplace_back(id, name, balance);
        if (id > maxId) maxId = id;
    }

    Account::setNextId(maxId + 1);
}

void AccountManager::saveAccounts() const {
    ofstream file(filename, ios::binary | ios::trunc);
    if (file.tellp() == 0) {
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        file.write(reinterpret_cast<char*>(bom), sizeof(bom));
    }
    for (const auto& acc : accounts) {
        file << acc.toString() << endl;
    }
}

void AccountManager::addAccount() {
    string name;
    double initialBalance;

    cout << "Введите название нового счёта: ";
    cin.ignore();
    getline(cin, name);

    
    if (name.empty()) {
        cout << "Название счёта не может быть пустым!\n";
        return;
    }

    cout << "Введите начальный баланс: ";
    cin >> initialBalance;

    accounts.emplace_back(name, initialBalance);
    saveAccounts();
    cout << "Счёт успешно добавлен.\n";
}

void AccountManager::showAccounts() const {
    if (accounts.empty()) {
        cout << "Нет доступных счетов.\n";
        return;
    }
    cout << "\nСписок счетов:\n";
    for (const auto& acc : accounts) {
        acc.display();
    }
}

int AccountManager::findAccountIndexById(int id) const {

    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getId() == id) return i;
    }
    return -1;
}
/*
void AccountManager::depositToAccount() {
    int id;
    double amount;
    showAccounts();
    cout << "Введите ID счёта для пополнения: ";
    cin >> id;
    cout << "Введите сумму: ";
    cin >> amount;

    int idx = findAccountIndexById(id);
    if (idx != -1) {
        accounts[idx].deposit(amount);
        saveAccounts();
        cout << "Счёт пополнен.\n";
    }
    else {
        cout << "Счёт не найден.\n";
    }
}

void AccountManager::withdrawFromAccount() {
    int id;
    double amount;
    showAccounts();
    cout << "Введите ID счёта для снятия: ";
    cin >> id;
    cout << "Введите сумму: ";
    cin >> amount;

    int idx = findAccountIndexById(id);
    if (idx != -1) {
        accounts[idx].withdraw(amount);
        saveAccounts();
        cout << "Со счета снято: " << amount << "\n";
    }
    else {
        cout << "Счёт не найден.\n";
    }
}
*/
bool AccountManager::depositToAccount(int accountId, double amount) {
    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {
            acc.deposit(amount);
            saveAccounts();
            return true;
        }
    }
    return false;
}

bool AccountManager::withdrawFromAccount(int accountId, double amount) {
    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {
            if (acc.withdraw(amount)) {
                saveAccounts();
                return true;
            }
            return false;
        }
    }
    return false;
}
