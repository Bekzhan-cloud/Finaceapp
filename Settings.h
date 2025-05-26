#pragma once
#include <string>

class Settings {
public:
    virtual ~Settings() = default;
    virtual void showMenu() = 0;
};

// Производный класс для настроек уведомлений
class NotificationSettings : public Settings {
public:
    bool enabled = false;
    int hour = 20;

    void showMenu() override;
    void checkAndNotify();
};
