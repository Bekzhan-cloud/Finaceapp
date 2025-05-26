#include "ExportReport.h"
#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
// Вспомогательная функция сравнения дат в формате "YYYY-MM-DD"
bool isDateInRange(const string& date, const string& start, const string& end) {
    return (date >= start && date <= end);
}

bool ExportReport::exportTransactionsToCSV(const TransactionManager& transactionMgr, 
                                           const string& filename,
                                           const string& startDate,
                                           const string& endDate) {
    ifstream fileIn("transactions.txt");
    if (!fileIn.is_open()) {
        cout << "Не удалось открыть файл транзакций для экспорта.\n";
        return false;
    }

    ofstream fileOut(filename, ios::trunc);
    if (!fileOut.is_open()) {
        cout << "Не удалось создать файл для экспорта.\n";
        return false;
    }

    fileOut << "ID;Счет;Сумма;Тип;Категория;Дата;Комментарий\n";

    string line;
    while (getline(fileIn, line)) {
        Transaction* t = Transaction::fromString(line);
        if (t) {
            string date = t->getDate();
            if (isDateInRange(date, startDate, endDate)) {
                string comment = t->getComment();
                for (char& c : comment) if (c == ';') c = ',';

                fileOut << t->getId() << ";"
                        << t->getAccountId() << ";"
                        << t->getAmount() << ";"
                        << t->getType() << ";"
                        << t->getCategory() << ";"
                        << t->getDate() << ";"
                        << comment << "\n";
            }
            delete t;
        }
    }

    fileIn.close();
    fileOut.close();
    cout << "Экспорт завершён! Файл: " << filename << endl;
    return true;
}