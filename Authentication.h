#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

using namespace std;

class Authentication {
private:
    string passwordFile;
    string currentPassword;

    bool passwordExists() const;
    void savePassword(const string& newPassword);
    string loadPassword() const;

public:
    Authentication(const string& filename = "password.txt");
    bool login();
};

#endif
