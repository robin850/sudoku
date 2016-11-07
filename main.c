#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	unsigned int ligne[3];
	unsigned int colonne[3];
} region;

typedef struct {
	region regions[9];
} grille;

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
  int i;
  bool  verbose;
  float time_alert;

  char nom_fichier[] = "grille.txt";

  int *grille  = (int*)malloc(81 * sizeof(int));
  int nbLignes = nombreLignes(nom_fichier);

  printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  if (argc == 1 || option(argc, argv, "--help"))
    afficherOptions(argv[0]);

  verbose = option(argc, argv, "--verbose");

  if (option(argc, argv, "--timeAlert"))
    timeAlert(argc, argv, &time_alert);

  int *tab = (int *)malloc(nbLignes * sizeof(int));

  for (i = 0; i < nbLignes; i++) {
    recupererGrille(nom_fichier, grille, i);
    afficherGrille(grille);
  }

  return 0;
}
