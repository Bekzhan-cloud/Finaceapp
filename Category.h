#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
using namespace std;
class Category {
private:
    int id;
    string name;
    static int nextId;

    
    static vector<Category> incomeCategories;
    static vector<Category> expenseCategories;

public:
    
    Category(const string& name);
    Category(int id, const string& name);

    
    int getId() const;
    string getName() const;
    void setName(const string& newName);
    string toString() const;
    static Category fromString(const string& line);

    static void setNextId(int id);

    
    static const vector<Category>& getIncomeCategories();
    static const vector<Category>& getExpenseCategories();
    static void addIncomeCategory(const string& name);
    static void addExpenseCategory(const string& name);
    static void removeIncomeCategory(int index);
    static void removeExpenseCategory(int index);
};

#endif
