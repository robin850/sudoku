/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include "grille.h"

void charger(char *nom_fichier, Grille *grille, int ligne) {
  FILE *fichier = fopen(nom_fichier, "r");

  int d, i, j, k, debut, debut_ligne, n = 0;
  int compteur = 0;

  // On rajoute le numéro de la ligne car \n compte
  // pour un caractère.
  fseek(fichier, (ligne*81)+ligne, SEEK_CUR);

  while (fscanf(fichier, "%1d", &d) == 1 && n < 81) {
    grille->tableau[n].valeur = d;
    grille->tableau[n].deBase = d != 0;

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

bool estDans(Case *tab, int i) {
  int j;

  for (j = 0; j < 9; j++)
    if (tab[j].valeur == i)
      return true;

  return false;
}

void placer(Grille *grille, int i, int j, int position, int valeur) {
  grille->tableau[position].valeur = valeur;
  grille->lignes[i][j].valeur      = valeur;
}

bool absentLigne(Grille *grille, int valeur, int ligne) {
  int colonne;

  for (colonne = 0; colonne < 9; colonne++)
    if (grille->lignes[ligne][colonne].valeur == valeur)
      return false;

  return true;
}

bool absentColonne(Grille *grille, int valeur, int colonne) {
  int ligne;

  for (ligne = 0; ligne < 9; ligne++)
    if (grille->lignes[ligne][colonne].valeur == valeur)
      return false;

  return true;
}

bool absentRegion(Grille *grille, int valeur, int ligne, int colonne) {
  // int i, region;

  // if (colonne < 3)
  //   region = ligne < 3 ? 0 : (ligne < 6 ? 3 : 6);
  // else if (colonne < 6)
  //   region = ligne < 3 ? 1 : (ligne < 6 ? 4 : 7);
  // else
  //   region = ligne < 3 ? 2 : (ligne < 6 ? 5 : 8);

  // for (i = 0; i < 9; i++)
  //   if (grille->regions[region][i].valeur == valeur)
  //     return false;

  int _i = ligne-(ligne%3), _j = colonne-(colonne%3);
    for (ligne = _i; ligne < _i+3; ligne++)
        for (colonne=_j; colonne < _j+3; colonne++)
            if (grille->lignes[ligne][colonne].valeur == valeur)
                return false;
    return true;
}
