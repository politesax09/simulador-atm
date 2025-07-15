#include <iostream>
#include <string>
#include "Account.h"

// Constructor por defecto
Account::Account() {
    this->account_number = "0000";
    this->balance = 0;
}

// Destructor
Account::~Account() {

}

// Anade el parametro "amount" a la propiedad "balance" de la clase
void Account::deposit(double amount) {
    this->balance += amount;
}

// Resta "amount" de "balance" previo comprobacion.
// Return:
// - true -> La operacion se aplica correctamente.
// - false -> La operacion falla por falta de saldo.
bool Account::withraw(double amount) {
    if (this->balance - amount >= 0)
    {
        this->balance -= amount;
        return true;
    }
    else
        return false;
}

// Devuelve la propiedad "balance".
double Account::get_balance() {
    return this->balance;
}