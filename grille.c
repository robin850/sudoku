#include "grille.h"

int *recupererGrille(char *nom_fichier, int *grille, int ligne) {
  FILE *fichier = fopen(nom_fichier, "r");

  int d, n = 0;

  fseek(fichier, ligne*81, SEEK_CUR);

  while (fscanf(fichier, "%1d", &d) == 1 && n < 81) {
    grille[n] = d;
    n++;
  }

  fclose(fichier);

  return grille;
}

int **regions(int *grille) {
  int ligne, i, j, region;
  int **regions = (int **)malloc(9 * sizeof(int *));

  for (region = 0; region < 9; region++) {
    regions[region] = (int *)malloc(9 * sizeof(int *));
    i = 0;

    for (ligne = 0, i = 0; ligne < 3; ligne++) {
      regions[region][i]   = grille[ligne * 9 + region * 3];
      regions[region][++i] = grille[ligne * 9 + 1 + region * 3];
      regions[region][++i] = grille[ligne * 9 + 2 + region * 3];
      i++;
    }
  }

  return regions;
}

void afficherGrille(int *grille) {
  int i;
  printf("+-----------+-----------+-----------+\n");

  for (i = 0; i < 81; i++) {
    if (i % 9 == 0 && i != 0)
      printf("|\n");
    if (i == 27 || i == 54)
      printf("+-----------+-----------+-----------+\n");

    printf("| %d ", grille[i]);

  }

  printf("|\n+-----------+-----------+-----------+\n");
}
