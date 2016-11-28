#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "grille.h"

typedef struct {
	unsigned int ligne[3];
	unsigned int colonne[3];
} region;

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

void solve (char *grille)
{
	return;
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

  int i;
  bool  verbose;
  float time_alert;

  char nom_fichier[] = "grille.txt";

  int nbLignes = nombreLignes(nom_fichier);

  printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  if (argc == 1 || option(argc, argv, "--help"))
    afficherOptions(argv[0]);

  verbose = option(argc, argv, "--verbose");

  if (option(argc, argv, "--timeAlert"))
    timeAlert(argc, argv, &time_alert);

  int *tab = (int *)malloc(nbLignes * sizeof(int));

  for (i = 0; i < nbLignes; i++) {
    charger(nom_fichier, grille, i);
    afficherGrille(grille);
  }

  return 0;
}
