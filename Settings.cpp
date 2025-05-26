#include "Settings.h"
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;
void NotificationSettings::showMenu() {
    int choice;
    do {
        system("cls");
        cout << "НАСТРОЙКИ УВЕДОМЛЕНИЙ\n";
        cout << "----------------------\n";
        cout << "1. Включить/выключить уведомления (" << (enabled ? "ВКЛ" : "ВЫКЛ") << ")\n";
        cout << "2. Время напоминания (" << hour << ":00)\n";
        cout << "0. Назад\n";
        cout << "----------------------\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            enabled = !enabled;
            break;
        case 2:
            cout << "Введите час (0-23): ";
            cin >> hour;
            cin.ignore();
            if (hour < 0) hour = 0;
            if (hour > 23) hour = 23;
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
}

// Функция для проверки и показа уведомления (можно вызывать из main или отдельного потока)
void NotificationSettings::checkAndNotify() {
    if (!enabled) return;
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    if (ltm.tm_hour == hour) {
        cout << "\n=== УВЕДОМЛЕНИЕ ===\nНе забудьте внести транзакции!\n===================\n";
        // Можно добавить задержку, чтобы не спамить каждый цикл
        this_thread::sleep_for(chrono::minutes(60));
    }
}