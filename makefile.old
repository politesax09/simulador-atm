# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = 

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BIN_DIR)/simulador_atm

# Regla principal
all: $(TARGET)

# Crear ejecutable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
    $(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilar archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Crear directorios si no existen
$(BUILD_DIR):
    mkdir -p $(BUILD_DIR)

$(BIN_DIR):
    mkdir -p $(BIN_DIR)

# Limpiar archivos generados
clean:
    rm -rf $(BUILD_DIR) $(BIN_DIR)

# Limpiar solo objetos
clean-obj:
    rm -rf $(BUILD_DIR)

# Ejecutar el programa
run: $(TARGET)
    ./$(TARGET)

# Compilar en modo debug
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Compilar en modo release
release: CXXFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Mostrar información del proyecto
info:
    @echo "Compilador: $(CXX)"
    @echo "Flags: $(CXXFLAGS)"
    @echo "Fuentes: $(SOURCES)"
    @echo "Objetos: $(OBJECTS)"
    @echo "Ejecutable: $(TARGET)"

# Reglas que no son archivos
.PHONY: all clean clean-obj run debug release info

# Dependencias automáticas
-include $(OBJECTS:.o=.d)