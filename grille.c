#include "grille.h"

void charger(char *nom_fichier, Grille *grille, int ligne) {
  FILE *fichier = fopen(nom_fichier, "r");

  int d, i, j, k, debut, debut_ligne, n = 0;
  int compteur = 0;

  fseek(fichier, ligne*81, SEEK_CUR);

  while (fscanf(fichier, "%1d", &d) == 1 && n < 81) {
    grille->tableau[n].valeur = d;
    grille->tableau[n].deBase = d == 0;

    n++;
  }

  // +-------------------------------------+
  // | Représentation en tableau de lignes |
  // +-------------------------------------+
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      grille->lignes[i][j] = grille->tableau[compteur];
      compteur++;
    }
  }

  // +---------------------------------------+
  // | Représentation en tableau de colonnes |
  // +---------------------------------------+
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      grille->colonnes[i][j] = grille->lignes[j][i];

  // +--------------------------------------+
  // | Représentation en tableau de régions |
  // +--------------------------------------+
  for (i = 0; i < 9; i++) {
    debut    = i < 3 ? 0 : (i < 6 ? 3 : 6);
    compteur = 0;

    for (j = debut; j < debut+3; j++) {
      debut_ligne = i % 3 == 0 ? 0 : (i % 3 == 1 ? 3 : 6);

      for (k = debut_ligne; k < debut_ligne+3; k++)
        grille->regions[i][compteur++]= grille->lignes[j][k];
    }
  }

  fclose(fichier);
}

void zero(int *tableau) {
  int i;

  for (i = 0; i < 9; i++)
    tableau[i] = 0;
}

bool estValide(Grille *grille) {
  int i, j, valeur;
  int *check = (int *)malloc(10 * sizeof(int *));

  // +------------------------+
  // | Vérification en lignes |
  // +------------------------+
  for (i = 0; i < 9; i++) {
    zero(check);

    for (j = 0; j < 9; j++)
      valeur = grille->lignes[i][j].valeur;

      if (valeur == 0)
        continue;

      if (check[valeur])
        return false;
      else
        check[valeur]++;
  }

  // +--------------------------+
  // | Vérification en colonnes |
  // +--------------------------+
  for (i = 0; i < 9; i++) {
    zero(check);

    for (j = 0; j < 9; j++)
      valeur = grille->colonnes[i][j].valeur;

      if (valeur == 0)
        continue;

      if (check[valeur])
        return false;
      else
        check[valeur]++;
  }

  // +-------------------------+
  // | Vérification en régions |
  // +-------------------------+
  for (i = 0; i < 9; i++) {
    zero(check);

    for (j = 0; j < 9; j++)
      valeur = grille->regions[i][j].valeur;

      if (valeur == 0)
        continue;

      if (check[valeur])
        return false;
      else
        check[valeur]++;
  }

  return true;
}

void afficher(Grille *grille) {
  int i, j;

  for (i = 0; i < 9; i++) {
    if (i % 3 == 0)
      printf("\n+---------+---------+---------+\n");
    else
      printf("\n");

    for (j = 0; j < 9; j++) {
      if (j % 3 == 0)
        printf("|");

      printf(" %d ", grille->lignes[i][j].valeur);
    }

    printf("|");
  }

  printf("\n+---------+---------+---------+\n");
}
