#include "Category.h"
#include <sstream>
#include <iostream>
using namespace std;

int Category::nextId = 1;
vector<Category> Category::incomeCategories = {
    Category("Зарплата"),
    Category("Подарки"),
    Category("Инвестиции"),
    Category("Прочее")
};
vector<Category> Category::expenseCategories = {
    Category("Еда"),
    Category("Транспорт"),
    Category("Развлечения"),
    Category("Коммунальные услуги"),
    Category("Прочее")
};

// Конструкторы
Category::Category(const string& name) : id(nextId++), name(name) {}
Category::Category(int id, const string& name) : id(id), name(name) {}

// Методы экземпляра
int Category::getId() const {
    return id;
}

string Category::getName() const {
    return name;
}

void Category::setName(const string& newName) {
    name = newName;
}

string Category::toString() const {
    ostringstream stream;
    stream << id << ";" << name;
    return stream.str();
}

Category Category::fromString(const string& line) {
    istringstream stream(line);
    string token;
    int id;
    string name;

    getline(stream, token, ';');
    id = stoi(token);

    getline(stream, name);

    return Category(id, name);
}

void Category::setNextId(int id) {
    nextId = id;
}

// Статические методы для управления категориями
const vector<Category>& Category::getIncomeCategories() {
    return incomeCategories;
}

const vector<Category>& Category::getExpenseCategories() {
    return expenseCategories;
}

void Category::addIncomeCategory(const string& name) {
    incomeCategories.emplace_back(name);
}

void Category::addExpenseCategory(const string& name) {
    expenseCategories.emplace_back(name);
}

void Category::removeIncomeCategory(int index) {
    if (index >= 0 && index < (int)incomeCategories.size()) {
        incomeCategories.erase(incomeCategories.begin() + index);
    }
}

void Category::removeExpenseCategory(int index) {
    if (index >= 0 && index < (int)expenseCategories.size()) {
        expenseCategories.erase(expenseCategories.begin() + index);
    }
}