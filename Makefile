CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
BIN_DIR = bin

# Crear carpeta bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
#---------------------------------------------------------------------
# Compilar el programa principal (cuando lo crees)
procesos: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/procesos_fork.c -o $(BIN_DIR)/procesos_fork

# Ejecutar programa principal
run: procesos
	./$(BIN_DIR)/procesos_fork
#---------------------------------------------------------------------
mi-proceso: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/mi_proceso.c -o $(BIN_DIR)/mi_proceso

run-mi-proceso: mi-proceso
	./$(BIN_DIR)/mi_proceso
#---------------------------------------------------------------------
# Se añade el archivo a compilar al bin
# Compilar test_fork
test: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/test_fork.c -o $(BIN_DIR)/test_fork

# Ejecutar test
# Se crea el comando "test" para indicarlo on the terminal
run-test: test
	./$(BIN_DIR)/test_fork
#---------------------------------------------------------------------


# Limpiar binarios
clean:
	rm -rf $(BIN_DIR)/*

.PHONY: clean run run-test test procesos mi-proceso run-mi-proceso
