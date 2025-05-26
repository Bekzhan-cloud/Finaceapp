#include "addTransaction.h"
#include "AccountManager.h"
#include "Account.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <vector>
#include "Transaction.h"
#include "Category.h"
#include <sstream>
#include "Budget.h"
#include <codecvt>
#include <locale>
using namespace std;

// категорий по умолчанию
vector<Category> getDefaultCategories(const string& type) {
    vector<Category> categories;
    if (type == "доход") {
        categories = {
            Category("Зарплата"),
            Category("Подарки"),
            Category("Инвестиции"),
            Category("Прочее")
        };
    } else if (type == "расход") {
        categories = {
            Category("Еда"),
            Category("Транспорт"),
            Category("Развлечения"),
            Category("Коммунальные услуги"),
            Category("Прочее")
        };
    }
    return categories;
}

void TransactionManager::addTransaction(AccountManager& accountMgr, Budget& budget) {
    vector<string> types = { "доход", "расход" };
    int typeChoice;
    double amount;
    int accountId;
    string description;

    cout << "\nДобавление новой транзакции:\n";

    // Дата
    time_t now = time(0);
    tm ltm;
    if (localtime_s(&ltm, &now) != 0) {
        cerr << "Ошибка: не удалось получить локальное время.\n";
        return;
    }

    char dateBuffer[11];
    if (strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &ltm) == 0) {
        cerr << "Ошибка: не удалось преобразовать дату в строку.\n";
        return;
    }
    string date = dateBuffer;

    // Выбор типа транзакции
    cout << "Тип транзакции:\n";
    for (size_t i = 0; i < types.size(); ++i)
        cout << i + 1 << ". " << types[i] << endl;

    cout << "Выберите тип: ";
    while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice >(int)types.size()) {
        cout << "Неверный выбор. Повторите ввод: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string type = types[typeChoice - 1];
    vector<Category> categories = getDefaultCategories(type);

    // Выбор категории
    cout << "Категория:\n";
    for (size_t i = 0; i < categories.size(); ++i)
        cout << i + 1 << ". " << categories[i].getName() << endl;

    int categoryChoice;
    cout << "Выберите категорию: ";
    while (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice >(int)categories.size()) {
        cout << "Неверный выбор. Повторите ввод: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Сумма
    cout << "Введите сумму: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Некорректная сумма. Повторите ввод: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
/*// Описание
    cout << "Описание: ";
    cin.ignore();
    getline(cin, description);*/

    
    accountMgr.showAccounts();
    cout << "Введите ID счёта: ";
    cin >> accountId;

    int idx = accountMgr.findAccountIndexById(accountId);
    if (idx == -1) {
        cout << "Счёт не найден!\n";
        return;
    }

    
    if (type == "расход") {
        if (!accountMgr.accounts[idx].withdraw(amount)) {
            cout << "Недостаточно средств.\n";
            return;
        }
        budget.addExpense(categories[categoryChoice - 1].getName(), amount);
        if (budget.isBudgetExceeded(categories[categoryChoice - 1].getName())) {
            cout << "Внимание! Бюджет для категории \"" << categories[categoryChoice - 1].getName() << "\" превышен.\n";
        }
    } else {
        accountMgr.accounts[idx].deposit(amount);
    }

    accountMgr.saveAccounts();

    
    Transaction* newTransaction = nullptr;
    int transactionId = Transaction::getNextId();
    if (type == "доход") {
        newTransaction = new Income(transactionId, accountId, amount, categories[categoryChoice - 1].getName(), date, description);
    } else {
        newTransaction = new Expense(transactionId, accountId, amount, categories[categoryChoice - 1].getName(), date, description);
    }
    transactions.push_back(newTransaction);
    Transaction::setNextId(transactionId + 1);

    
    ofstream file("transactions.txt", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи.\n";
        return;
    }
    file << newTransaction->toString() << endl;
    file.close();

    cout << "Транзакция успешно добавлена.\n";
}

void TransactionManager::showAllTransactions() {
    // Загружаем все транзакции из файла (каждый раз для актуальности)
    ifstream file("transactions.txt", ios::binary);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл транзакций.\n";
        return;
    }

    // Очищаем текущий список и освобождаем память
    for (Transaction* t : transactions) delete t;
    transactions.clear();

    string line;
    int maxId = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            Transaction* t = Transaction::fromString(line);
            transactions.push_back(t);
            if (t->getId() > maxId) {
                maxId = t->getId();
            }
        }
    }
    file.close();
    Transaction::setNextId(maxId + 1);

    if (transactions.empty()) {
        cout << "Нет доступных транзакций.\n";
        return;
    }

    cout << "\nСписок всех транзакций:\n";
    cout << "----------------------------\n";
    for (const Transaction* t : transactions) {
        t->display();
    }
}


TransactionManager::~TransactionManager() {
    for (Transaction* t : transactions) delete t;
}

