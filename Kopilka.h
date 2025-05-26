#pragma once
#include <string>
using namespace std;
class AccountManager;

class Kopilka {
private:
    double balance;
    string filename;

public:
    Kopilka(const string& filename = "Kopilka.txt");
    void deposit(double amount); 
    bool withdraw(double amount);
    double getBalance() const;
    void display() const;
    void save() const;
    void load();

    
    bool transferFromAccount(AccountManager& accountMgr, int accountId, double amount);
    bool transferToAccount(AccountManager& accountMgr, int accountId, double amount);
};
