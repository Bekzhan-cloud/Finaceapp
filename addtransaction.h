#ifndef addTransaction_h
#define addTransaction_h

#include <vector>
#include "Transaction.h"

class AccountManager;
class Budget;

class TransactionManager {
private:
    vector<Transaction*> transactions;

public:
    ~TransactionManager(); 
    void addTransaction(AccountManager& accountMgr, Budget& budget);
    void showAllTransactions();
    //void loadFromFile();
    //void saveToFile();
};

#endif