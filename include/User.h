#include <string>
#include <vector>
#include "Account.h"
#include "Transaction.h"

#ifndef USER_H
#define USER_H

class User
{
private:
    std::string username;
    std::string hashed_pin;
    Account account;
    std::vector<Transaction> transaction_history;
public:
    User();
    User(std::string new_username, std::string new_pin, Account new_account);
    ~User();
    bool authenticate(std::string entered_pin);
    void change_pin(std::string new_pin);
    void record_transaction(std::string type, double amount);
    void record_transaction(std::string type, double amount, std::string timestamp);
    std::string getUsername();
    std::string getHashedPin();
    Account getAccount();
    std::vector<Transaction> get_transaction_history();
};

#endif