#include <string>

#ifndef TRANSACTION_H
#define TRANSACTION_H

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_IN,
    TRANSFER_OUT,
    BALANCE_INQUIRY,
    PIN_CHANGE,
    NONE
};

class Transaction
{
private:
    TransactionType type;
    double amount;
    std::string timestamp;
public:
    Transaction();
    Transaction(std::string type, double amount);
    Transaction(std::string type, double amount, std::string timestamp);
    ~Transaction();
    std::string to_string();
    void set_timestamp();
    std::string typeToString() const;
    static TransactionType stringToType(const std::string& str);
};

#endif