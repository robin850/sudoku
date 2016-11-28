#ifndef GRILLE_H
#define GRILLE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int regions[9][9];
  int lignes[9][9];
  int colonnes[9][9];
  int tableau[81];
} Grille;

void charger(char *nom_fichier, Grille *grille, int ligne);

void afficher(Grille *grille);

#endif
