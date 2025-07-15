#include <string>

#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction
{
private:
    std::string type;
    double amount;
    std::string timestamp;
public:
    Transaction();
    ~Transaction();
    std::string to_string();
};

#endif