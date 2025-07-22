#include <string>

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
private:
    std::string account_number;
    double balance;
public:
    Account();
    Account(std::string new_account_number, double new_balance);
    ~Account();
    void deposit(double amount);
    bool withraw(double amount);
    double get_balance();
};

#endif