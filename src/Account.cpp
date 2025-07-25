#include <iostream>
#include "Account.h"

// Constructor por defecto
Account::Account() {
    this->account_number = "00000000";
    this->balance = 0;
}

// Constructor por parametro
Account::Account(std::string new_account_number, double new_balance) {
    this->account_number = new_account_number;
    this->balance = new_balance;
}

// Destructor
Account::~Account() {}

// Anade el parametro "amount" a la propiedad "balance" de la clase
void Account::deposit(double amount) {
    if (amount > 0)
        this->balance += amount;
    else
        std::cout << "ERROR: El monto debe ser mayor que 0." << std::endl;
}

// Resta "amount" de "balance" previo comprobacion.
// Return:
// - true -> La operacion se aplica correctamente.
// - false -> La operacion falla por falta de saldo.
bool Account::withraw(double amount) {
    if (this->balance - amount >= 0 && amount > 0)
    {
        this->balance -= amount;
        return true;
    }
    else
        return false;
}

// Accede a la propiedad "balance".
// Return:
// - double -> Valor de "balance"
double Account::get_balance() const {
    return this->balance;
}

// Accede a la propiedad "account_number".
// Return:
// - string -> Valor de "account_number"
std::string Account::get_account_number() const {
    return this->account_number;
}