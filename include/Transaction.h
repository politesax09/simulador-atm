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
    std::string get_timestamp() const;
    double get_amount() const;
    std::string type_to_string() const;
    static TransactionType string_to_type(const std::string& str);
};

#endif