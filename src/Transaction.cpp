#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "Transaction.h"

/* TODO:
- getAccount()
- getTimestamp()
*/


Transaction::Transaction(){
    // this->type = TransactionType::NONE;
    this->type = TransactionType::NONE;
    this->amount = 0;
    this->set_timestamp();
}

Transaction::~Transaction(){}

// Obtiene una linea en formato string imprimible con los datos de la clase.
// Return:
// - string -> Linea con los datos imprimibles.
std::string Transaction::to_string(){
    return this->timestamp + " " + this->typeToString() + " " + std::to_string(this->amount) + "$";
}

// Crea una timestamp acutal y se la asigna a la propiedad "timestamp" de la clase.
void Transaction::set_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeT = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&timeT);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    this->timestamp = oss.str();
}

// Convierte el valor de la propiedad "type" de "TransactionType" a string.
// Return:
// - string -> Valor de "type" en formato string.
std::string Transaction::typeToString() const {
    switch (this->type)
    {
    case TransactionType::DEPOSIT:
        return "DEPOSIT";
    case TransactionType::WITHDRAWAL:
        return "WITHDRAWAL";
    case TransactionType::TRANSFER_IN:
        return "TRANSFER_IN";
    case TransactionType::TRANSFER_OUT:
        return "TRANSFER_OUT";
    case TransactionType::BALANCE_INQUIRY:
        return "BALANCE_INQUIRY";
    case TransactionType::PIN_CHANGE:
        return "PIN_CHANGE";
    case TransactionType::NONE:
        return "NONE";
    default:
        return "UNKNOWN";
    }
}

// Convierte el parametro de tipo string a "TransactionType".
// Return:
// - TransactionType -> Valor del enum correspondiente al string introducido por parametro
TransactionType Transaction::stringToType(const std::string& str){
    if (str == "DEPOSIT") {
        return TransactionType::DEPOSIT;
    } else if (str == "WITHDRAWAL") {
        return TransactionType::WITHDRAWAL;
    } else if (str == "TRANSFER_IN") {
        return TransactionType::TRANSFER_IN;
    } else if (str == "TRANSFER_OUT") {
        return TransactionType::TRANSFER_OUT;
    } else if (str == "BALANCE_INQUIRY") {
        return TransactionType::BALANCE_INQUIRY;
    } else if (str == "PIN_CHANGE") {
        return TransactionType::PIN_CHANGE;
    } else if (str == "NONE") {
        return TransactionType::NONE;
    }
    return TransactionType::NONE;
}