/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include "io.h"
#include "options.h"

/**
 * Affiche les options qui peuvent être utilisées avec le programme
 * et quitte via `exit`. Ce message est affiché quand trop peu
 * d'arguments sont passés.
 *
 * @param  name - Nom du fichier executé (i.e. main)
 * @return void
 */
void afficherOptions(char *name) {
  printf("Utilisation: %s fichier [options]", name);

  printf("\n\n");

  printf("--help:      Affiche cette aide.\n");
  printf("--verbose:   Solve en détaillant les operations.\n");
  printf("--timeAlert: Temps en secondes pour arrêter la resolution\n");
  printf("             des grilles si le temps donne est depasse.\n");

  exit(0);
}

/**
 * Fonction qui vérifie si une option a été passée en paramètre
 * en ligne de commande.
 *
 * @param  argc   - Nombre d'arguments
 * @param  argv   - Tableau d'arguments
 * @param  option - Nom de l'option
 * @return bool
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
 *
 * @param  argc   - Nombre d'arguments
 * @param  argc   - Tableau d'arguments
 * @param  valeur - Pointeur sur la variable contenant la valeur
 * @return void
 */
void timeAlert(int argc, char** argv, float *valeur) {
  int i;

  for (i = 0; i < argc; i++)
    if (strcmp(argv[i], "--timeAlert") == 0)
      break;

  *valeur = strtof(argv[i+1], NULL);
}

/**
 * Permet de récupérer la date courante sous forme
 * de timestamp. Utile pour mesurer le temps que
 * prend la résolution d'une grille.
 *
 * @return double
 */
double temps() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec*1e-6;
}
