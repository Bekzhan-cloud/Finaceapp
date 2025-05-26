#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account {
private:
    string name;
    double balance;
    int id;
    static int nextId;

public:
    Account(const string& name, double initialBalance = 0.0);
    Account(int id, const string& name, double balance); 

    void deposit(double amount);
    bool withdraw(double amount);
    void display() const;

    double getBalance() const;
    string getName() const;
    int getId() const;

    string toString() const;

    static void setNextId(int id);
};

#endif
