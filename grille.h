#ifndef GRILLE_H
#define GRILLE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int regions[9][9];
  int lignes[9][9];
  int colonnes[9][9];
  int tableau[81];
} grille;

int *recupererGrille(char *nom_fichier, int *grille, int ligne);

#endif
