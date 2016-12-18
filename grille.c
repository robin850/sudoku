/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include "grille.h"

/**
 * Charge une grille de Sudoku pour un fichier et une ligne donnés.
 *
 * @param  nom_fichier - Chemin vers le fichier.
 * @param  grille      - Pointeur sur la grille.
 * @param  ligne       - Ligne où la grille est écrite.
 * @return void
 */
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

/**
 * Vérifie si une valeur est présente dans un tableau.
 *
 * @param  tab - Tableau.
 * @param  i   - Valeur à chercher.
 * @return bool
 */
bool estDans(Case *tab, int i) {
  int j;

  for (j = 0; j < 9; j++)
    if (tab[j].valeur == i)
      return true;

  return false;
}

/**
 * Vérifie si une valeur est absente d'une ligne.
 *
 * @param  grille - Pointeur sur la grille.
 * @param  valeur - Valeur à chercher.
 * @param  ligne  - Ligne sur laquelle chercher.
 * @return bool
 */
bool absentLigne(Grille *grille, int valeur, int ligne) {
  int colonne;

  for (colonne = 0; colonne < 9; colonne++)
    if (grille->lignes[ligne][colonne].valeur == valeur)
      return false;

  return true;
}

/**
 * Vérifie si une valeur est absente d'une colonne.
 *
 * @param  grille  - Pointeur sur la grille.
 * @param  valeur  - Valeur à chercher.
 * @param  colonne - Colonne sur laquelle chercher.
 * @return bool
 */
bool absentColonne(Grille *grille, int valeur, int colonne) {
  int ligne;

  for (ligne = 0; ligne < 9; ligne++)
    if (grille->lignes[ligne][colonne].valeur == valeur)
      return false;

  return true;
}

/**
 * Vérifie si une valeur est absente d'une région. La région
 * est déterminée à partir de la ligne et de la colone à
 * laquelle le processus de résolution se trouve.
 *
 * @param  grille  - Pointeur sur la grille.
 * @param  valeur  - Valeur à chercher.
 * @param  ligne   - Ligne actuelle.
 * @param  colonne - Colonne actuelle.
 * @return bool
 */
bool absentRegion(Grille *grille, int valeur, int ligne, int colonne) {
  int i, j;

  // Précedent code utilisant la représentation en tableaux
  // de régions (trop lente, c.f. compte rendu).
  //
  // int i, region;
  //
  // if (colonne < 3)
  //   region = ligne < 3 ? 0 : (ligne < 6 ? 3 : 6);
  // else if (colonne < 6)
  //   region = ligne < 3 ? 1 : (ligne < 6 ? 4 : 7);
  // else
  //   region = ligne < 3 ? 2 : (ligne < 6 ? 5 : 8);
  //
  // for (i = 0; i < 9; i++)
  //   if (grille->regions[region][i].valeur == valeur)
  //     return false;

  int debut_l = ligne - (ligne % 3);
  int debut_c = colonne - (colonne % 3);

  for (i = debut_l; i < debut_l + 3; i++)
    for (j = debut_c; j < debut_c + 3; j++)
      if (grille->lignes[i][j].valeur == valeur)
        return false;

  return true;
}
