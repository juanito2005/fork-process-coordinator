CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
BIN_DIR = bin

# Crear carpeta bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
#---------------------------------------------------------------------

# Se añade el archivo a compilar al bin
# Compilar test_fork
respuestas: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/respuestas_preguntas.c -o $(BIN_DIR)/respuestas_preguntas

# Se crea el comando "test" para indicarlo on the terminal
# Ejecutar programa principal
run-respuestas: respuestas
	./$(BIN_DIR)/respuestas_preguntas

#---------------------------------------------------------------------

mi-proceso: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/mi_proceso.c -o $(BIN_DIR)/mi_proceso

run-mi-proceso: mi-proceso
	./$(BIN_DIR)/mi_proceso

#---------------------------------------------------------------------

# Limpiar binarios
clean:
	rm -rf $(BIN_DIR)/*

.PHONY: clean run run-test test procesos mi-proceso run-mi-proceso
