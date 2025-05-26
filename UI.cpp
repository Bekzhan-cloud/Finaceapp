#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>
#include "UI.h"
#include "AccountManager.h"
#include "addTransaction.h"
#include "Category.h"
#include "Budget.h"
#include "Kopilka.h"
#include "Analytics.h"
#include "ExportReport.h"
#include "Settings.h"
using namespace std;
// Функция для получения ширины консоли


int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Функция для вывода текста по центру
void printCentered(const string& str) {
    int consoleWidth = getConsoleWidth();           // Ширина консоли
    int spaces = (consoleWidth - str.length()) / 2; // Сколько пробелов нужно добавить слева
    cout << string(spaces, ' ') << str << endl;
}

// Функция для вывода категорий
void printCategories(const vector<Category>& categories, const string& title) {
    system("cls");
    printCentered(title);
    printCentered("-----------------------------");

    if (categories.empty()) {
        printCentered("Список пуст.");
    } else {
        for (size_t i = 0; i < categories.size(); ++i) {
            // Формируем строку категории
            string categoryLine = to_string(i + 1) + ". " + categories[i].getName();
            // Выводим строку по центру
            printCentered(categoryLine);
        }
    }

    printCentered("-----------------------------");
}

// главного меню
void showMainMenu()
{
    system("cls"); // Очистка экрана
    printCentered("СИСТЕМА УПРАВЛЕНИЯ ЛИЧНЫМИ ФИНАНСАМИ");
    printCentered("-----------------------------");
    printCentered("1. Управление счетами");
    printCentered("2. Транзакции");
    printCentered("3. Категории");
    printCentered("4. Бюджет");
    printCentered("5. Копилка");
    printCentered("6. Аналитика");
    printCentered("7. Экспорт отчетов");
    printCentered("8. Настройки");
    printCentered("0. Выход");
    printCentered("-----------------------------");
    printCentered("Выберите пункт: ");
    cout << " Выберите пункт: ";
}
// меню управления счетами
void runAccountMenu(AccountManager &mgr)
{
    
    int choice;
    do
    {
        system("cls");
        printCentered("МЕНЮ СЧЕТОВ");
        printCentered("---------------------");
        printCentered("1. Показать все счета");
        printCentered("2. Добавить новый счёт");
        //printCentered("3. Пополнить счёт");
        //printCentered("4. Снять со счёта");
        printCentered("0. Назад");
        printCentered("---------------------");
        printCentered("Выберите действие: ");
        cin >> choice;
        switch (choice)
        {
        case 1:
            mgr.showAccounts();
            break;
        case 2:
            mgr.addAccount();
            break;
        case 3:
            //mgr.depositToAccount();
            break;
        case 4:
            //mgr.withdrawFromAccount();
            break;
        case 0:
            break;
        default:
            cout << " ⚠️  Неверный выбор. Попробуйте ещё раз.\n";
        }

        if (choice != 0)
        {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}
// меню транзакций
void showTransactionMenu(TransactionManager& transactionMgr, AccountManager& accountMgr, Budget& budget) {
    int choice;
    do {
        system("cls");
        printCentered("МЕНЮ ТРАНЗАКЦИЙ");
        printCentered("-------------------");
        printCentered("1. Показать все транзакции");
        printCentered("2. Добавить новую транзакцию");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        switch (choice) {
        case 1:
            transactionMgr.showAllTransactions();
            break;
        case 2:
            transactionMgr.addTransaction(accountMgr, budget);
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}
// меню категорий
void showCategoryMenu() {
    int choice;
    do {
        system("cls");
        printCentered("МЕНЮ КАТЕГОРИЙ");
        printCentered("-------------------");
        printCentered("1. Показать категории доходов");
        printCentered("2. Показать категории расходов");
        printCentered("3. Добавить категорию доходов");
        printCentered("4. Добавить категорию расходов");
        printCentered("5. Удалить категорию доходов");
        printCentered("6. Удалить категорию расходов");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        switch (choice) {
        case 1:
            printCategories(Category::getIncomeCategories(), "КАТЕГОРИИ ДОХОДОВ:");
            break;
        case 2:
            printCategories(Category::getExpenseCategories(), "КАТЕГОРИИ РАСХОДОВ:");
            break;
        case 3: {
            system("cls");
            cout << "Введите название новой категории доходов: ";
            string newCategoryName;
            cin.ignore();
            getline(cin, newCategoryName);
            Category::addIncomeCategory(newCategoryName);
            cout << "Категория доходов \"" << newCategoryName << "\" успешно добавлена.\n";
            break;
        }
        case 4: {
            system("cls");
            cout << "Введите название новой категории расходов: ";
            string newCategoryName;
            cin.ignore();
            getline(cin, newCategoryName);
            Category::addExpenseCategory(newCategoryName);
            cout << "Категория расходов \"" << newCategoryName << "\" успешно добавлена.\n";
            break;
        }
        case 5: {
            printCategories(Category::getIncomeCategories(), "КАТЕГОРИИ ДОХОДОВ:");
            cout << "Введите номер категории доходов для удаления: ";
            int categoryIndex;
            cin >> categoryIndex;
            Category::removeIncomeCategory(categoryIndex - 1);
            break;
        }
        case 6: {
            printCategories(Category::getExpenseCategories(), "КАТЕГОРИИ РАСХОДОВ:");
            cout << "Введите номер категории расходов для удаления: ";
            int categoryIndex;
            cin >> categoryIndex;
            Category::removeExpenseCategory(categoryIndex - 1);
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}

//Бюджет
void showBudgetMenu(Budget& budget) {
    int choice;
    do {
        system("cls");
        printCentered("МЕНЮ БЮДЖЕТА");
        printCentered("-------------------");
        printCentered("1. Установить бюджет для категории");
        printCentered("2. Показать бюджеты");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        switch (choice) {
        case 1: {
            printCategories(Category::getExpenseCategories(), "КАТЕГОРИИ РАСХОДОВ:");
            cout << "Введите номер категории: ";
            int categoryIndex;
            cin >> categoryIndex;

            if (categoryIndex < 1 || categoryIndex > (int)Category::getExpenseCategories().size()) {
                cout << "Неверный выбор категории.\n";
                break;
            }

            string selectedCategory = Category::getExpenseCategories()[categoryIndex - 1].getName();
            cout << "Введите сумму бюджета для категории \"" << selectedCategory << "\": ";
            double amount;
            cin >> amount;

            budget.setBudget(selectedCategory, amount);
            cout << "Бюджет для категории \"" << selectedCategory << "\" установлен на сумму " << amount << ".\n";
            break;
        }
        case 2:
            system("cls");
            budget.displayBudgets();
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);
}
//Копилка
void showKopilkaMenu(Kopilka& kopilka, AccountManager& accountMgr) {
    int choice;
    do {
        system("cls");
        printCentered("МЕНЮ КОПИЛКИ");
        printCentered("-------------------");
        printCentered("1. Показать баланс копилки");
        printCentered("2. Перевести со счета в копилку");
        printCentered("3. Перевести из копилки на счет");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        switch (choice) {
        case 1:
            kopilka.display();
            break;
        case 2: {
            int accId;
            double amount;
            accountMgr.showAccounts();
            cout << "Введите ID счета: ";
            cin >> accId;
            cout << "Сумма для перевода: ";
            cin >> amount;
            kopilka.transferFromAccount(accountMgr, accId, amount);
            break;
        }
        case 3: {
            int accId;
            double amount;
            accountMgr.showAccounts();
            cout << "Введите ID счета: ";
            cin >> accId;
            cout << "Сумма для перевода: ";
            cin >> amount;
            kopilka.transferToAccount(accountMgr, accId, amount);
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
}
//
// меню аналитики
void showAnalyticsMenu(TransactionManager& transactionMgr) {
    Analytics analytics;
    
    int choice;
    do {
        system("cls");
        printCentered("МЕНЮ АНАЛИТИКИ");
        printCentered("-------------------");
        printCentered("1. Общая статистика (весь период)");
        printCentered("2. По категориям (весь период)");
        printCentered("3. Общая статистика за период");
        printCentered("4. По категориям за период");
        printCentered("5. Экспорт в Excel (CSV)");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        string startDate, endDate;
        time_t now = time(0);
        tm* ltm = 
        localtime(&now);
        char buf[11];

        switch (choice) {
        case 1:
            analytics.showSummary(transactionMgr); // весь период
            break;
        case 2:
            analytics.showCategoryStats(transactionMgr); // весь период
            break;
        case 3: { // Общая статистика за период
            // Запрос периода
            printCentered("1. За сегодня");
            printCentered("2. За текущую неделю");
            printCentered("3. За текущий месяц");
            printCentered("4. Произвольный период");
            int periodChoice;
            cin >> periodChoice;
            switch (periodChoice) {
                case 1:
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    startDate = endDate = buf;
                    break;
                case 2: {
                    int wday = ltm->tm_wday == 0 ? 6 : ltm->tm_wday - 1;
                    tm weekStart = *ltm;
                    weekStart.tm_mday -= wday;
                    mktime(&weekStart);
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &weekStart);
                    startDate = buf;
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    endDate = buf;
                    break;
                }
                case 3: {
                    tm monthStart = *ltm;
                    monthStart.tm_mday = 1;
                    mktime(&monthStart);
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &monthStart);
                    startDate = buf;
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    endDate = buf;
                    break;
                }
                case 4:
                    cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
                    cin >> startDate;
                    cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
                    cin >> endDate;
                    break;
                default:
                    cout << "Неверный выбор периода.\n";
                    continue;
            }
            analytics.showSummaryPeriod(transactionMgr, startDate, endDate);
            break;
        }
        case 4: { // По категориям за период
            printCentered("1. За сегодня");
            printCentered("2. За текущую неделю");
            printCentered("3. За текущий месяц");
            printCentered("4. Произвольный период");
            int periodChoice;
            cin >> periodChoice;
            switch (periodChoice) {
                case 1:
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    startDate = endDate = buf;
                    break;
                case 2: {
                    int wday = ltm->tm_wday == 0 ? 6 : ltm->tm_wday - 1;
                    tm weekStart = *ltm;
                    weekStart.tm_mday -= wday;
                    mktime(&weekStart);
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &weekStart);
                    startDate = buf;
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    endDate = buf;
                    break;
                }
                case 3: {
                    tm monthStart = *ltm;
                    monthStart.tm_mday = 1;
                    mktime(&monthStart);
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &monthStart);
                    startDate = buf;
                    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
                    endDate = buf;
                    break;
                }
                case 4:
                    cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
                    cin >> startDate;
                    cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
                    cin >> endDate;
                    break;
                default:
                    cout << "Неверный выбор периода.\n";
                    continue;
            }
            analytics.showCategoryStatsPeriod(transactionMgr, startDate, endDate);
            break;
        }
        case 5:
            showExportMenu(transactionMgr);
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
}

// меню экспорта

void showExportMenu(TransactionManager& transactionMgr) {

    int choice;
    do {
        system("cls");
        printCentered("ЭКСПОРТ В EXCEL (CSV)");
        printCentered("-------------------");
        printCentered("1. За сегодня");
        printCentered("2. За текущую неделю");
        printCentered("3. За текущий месяц");
        printCentered("4. За произвольный период");
        printCentered("0. Назад");
        printCentered("-------------------");
        printCentered("Выберите действие: ");
        cin >> choice;

        // Получаем текущую дату
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buf[11];
        string startDate, endDate;

        switch (choice) {
        case 1: // Сегодня
            strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
            startDate = endDate = buf;
            ExportReport::exportTransactionsToCSV(transactionMgr, "transactions_export.csv", startDate, endDate);
            break;
        case 2: { // Неделя
            int wday = ltm->tm_wday == 0 ? 6 : ltm->tm_wday - 1; // 0=вс, 1=пн...
            tm weekStart = *ltm;
            weekStart.tm_mday -= wday;
            mktime(&weekStart);
            strftime(buf, sizeof(buf), "%Y-%m-%d", &weekStart);
            startDate = buf;
            strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
            endDate = buf;
            ExportReport::exportTransactionsToCSV(transactionMgr, "transactions_export.csv", startDate, endDate);
            break;
        }
        case 3: { // Месяц
            tm monthStart = *ltm;
            monthStart.tm_mday = 1;
            mktime(&monthStart);
            strftime(buf, sizeof(buf), "%Y-%m-%d", &monthStart);
            startDate = buf;
            strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
            endDate = buf;
            ExportReport::exportTransactionsToCSV(transactionMgr, "transactions_export.csv", startDate, endDate);
            break;
        }
        case 4: // Произвольный период
            cout << "Введите начальную дату (ГГГГ-ММ-ДД): ";
            cin >> startDate;
            cout << "Введите конечную дату (ГГГГ-ММ-ДД): ";
            cin >> endDate;
            ExportReport::exportTransactionsToCSV(transactionMgr, "transactions_export.csv", startDate, endDate);
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
}


// меню настроек
void showSettingsMenu() {
    NotificationSettings notifSettings;
    notifSettings.showMenu();
}