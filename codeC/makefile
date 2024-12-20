# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = abr.o avl.o main.o
EXEC = exec

# Règles principales
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c tri.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers intermédiaires
clean:
	rm -f $(OBJ)

# Nettoyage complet (supprime aussi l'exécutable)
distclean: clean
	rm -f $(EXEC)

# Cible "phony" pour éviter les conflits avec des fichiers du même nom
.PHONY: all clean distclean
