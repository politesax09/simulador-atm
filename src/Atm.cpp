#include <string>
#include <map>
#include <iostream>
#include "Atm.h"
#include "User.h"
#include "utils.h"

Atm::Atm(){}

Atm::~Atm(){}

// Carga los usuarios del JSON a la lista de usuarios de la clase.
void Atm::load_users() {
    std::map<std::string, User> users = readUsersFromFile("./db/db.json");
    // this->users.clear();
    // Copiar uno a uno del map<> al unordered_map<> porque no existe casting
    for (const auto& pair : users) {
        this->users.insert(pair);
    }
}

// Guarda los usuarios de la lista de usuarios.
void Atm::save_users() {
    // Copiar uno a uno del map<> al unordered_map<> porque no existe casting
    std::map<std::string, User> users;
    for (const auto& pair : this->users) {
        this->users.insert(pair);
    }
    saveUsersToJSON(users, "./db/db.json");
}

// Comprueba si el usuario existe y si el PIN es correcto.
// Params:
// - username -> string, Nombre de usuario a comprobar.
// - pin -> string, PIN a comprobar.
// Return:
// - User* -> Puntero al usuario si todo es correcto. Si no, NULL.
User* Atm::login(std::string username, std::string pin) {
    for (const auto& pair : this->users) {
        if (username == pair.first)
        {
            User user = pair.second;
            if (user.authenticate(pin))
                return &user;   // FIX: No se si devuelvo bien el puntero.
            else
                return nullptr;
        }
        
    }
    return nullptr;
}

// Imprime el menu principal, gestiona las clases y ejecuta los metodos necesarios.
// Params:
// - user -> User*, El puntero del usuario en uso.
void Atm::show_main_menu(User* user) {
    char option;
    double amount;
    std::vector<Transaction> transHistory;
    std::string oldPin;

    while (option != '6')
    {
        std::cout << "1. Check balance\n2. Deposit\n3. Withdraw\n4. Transaction history\n5. Change PIN\n6. Logout\nSelect option >> ";
        std::cin >> option;
        
        switch (option)
        {
            case '1':
                std::cout << "Balance actual:" << user->getAccount().get_balance() << "$" << std::endl;
                user->record_transaction("BALANCE_INQUIRY", 0);
                break;
            case '2':
                std::cout << "Cantidad a depositar: ";
                std::cin >> amount;
                user->getAccount().deposit(amount);
                std::cout << "Deposito realizado correctamente.\nBalance actual: " << user->getAccount().get_balance() << "$" << std::endl;
                user->record_transaction("DEPOSIT", amount);
                break;
            case '3':
                std::cout << "Cantidad a retirar: ";
                std::cin >> amount;
                user->getAccount().withraw(amount);
                std::cout << "Retiro realizado correctamente.\nBalance actual: " << user->getAccount().get_balance() << "$" << std::endl;
                user->record_transaction("WITHDRAWAL", amount);
                break;
            case '4':
                std::cout << "Historial de transacciones:" << std::endl;
                transHistory = user->get_transaction_history();
                for (auto& t : transHistory)
                    std::cout << t.to_string() << std::endl;
                break;
            case '5':
                std::cout << "Introduce el PIN actual: ";
                std::cin >> oldPin;
                if (user->authenticate(oldPin)) {
                    std::string newPin;
                    std::cout << "Introduce nuevo PIN: ";
                    std::cin >> newPin;
                    user->change_pin(newPin);
                    std::cout << "PIN actualizado correctamente." << std::endl;
                    user->record_transaction("PIN_CHANGE", 0);
                }
                break;
            case '6':
                std::cout << "Hasta la proxima..." << std::endl;
                break;
            default:
                std::cout << "ERROR: Seleccione una opcion disponible (1-6)." << std::endl;
        }
    }
}