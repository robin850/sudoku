#ifndef GRILLE_H
#define GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int valeur;
	bool deBase;
}Case;

typedef struct {
  Case regions[9][9];
  Case lignes[9][9];
  Case colonnes[9][9];
  Case tableau[81];
} Grille;

void charger(char *nom_fichier, Grille *grille, int ligne);

void afficher(Grille *grille);

#endif
