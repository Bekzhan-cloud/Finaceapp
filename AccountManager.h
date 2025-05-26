#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "Account.h"
#include <vector>

class AccountManager {
private:
    vector<Account> accounts;
    string filename;
    friend class TransactionManager; // доступ к приватным членам AccountManager

public:
    AccountManager(const string& filename = "accounts.txt");

    void loadAccounts();
    void saveAccounts() const;

    void addAccount();
    void showAccounts() const;
    bool depositToAccount(int accountId, double amount);
    bool withdrawFromAccount(int accountId, double amount);

    int findAccountIndexById(int id) const;
};

#endif

