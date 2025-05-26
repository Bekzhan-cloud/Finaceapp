#include "Transaction.h"
#include <iostream>
#include <sstream>
#include <iomanip>


int Transaction::nextId = 1;

// Фабрика для создания наследника по строке
Transaction* Transaction::fromString(const string& line) {
    istringstream stream(line);
    string token;
    int id, accountId;
    double amount;
    string type, category, date, comment;

    getline(stream, token, ';');
    id = stoi(token);

    getline(stream, token, ';');
    accountId = stoi(token);

    getline(stream, token, ';');
    amount = stod(token);

    getline(stream, type, ';');
    getline(stream, category, ';');
    getline(stream, date, ';');
    getline(stream, comment);

    if (line.find("доход") != string::npos)
        return new Income(id, accountId, amount, category, date, comment);
    else
        return new Expense(id, accountId, amount, category, date, comment);
}

// для новой транзакции
Transaction::Transaction(int accountId, double amount, const string& category,
    const string& date, const string& comment)
    : id(nextId++), accountId(accountId), amount(amount), category(category),
      date(date), comment(comment) {}

// ля существующей транзакции 
Transaction::Transaction(int id, int accountId, double amount, const string& category,
    const string& date, const string& comment)
    : id(id), accountId(accountId), amount(amount), category(category),
      date(date), comment(comment) {}


// Преобразование  в строку
string Transaction::toString() const {
    ostringstream stream;
    stream << id << ";" << accountId << ";" << fixed << setprecision(2) << amount << ";"
           << category << ";" << date << ";" << comment;
    return stream.str();
}

// информации о транзакции
void Transaction::display() const {
    cout << "ID: " << id << "\n"
              << "Счёт: " << accountId << "\n"
              << "Сумма: " << fixed << setprecision(2) << amount << "\n"
              << "Категория: " << category << "\n"
              << "Дата: " << date << "\n"
              //<< "Комментарий: " << comment << "\n"
              << "----------------------------\n";
}

int Transaction::getId() const { return id; }
int Transaction::getAccountId() const { return accountId; }
double Transaction::getAmount() const { return amount; }
string Transaction::getCategory() const { return category; }
string Transaction::getDate() const { return date; }
string Transaction::getComment() const { return comment; }
int Transaction::getNextId() {
    return nextId;
}
void Transaction::setNextId(int newId) {
    nextId = newId;
}

void Income::display() const {
    cout << "ID: " << id << "\nСчёт: " << accountId << "\nСумма: +" << fixed << setprecision(2) << amount
              << "\nТип: Доход\nКатегория: " << category << "\nДата: " << date << "\nКомментарий: " << comment
              << "\n----------------------------\n";
}

string Income::toString() const {
    ostringstream stream;
    stream << id << ";" << accountId << ";" << amount << ";доход;" << category << ";" << date << ";" << comment;
    return stream.str();
}

void Expense::display() const {
    cout << "ID: " << id << "\nСчёт: " << accountId << "\nСумма: -" << fixed << setprecision(2) << amount
              << "\nТип: Расход\nКатегория: " << category << "\nДата: " << date << "\nКомментарий: " << comment
              << "\n----------------------------\n";
}

string Expense::toString() const {
    ostringstream stream;
    stream << id << ";" << accountId << ";" << amount << ";расход;" << category << ";" << date << ";" << comment;
    return stream.str();
}
