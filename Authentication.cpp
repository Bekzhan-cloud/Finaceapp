#include "Authentication.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

Authentication::Authentication(const string& filename) : passwordFile(filename) {}

bool Authentication::passwordExists() const {
    ifstream file(passwordFile);
    return file.good();
}

void Authentication::savePassword(const string& newPassword) {
    ofstream file(passwordFile);
    if (file.is_open()) {
        file << newPassword;
    }
}

string Authentication::loadPassword() const {
    ifstream file(passwordFile);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл пароля!");
    }
    string savedPassword;
    getline(file, savedPassword);
    return savedPassword;
}

bool Authentication::login() {
    try {
        if (!passwordExists()) {
            cout << "Первый запуск! Придумайте новый пароль: ";
            string newPassword;
            cin >> newPassword;
            savePassword(newPassword);
            cout << "Пароль сохранён. Перезапустите программу.\n";
            return false;
        } else {
            string saved = loadPassword();
            cout << "Введите пароль: ";
            string entered;
            cin >> entered;

            if (entered == saved) {
                cout << "Вход выполнен.\n";
                return true;
            } else {
                cout << "Неверный пароль!\n";
                return false;
            }
        }
    } catch (const exception& ex) {
        cout << "Ошибка аутентификации: " << ex.what() << endl;
        return false;
    }
}