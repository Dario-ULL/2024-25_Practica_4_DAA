# Variables
CC = g++
CFLAGS = -Wall -std=c++11
OBJ_DIR = ImplementacionClases
INC_DIR = Clases
SRC_DIR = $(OBJ_DIR)
MAIN_SRC = main.cc
EXEC = main

# Archivos objeto, con todos los archivos fuente de .cc a .o
OBJ_FILES = $(OBJ_DIR)/LectorFichero.o \

# Regla por defecto
all: $(EXEC) clean

# Regla para compilar el ejecutable
$(EXEC): $(OBJ_FILES) $(MAIN_SRC)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(MAIN_SRC) -o $(EXEC)

# Regla para compilar los archivos .cc a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@


# Limpiar los archivos objeto y ejecutables generados
clean:
	rm -f $(OBJ_FILES)

# Regla para limpiar todo
fclean: clean
	rm -f $(EXEC)

# Regla para recompilar todo
re: fclean all
