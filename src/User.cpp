#include <string>
#include <iostream>
#include "User.h"

/* TODO:
- authenticate()
- change_pin()
- record_transaction()
- record_transaction() sobrecarga
- get_transaction_history()
*/


// Constrctor por defecto
User::User(){
    this->username = "Default";
    // this->hashed_pin = "0000";  Hashear el pin
    this->account = Account();
}

// Constructor por parametro
// Params:
// - new_username -> String que sera "username" del objeto.
// - new_pin -> String que sera hasheado y guardado en "hashed_pin" del objeto.
// - new_account -> Objeto "Account" guardado como referencia en el objeto "User" creado
User::User(std::string new_username, std::string new_pin, Account new_account) {
    this->username = new_username;
    this->hashed_pin = new_pin;
    this->account = new_account;
}

// User::User(std::string new_username, std::string new_pin, double amount){
//     this->username = new_username;
//     this->hashed_pin = new_pin;
//     this.
// }

User::~User(){
    // this->account.delete();
}

bool User::authenticate(std::string entered_pin){

}

void User::change_pin(std::string new_pin){}

// Crea el objeto "Transaction" con los parametros introduciddos y lo anade a "transaction_history".
// Esta sobrecarga anade una "timestamp" automaticamente.
// Params:
// - type -> String que sera la propiedad "type" del objeto "Transaction".
// - amount -> Double que sera la propiedad "amount" del objeto "Transaction".
void User::record_transaction(std::string type, double amount){}

// Crea el objeto "Transaction" con los parametros introduciddos y lo anade a "transaction_history".
// Esta variante anade tambien la "timestamp" leida del JSON.
// Params:
// - type -> String que sera la propiedad "type" del objeto "Transaction".
// - amount -> Double que sera la propiedad "amount" del objeto "Transaction".
// - timestamp -> String que sera la propiedad "timestamp" del objeto "Transaction";
void User::record_transaction(std::string type, double amount, std::string timestamp){}

std::string User::getUsername() {
    return this->username;
}

std::string User::getHashedPin() {
    return this->hashed_pin;
}

Account User::getAccount() {
    return this->account;
}

std::vector<Transaction> User::get_transaction_history(){}
