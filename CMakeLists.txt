cmake_minimum_required(VERSION 3.20)

# Información del proyecto
project(SimuladorATM 
    VERSION 1.0.0
    DESCRIPTION "Simulador de cajero automático en C++"
    LANGUAGES CXX
)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configuración de directorios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Directorios de headers
include_directories(include)

# Asegurar detección correcta de CPU en Mac ARM64
if(APPLE AND NOT DEFINED CMAKE_APPLE_SILICON_PROCESSOR)
    message(STATUS "Apple Silicon detected: setting processor to arm64")
    set(CMAKE_APPLE_SILICON_PROCESSOR "arm64" CACHE STRING "" FORCE)
endif()

# Configuración específica para macOS
if(APPLE)
    set_target_properties(simulador_atm PROPERTIES
        MACOSX_RPATH ON
        INSTALL_RPATH_USE_LINK_PATH ON
    )
endif()

# Flags de compilación basados en tu Makefile original
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
    message(STATUS "Modo Debug activado")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
    message(STATUS "Modo Release activado")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    message(STATUS "Modo por defecto")
endif()

# Verificar que existe nlohmann/json local
if(EXISTS ${CMAKE_SOURCE_DIR}/include/json.hpp)
    message(STATUS "nlohmann/json encontrado localmente: include/json.hpp")
    set(HAS_NLOHMANN_JSON ON)
    add_definitions(-DHAVE_NLOHMANN_JSON)
else()
    message(WARNING "nlohmann/json NO encontrado en include/json.hpp")
    set(HAS_NLOHMANN_JSON OFF)
endif()

# Buscar OpenSSL (completamente opcional)
find_package(OpenSSL QUIET)
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL encontrado: ${OPENSSL_VERSION}")
    add_definitions(-DHAVE_OPENSSL)
    set(HAS_OPENSSL ON)
else()
    message(STATUS "OpenSSL no encontrado - usando hash simple")
    set(HAS_OPENSSL OFF)
endif()

# Archivos fuente (basado en tu Makefile)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Mostrar archivos encontrados
message(STATUS "Archivos fuente encontrados:")
foreach(source ${SOURCES})
    message(STATUS "  ${source}")
endforeach()

message(STATUS "Archivos header encontrados:")
foreach(header ${HEADERS})
    message(STATUS "  ${header}")
endforeach()

# Crear ejecutable
add_executable(simulador_atm ${SOURCES} ${HEADERS})

# Solo enlazar OpenSSL si está disponible (nlohmann/json es header-only)
if(HAS_OPENSSL)
    target_link_libraries(simulador_atm PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# Crear directorio de base de datos
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/db)

# Copiar archivo de base de datos si existe
if(EXISTS ${CMAKE_SOURCE_DIR}/db/db.json)
    configure_file(${CMAKE_SOURCE_DIR}/db/db.json ${CMAKE_BINARY_DIR}/db/db.json COPYONLY)
    message(STATUS "Archivo db.json copiado al directorio build")
endif()

# Targets personalizados (equivalentes a tu Makefile)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Limpiando todos los archivos generados"
)

add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/simulador_atm
    DEPENDS simulador_atm
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Ejecutando simulador ATM"
)

add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo "Información del proyecto:"
    COMMAND ${CMAKE_COMMAND} -E echo "  Compilador: ${CMAKE_CXX_COMPILER}"
    COMMAND ${CMAKE_COMMAND} -E echo "  Flags: ${CMAKE_CXX_FLAGS}"
    COMMAND ${CMAKE_COMMAND} -E echo "  Ejecutable: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/simulador_atm"
    COMMAND ${CMAKE_COMMAND} -E echo "  nlohmann/json local: ${HAS_NLOHMANN_JSON}"
    COMMAND ${CMAKE_COMMAND} -E echo "  OpenSSL: ${HAS_OPENSSL}"
    COMMENT "Mostrando información del proyecto"
)

# TESTING
# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Tests
add_executable(transaction_tests tests/test_transaction.cpp)
target_link_libraries(transaction_tests transaction gtest_main)

# add_executable(account_tests tests/test_account.cpp)
# target_link_libraries(account_tests account gtest_main)

# add_executable(user_tests tests/test_user.cpp)
# target_link_libraries(user_tests user gtest_main)

# add_executable(atm_tests tests/test_atm.cpp)
# target_link_libraries(atm_tests atm gtest_main)

include(GoogleTest)
gtest_discover_tests(transaction_tests)
# gtest_discover_tests(account_tests)
# gtest_discover_tests(user_tests)
# gtest_discover_tests(atm_tests)

# Información del build
message(STATUS "========================================")
message(STATUS "Configuración del proyecto:")
message(STATUS "  Nombre: ${PROJECT_NAME}")
message(STATUS "  Versión: ${PROJECT_VERSION}")
message(STATUS "  Compilador: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "  nlohmann/json: ${HAS_NLOHMANN_JSON} (local)")
message(STATUS "  OpenSSL: ${HAS_OPENSSL}")
message(STATUS "  Directorio fuente: ${CMAKE_SOURCE_DIR}")
message(STATUS "  Directorio build: ${CMAKE_BINARY_DIR}")
message(STATUS "========================================")