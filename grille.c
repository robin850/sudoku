#include "grille.h"

void charger(char *nom_fichier, Grille *grille, int ligne) {
  FILE *fichier = fopen(nom_fichier, "r");

  int d, n = 0;

  fseek(fichier, ligne*81, SEEK_CUR);

  while (fscanf(fichier, "%1d", &d) == 1 && n < 81) {
    grille->tableau[n] = d;
    n++;
  }

  fclose(fichier);
}

int **regions(Grille *grille) {
  int ligne, i, region;
  int **regions = (int **)malloc(9 * sizeof(int *));

  for (region = 0; region < 9; region++) {
    regions[region] = (int *)malloc(9 * sizeof(int *));
    i = 0;

    for (ligne = 0, i = 0; ligne < 3; ligne++) {
      regions[region][i]   = grille->tableau[ligne * 9 + region * 3];
      regions[region][++i] = grille->tableau[ligne * 9 + 1 + region * 3];
      regions[region][++i] = grille->tableau[ligne * 9 + 2 + region * 3];
      i++;
    }
  }

  return regions;
}

void afficher(Grille *grille) {
  int i;
  printf("+-----------+-----------+-----------+\n");

  for (i = 0; i < 81; i++) {
    if (i % 9 == 0 && i != 0)
      printf("|\n");
    if (i == 27 || i == 54)
      printf("+-----------+-----------+-----------+\n");

    printf("| %d ", grille->tableau[i]);

  }

  printf("|\n+-----------+-----------+-----------+\n");
}
