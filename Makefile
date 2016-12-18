all: main

solveur: solveur.h solveur.c
	gcc -c solveur.c -Wall -Wextra

options: options.h options.c
	gcc -c options.c -Wall -Wextra

io: io.h io.c
	gcc -c io.c -Wall -Wextra

grille: grille.h grille.c
	gcc -c grille.c -Wall -Wextra

main: main.c grille solveur options io
	gcc -o main grille.o solveur.o options.o io.o main.c -Wall -Wextra
