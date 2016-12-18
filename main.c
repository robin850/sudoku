/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grille.h"
#include "solveur.h"
#include "options.h"
#include "io.h"

int main(int argc, char** argv) {
  Grille *grille = (Grille *)malloc(sizeof(Grille));

  int i = 0;
  int *nbErreursLigne, *nbErreursColonne, maximumErreurs;

  bool  verbose_opt, print_opt, time_alert_opt;
  float time_alert;
  double debut, fin, total = 0.0;

  if (argc == 1 || option(argc, argv, "--help"))
    afficherOptions(argv[0]);

  char *nom_fichier = argv[1];
  int nbLignes = nombreLignes(nom_fichier);


  print_opt      = option(argc, argv, "--print");
  verbose_opt    = option(argc, argv, "--verbose");
  time_alert_opt = option(argc, argv, "--timeAlert");

  if (time_alert_opt)
    timeAlert(argc, argv, &time_alert);

  if (print_opt)
    printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  // +----------------------------------------------+
  // | Boucle lisant chacune des grilles du fichier |
  // +----------------------------------------------+
  for (i = 0; i < nbLignes; i++) {
    charger(nom_fichier, grille, i);

    if (print_opt)
      printf("Grille %d\n", i+1);

    debut = temps();

    // -> Résolution par back-tracking
    backtracking(grille, 0);

    // -> Tentative en Stochastique
    // do {
    //   nbErreursLigne   = nbErreursLignes(grille);
    //   nbErreursColonne = nbErreursColonnes(grille);
    //   maximumErreurs   = maxErreurs(nbErreursLigne, nbErreursColonne);

    //   for (i = 0; i < 9; i++)
    //     remplirRandomRegion(grille, i);

    // } while (maximumErreurs != -1);

    fin = temps();
    total += fin - debut;

    if (print_opt)
      afficher(grille);

    ecrire(grille);

    if (print_opt)
      printf("\nLa grille n°%d a ete resolue en %lf secondes.\n\n", i+1, (fin - debut));

    if (time_alert_opt && total >= time_alert) {
      printf("%d grilles résolues en %lf secondes.", i+1, total);
      exit(0);
    }
  }

  return 0;
}
