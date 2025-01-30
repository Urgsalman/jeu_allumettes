# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL2 -lSDL2_ttf

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/jeu_allumettes.exe

# Règle par défaut
all: $(TARGET)

# Compilation du programme
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # Crée le dossier bin/ s'il n'existe pas
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Crée le dossier obj/ s'il n'existe pas
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean