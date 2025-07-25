#include <string>
#include <map>
#include "User.h"

#ifndef UTILS_H
#define UTILS_H

// Abre el fichero JSON que almacena los datos y lee los usuarios guardados con sus datos
// y los carga en los objetos necesarios. Si no se encuentra el fichero, se crean los usuarios por defecto.
std::map<std::string, User> readUsersFromFile(std::string path);

// Crea un diccionario de usuarios por defecto.
std::map<std::string, User> createDefaultUsers();

// Guarda los usuarios y algunos metadatos en el fichero JSON a modo de base de datos.
void saveUsersToJSON(const std::map<std::string, User>& users, const std::string& path);

// Calcula el hash del PIN introducido.
std::string hashPin(std::string pin);

// Comprueba que el PIN y el hash introducidos coninciden. Si no, lanza una excepcion.
bool verifyPin(std::string hashed, std::string entered);

// Obtiene el timestamp actual en formato ISO 8601
std::string getCurrentTimestamp();

#endif