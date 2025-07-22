#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include "json.hpp"
#include "User.h"

using json = nlohmann::json;

/* TODO:
- createDefaultUsers()
- hashPin()
- verifyPin()
- getCurrentTimestamp()
*/


// Abre el fichero JSON que almacena los datos y lee los usuarios guardados con sus datos y los carga en los objetos necesarios.
// Si no se encuentra el fichero, se crean los usuarios por defecto.
std::map<std::string, User> readUsersFromFile(std::string path){
    std::map<std::string, User> users;
    // Abrir fichero JSON 
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "Archivo " << path << " no encontrado. Creando usuarios por defecto..." << std::endl;
        return createDefaultUsers();
    }
    else {
        std::cout << "Leyendo usuarios de archivo: " << path << std::endl;
        try
        {
            json jsonData;
            file >> jsonData;

            // Leer usuarios
            for (const auto& userJson : jsonData["users"])
            {
                std::string username = userJson["username"];
                std::string hashedPin = userJson["hashed_pin"];

                // Leer cuenta y asignarla al usuario
                double balance = userJson["account"]["balance"];
                std::string accountNumber = userJson["account"]["account_number"];
                Account account(accountNumber, balance);

                // Crear usuario con los datos
                User user(username, hashedPin, account);

                // Leer historial de transacciones
                for (const auto& transJson : userJson["transaction_history"])
                {
                    std::string type = transJson["type"];
                    double amount = transJson["amount"];
                    std::string timestamp = transJson["timestamp"];
                    user.record_transaction(type, amount, timestamp);
                }
                users[username] = user;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Error procesando JSON: " << e.what() << std::endl;
            std::cout << "Creando usuarios por defecto..." << std::endl;
            return createDefaultUsers();
        }
        file.close();
        std::cout << "Usuarios cargados desde JSON: " << users.size() << std::endl;
        return users;
    }
}

std::map<std::string, User> createDefaultUsers() {
// Usuarios por defecto:
        // User admin = User("admin", "1234", 10000.0);
        // users["admin"] = admin;
}

void saveUsersToJSON(const std::map<std::string, User>& users, const std::string& path) {
    json jsonData;
    
    // Actualizar Meetadata
    jsonData["metadata"]["version"] = "1.0";
    jsonData["metadata"]["last_updated"] = getCurrentTimestamp();
    jsonData["metadata"]["total_users"] = users.size();

    // Actualizar Usuarios
    json usersArray = json::array();
    for (const auto& userPair : users)
    {
        const User& user = userPair.second;
        json userJson;
        userJson["username"] = user.getUsername();
        userJson["hashed_pin"] = user.getHashedPin();
        userJson["status"] = "active";

        // Actualizar Cuenta
        userJson["account"]["account_number"] = user.getAccount().getAccountNumber();
        userJson["account"]["balance"] = user.getAccount().getBalance();
        userJson["account"]["account_type"] = "checking";

        // Actualizar Historial de transacciones
        json transArray = json::array();
        for (const auto& trans : user.get_transaction_history())
        {
            json transElem;
            transElem["type"] = trans.typeToString();
            transElem["amount"] = trans.getAmount();
            transElem["timestamp"] = trans.getTimestamp();
            transArray.push_back(transElem);
        }
        userJson["transacction_history"] = transArray;
        usersArray.push_back(userJson);
    }
    jsonData["users"] = usersArray;

    // Escribir en el fichero
    std::ofstream file(path);
    if (file.is_open())
    {
        file << jsonData.dump(4);
        file.close();
        std::cout << "Usuarios guardados en el JSON: " << path << std::endl;
    }
    else
        std::cout << "Error al abrir el archivo JSON: " << path << std::endl;    
}

std::string hashPin(std::string pin) {

}


bool verifyPin(std::string hashed, std::string entered) {

}