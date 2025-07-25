#include <string>
#include <iostream>
#include "User.h"
#include "utils.h"

/* TODO:
- get_transaction_history() ???? no se si asi se devuelve el puntero correctamente
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

// Comprueba si el PIN introducido coincide con el del usuario.
// Params:
// - entered_pin -> String, pin introducido para intentar login.
// Return: bool, True si coinciden (login correcto) y False si no.
bool User::authenticate(std::string entered_pin){
    return verifyPin(this->hashed_pin, entered_pin);
}

// Cambia el PIN actual por un nuevo PIN.
// Params:
// - new_pin -> String, nuevo PIN que va a guardar.
void User::change_pin(std::string new_pin){
    this->hashed_pin = hashPin(new_pin);
}

// Crea el objeto "Transaction" con los parametros introduciddos y lo anade a "transaction_history".
// Esta sobrecarga anade una "timestamp" automaticamente. Se utilizara para una nueva transaccion.
// Params:
// - type -> String que sera la propiedad "type" del objeto "Transaction".
// - amount -> Double que sera la propiedad "amount" del objeto "Transaction".
void User::record_transaction(std::string type, double amount){
    Transaction transaction(type, amount);
    this->transaction_history.push_back(transaction);
}

// Crea el objeto "Transaction" con los parametros introduciddos y lo anade a "transaction_history".
// Esta variante anade tambien la "timestamp" por parametro. Se utilizara al leer los datos del JSON.
// Params:
// - type -> String que sera la propiedad "type" del objeto "Transaction".
// - amount -> Double que sera la propiedad "amount" del objeto "Transaction".
// - timestamp -> String que sera la propiedad "timestamp" del objeto "Transaction";
void User::record_transaction(std::string type, double amount, std::string timestamp){
    Transaction transaction(type, amount, timestamp);
    this->transaction_history.push_back(transaction);
}

std::string User::getUsername() const {
    return this->username;
}

std::string User::getHashedPin() const {
    return this->hashed_pin;
}

Account User::getAccount() const {
    return this->account;
}

std::vector<Transaction> User::get_transaction_history() const {
    return this->transaction_history;
}
