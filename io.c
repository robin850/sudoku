/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include "io.h"

/**
 * Affiche une erreur passé en paramètre et sort du programme
 * avec un code d'erreur 1.
 *
 * @param  message - Message à afficher
 * @return void
 */
void erreur(const char* message) {
  printf("Erreur : %s", message);
  exit(1);
}

/**
 * Affiche la grille de Sudoku de manière lisible (représentation)
 * sous formes de régions.
 *
 * @param  grille - Le grille à afficher.
 * @return void
 */
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

/**
 * Ecrit la représentation d'une grille dans le fichier final
 * contenant les solutions des différentes grilles.
 *
 * @param  grille - La grille à écrire
 * @return void
 */
void ecrire(Grille *grille) {
  int i, j;

  FILE *fichier = fopen("solutionbazniardupret.txt", "a");

  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      fprintf(fichier, "%d", grille->lignes[i][j].valeur);

  fprintf(fichier, "\n");

  fclose(fichier);
}
