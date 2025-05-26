#ifndef UI_H
#define UI_H
#include <string>
using namespace std;
class AccountManager;
class TransactionManager;
class Budget;
class Kopilka;

void printCentered(const string& str); 
void showMainMenu(); 
void runAccountMenu(class AccountManager& mgr);
void showTransactionMenu(class TransactionManager& transactionMgr, AccountManager& accountMgr, Budget& budget);
void showCategoryMenu(); 
void showBudgetMenu(class Budget& budget); 
void showKopilkaMenu(class Kopilka& Kopilka, AccountManager& accountMgr);
void showAnalyticsMenu(class TransactionManager& transactionMgr);
void showExportMenu(TransactionManager& transactionMgr);
void showSettingsMenu();
#endif
