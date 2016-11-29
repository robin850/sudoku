#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "grille.h"

int nombreLignes(char *nom_fichier) {
  FILE *fichier = fopen(nom_fichier, "r");

	char c;
	int nbLignes = 0;

	while ((c = fgetc(fichier)) != EOF) {
		if (c == '\n')
			nbLignes++;
	}

  fclose(fichier);

	return nbLignes;
}

void remplirRandom(Grille *grille) {
  srand(time(NULL));
  int i, v;
  for (i = 0; i < 81; i++)
    if (grille->tableau[i] == 0) {
      do {
        v = (rand() %10);
      } while (v == 0);

      grille->tableau[i] = v;
    }
}

bool estDans(int *tab, int i) {
  int j;

  for (j = 0; j < 9; j++)
    if (tab[j] == i)
      return true;

  return false;
}

int **valeursRegions(int **regions) {
  int i, j, k;
  int valeurs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int **valeursRegs = (int **)malloc(9 * sizeof(int *));

  for (i = 0; i < 9; i++)
    memcpy(valeursRegs[i], valeurs, sizeof(valeurs));

  for (i = 0; i < 9; i++) //Région
  {
    for (j = 0; j < 9; j++) //Case
    {
      for(k = 0; k < 9; k++) //Valeur du tableau
        if(estDans(valeursRegs[k], regions[i][j]))
          valeursRegs[k] = 0;
    }
  }
  return valeursRegs;
}


void verifierFicher() {
  // Checker si c'est la bonne taille
  // Si elle est valide de base
  //   - Si c'est les bons caractères
  //   - Si les caractères sont bien placés (pas deux fois le même
  //     sur la même ligne ou la même colonne.
}

/**
 * Affiche une erreur passé en paramètre et sort du programme
 * avec un code d'erreur 1.
 */
void erreur(const char* message) {
  printf("Erreur : %s", message);
  exit(1);
}

void afficherOptions(char *name) {
  printf("Utilisation: %s [fichier] [options]", name);

  printf("\n\n");

  printf("--help:      Affiche cette aide.\n");
  printf("--verbose:   Solve en détaillant les operations.\n");
  printf("--timeAlert: Temps en millisecondes pour arrêter la resolution\n");
  printf("             de la grille si le temps donne est depasse.\n");

  exit(0);
}

/**
 * Fonction qui vérifie si une option a été passée en paramètre
 * en ligne de commande.
 */
bool option(int argc, char** argv, char* option) {
  for (int i = 0; i < argc; i++)
    if (strcmp(argv[i], option) == 0)
      return true;

  return false;
}

/**
 * Fonction qui récupère la valeur passé en paramètre
 * de l'otpion 'timeAlert'.
 */
void timeAlert(int argc, char** argv, float *valeur) {
  int i;

  for (i = 0; i < argc; i++)
    if (strcmp(argv[i], "--timeAlert") == 0)
      break;

  *valeur = strtof(argv[i+1], NULL);
}

int main(int argc, char** argv) {
  Grille *grille = (Grille *)malloc(sizeof(Grille));

  int i = 0, j;
  bool  verbose;
  float time_alert;

  if (argc == 1 || option(argc, argv, "--help"))
    afficherOptions(argv[0]);

  char *nom_fichier = argv[1];
  int nbLignes = nombreLignes(nom_fichier);

  printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  verbose = option(argc, argv, "--verbose");

  if (option(argc, argv, "--timeAlert"))
    timeAlert(argc, argv, &time_alert);

  charger(nom_fichier, grille, i);
  printf("Grille %d\n", i);
  afficher(grille);
  printf("\n\n");

  int **regs = regions(grille);
  remplirRandom(grille);
  afficher(grille);

  // int **valeursReg = valeursRegions(regs);

  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      printf("%d -", i);

  for (i = 0; i < nbLignes; i++) {
    charger(nom_fichier, grille, i);
    afficher(grille);
  }

  return 0;
}
