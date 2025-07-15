#include <string>
#include <unordered_map>
#include "User.h"

#ifndef ATM_H
#define ATM_H

class atm
{
private:
    std::unordered_map<std::string, User> users;
public:
    atm(/* args */);
    ~atm();
    void load_users();
    void save_users();
    User* login(std::string username, std::string pin);
    void show_main_menu(User* user);
};

#endif