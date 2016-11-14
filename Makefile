all: main

grille: grille.h grille.c
	gcc -c grille.c -Wall -Wextra

main: main.c grille
	gcc -o main grille.o main.c -Wall -Wextra
