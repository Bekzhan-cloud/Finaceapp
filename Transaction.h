#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;
class Transaction {
protected:
    int id;
    int accountId;
    double amount;
    string category;
    string date;
    string comment;
    static int nextId;

    
    Transaction(int id, int accountId, double amount, const string& category,
                const string& date, const string& comment);
    Transaction(int accountId, double amount, const string& category,
                const string& date, const string& comment);

public:
    virtual ~Transaction() = default;

    virtual string getType() const = 0;
    virtual void display() const = 0;
    virtual string toString() const = 0;

    int getId() const;
    int getAccountId() const;
    double getAmount() const;
    string getCategory() const;
    string getDate() const;
    string getComment() const;

    static void setNextId(int newId);
    static int getNextId();

    static Transaction* fromString(const string& line);
};

class Income : public Transaction {
public:
    Income(int id, int accountId, double amount, const string& category,
           const string& date, const string& comment)
        : Transaction(id, accountId, amount, category, date, comment) {}

    Income(int accountId, double amount, const string& category,
           const string& date, const string& comment)
        : Transaction(accountId, amount, category, date, comment) {}

    string getType() const override { return "доход"; }
    void display() const override;
    string toString() const override;
};

class Expense : public Transaction {
public:
    Expense(int id, int accountId, double amount, const string& category,
            const string& date, const string& comment)
        : Transaction(id, accountId, amount, category, date, comment) {}

    Expense(int accountId, double amount, const string& category,
            const string& date, const string& comment)
        : Transaction(accountId, amount, category, date, comment) {}

    string getType() const override { return "расход"; }
    void display() const override;
    string toString() const override;
};

#endif