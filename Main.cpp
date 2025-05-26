// main.cpp
#include <iostream>
#include "Authentication.h"
#include "AccountManager.h"
#include "Transaction.h"
#include "addTransaction.h"
#include "UI.h"
#include <windows.h>
#include "Category.h"
#include "Budget.h"
#include "Kopilka.h"
#include "Analytics.h"
//#include "ExportReport.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru");
 
    // Аутентификация
    Authentication auth;
    if (!auth.login()) {
        
        return 0;
    }

    //Инициализируем
    AccountManager accountMgr("accounts.txt");
    TransactionManager transactionMgr;
    Budget budget;
    Kopilka kopilka;
    // ExportReport exporter;

    int choice;
    do {
        showMainMenu(); // Показываем основное меню
        cin >> choice;

        switch (choice) {
        case 1: runAccountMenu(accountMgr); break;
        case 2: showTransactionMenu(transactionMgr, accountMgr,budget); break;
        case 3: showCategoryMenu(); break;
        case 4: showBudgetMenu(budget);break;
        case 5: showKopilkaMenu(kopilka, accountMgr);break;
        case 6: showAnalyticsMenu(transactionMgr); break;
        case 7: showExportMenu(transactionMgr); break;
        case 8: showSettingsMenu(); break;
            
        case 0: cout << "Выход из программы.\n"; break;
        default: cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);
    

    return 0;
}
