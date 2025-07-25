#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <openssl/sha.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include "User.h"

using json = nlohmann::json;


// Abre el fichero JSON que almacena los datos y lee los usuarios guardados con sus datos
// y los carga en los objetos necesarios. Si no se encuentra el fichero, se crean los usuarios por defecto.
// Params:
// - path -> String que indica la ruta al fichero utilizado.
// Return: map<string, User>, diccionario de usuarios con clave "string" y valor "User".
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

// Crea un diccionario de usuarios por defecto.
// Return: map<string, User>, Diccionario con clave "string" y valor "User".
std::map<std::string, User> createDefaultUsers() {
    Account acc_usr1("ES123456789", 1000.00);
    Account acc_usr2("ES877334422", 3000.00);
    Account acc_usr3("ES483729334", 45000.00);
    User usr1("Rogelio", "1234", acc_usr1);
    User usr2("Angel", "4321", acc_usr3);
    User usr3("Rosa", "2222", acc_usr3);

    users["rogelio"] = usr1;
    users["angel"] = usr2;
    users["rosa"] = usr3;
    return users;
}

// Guarda los usuarios y algunos metadatos en el fichero JSON a modo de base de datos.
// Params:
// - users -> Referencia al diccionario <string,User> donde se almacenan los usuarios.
// - path -> Referencia al string que indica la ruta del fichero JSON.
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

// Calcula el hash del PIN introducido.
// Params:
// - pin -> Tipo string.
// Return: string, PIN hashedado.
std::string hashPin(std::string pin) {
    // Validar PIN longitud y solo numeros
    if (pin.length() != 4)
        throw std::invalid_argument("El PIN debe tener 4 digitos.");
    for (char c : pin) {
        if (!std::isdigit(c))
            throw std::invalid_argument("El PIN debe contener solo numeros.");
    }
    // Anadir salt
    std::string saltedPin = pin + "adfiRHsCsw45D";
    // Generar hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, saltedPin.c_str(), saltedPin.length());
    SHA256_Final(hash, &sha256);
    // Convertir a string hex
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();    


}

// Comprueba que el PIN y el hash introducidos coninciden. Si no, lanza una excepcion.
// Params:
// - hashed -> String, hash del PIN.
// - entered -> String, PIN introducido sin hashear.
// Return: bool, True si coinciden, False si no.
bool verifyPin(std::string hashed, std::string entered) {
    try
    {
        std::string enteredHash = hashPin(entered);
        return hashed == enteredHash;
    }
    catch(const std::exception& e)
        return false;
}

// Obtiene el timestamp actual en formato ISO 8601
// Return: string, timestamp en formato "YYYY-MM-DD HH:MM:SS"
std::string getCurrentTimestamp() {
    // Obtener tiempo actual
    auto now = std::chorno::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    // Convertir a estructura tm
    std::tm* tm = std::localtime(&time_t);
    // Formatear como string
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}