/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "grille.h"
#include "solveur.h"
#include "options.h"
#include "io.h"

int nombreLignes(char *nom_fichier) {
  FILE *fichier = fopen(nom_fichier, "r");

	int d;
	int nbLignes = 0;

	while (fscanf(fichier, "%81d", &d) == 1)
		nbLignes++;

  fclose(fichier);

	return nbLignes;
}

void remplirRandom(Grille *grille) {
  srand(time(NULL));
  int i, j, compteur = 0, debut, debut_ligne, k;
  for (i = 0; i < 81; i++)
    if (grille->tableau[i].deBase == false) {
      grille->tableau[i].valeur = rand()%9+1;
    }

  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
    {
      grille->lignes[i][j].valeur = grille->tableau[compteur].valeur;
      compteur++;
    }

  for (i = 0; i < 9; i++) {
    debut    = i < 3 ? 0 : (i < 6 ? 3 : 6);
    compteur = 0;

    for (j = debut; j < debut+3; j++) {
      debut_ligne = i % 3 == 0 ? 0 : (i % 3 == 1 ? 3 : 6);

      for (k = debut_ligne; k < debut_ligne+3; k++)
        grille->regions[i][compteur++]= grille->lignes[j][k];
    }
  }
}

int *nbErreursRegions(Grille *grille)
{
  int i, j, idRegion = 0;
  int *nbErreur = (int*)malloc(9*sizeof(int));
  //Création de la région demandée
  int *region = (int*)malloc(9*sizeof(int));

  for (i = 0; i < 9; i++)
      nbErreur[i] = 0;

  for(idRegion = 0; idRegion < 9; idRegion++)
  {
    int valeurs[9] = {1,2,3,4,5,6,7,8,9};
    for (i = 0; i < 9; i++)
      region[i] = grille->regions[idRegion][i].valeur;

    //Met les valeurs à 0 quand il la trouve dans la région
    for(i = 0; i < 9; i++)
      for(j = 0; j < 9; j++)
       if(region[i] == valeurs[j])
          valeurs[j] = 0;

    //Compte les erreurs
    for(i = 0; i < 9; i++)
      if(valeurs[i] != 0)
        nbErreur[idRegion]++;
  }

  return nbErreur;
}

int sommeErreursRegions(int *nbErreursRegions)
{
  int i, somme = 0;
  for (i = 0; i < 9; i++)
    somme += nbErreursRegions[i];
  return somme;
}

int *nbErreursLignes(Grille *grille)
{
  int i,j, k;
  int *nbErreursLigne = (int*)malloc(9 * sizeof(int));
  for (i = 0; i < 9; i++)
    nbErreursLigne[i] = 0;

  for (i = 0; i < 9; i++) //pour chaque ligne
  {
    int valeurs[9] = {1,2,3,4,5,6,7,8,9};

    for (j = 0; j < 9; j++) //pour chaque caractère
      for (k = 0; k < 9; k++) //pour chaque valeur
        if (grille->lignes[i][j].valeur == valeurs[k])
          valeurs[k] = 0;

    for(k = 0; k < 9; k++)
      if(valeurs[k] != 0)
        nbErreursLigne[i]++;
  }

  return nbErreursLigne;
}

int *nbErreursColonnes(Grille *grille)
{
  int i,j, k;
  int *nbErreursColonne = (int*)malloc(9 * sizeof(int));
  for (i = 0; i < 9; i++)
    nbErreursColonne[i] = 0;

  for (i = 0; i < 9; i++) //pour chaque ligne
  {
    int valeurs[9] = {1,2,3,4,5,6,7,8,9};

    for (j = 0; j < 9; j++) //pour chaque caractère
      for (k = 0; k < 9; k++) //pour chaque valeur
        if (grille->lignes[j][i].valeur == valeurs[k])
          valeurs[k] = 0;

    for(k = 0; k < 9; k++)
      if(valeurs[k] != 0)
        nbErreursColonne[i]++;
  }

  return nbErreursColonne;
}

//Retourne l'ID de la région avec le plus d'erreurs pour la random
int maxErreurs(int *nbErreursLigne, int *nbErreursColonne)
{
  int i;
  int *max = (int*)malloc(9*sizeof(int));
  max[0] = nbErreursLigne[0] + nbErreursLigne[1] + nbErreursLigne[2] + nbErreursColonne[0] + nbErreursColonne[1] + nbErreursColonne[2];
  max[1] = nbErreursLigne[0] + nbErreursLigne[1] + nbErreursLigne[2] + nbErreursColonne[3] + nbErreursColonne[4] + nbErreursColonne[5];
  max[2] = nbErreursLigne[0] + nbErreursLigne[1] + nbErreursLigne[2] + nbErreursColonne[6] + nbErreursColonne[7] + nbErreursColonne[8];

  max[3] = nbErreursLigne[3] + nbErreursLigne[4] + nbErreursLigne[5] + nbErreursColonne[0] + nbErreursColonne[1] + nbErreursColonne[2];
  max[4] = nbErreursLigne[3] + nbErreursLigne[4] + nbErreursLigne[5] + nbErreursColonne[3] + nbErreursColonne[4] + nbErreursColonne[5];
  max[5] = nbErreursLigne[3] + nbErreursLigne[4] + nbErreursLigne[5] + nbErreursColonne[6] + nbErreursColonne[7] + nbErreursColonne[8];

  max[6] = nbErreursLigne[6] + nbErreursLigne[7] + nbErreursLigne[8] + nbErreursColonne[0] + nbErreursColonne[1] + nbErreursColonne[2];
  max[7] = nbErreursLigne[6] + nbErreursLigne[7] + nbErreursLigne[8] + nbErreursColonne[3] + nbErreursColonne[4] + nbErreursColonne[5];
  max[8] = nbErreursLigne[6] + nbErreursLigne[7] + nbErreursLigne[8] + nbErreursColonne[6] + nbErreursColonne[7] + nbErreursColonne[8];

  int maxi = max[0];
  int idRegion = 0;

  for (i = 1; i < 9; i++) {
    if(maxi < max[i])
    {
      maxi = max[i];
      idRegion = i;
    }
  }

  if(maxi == 0)
    return -1;

  return idRegion;
}

void remplirRandomRegion(Grille *grille, int idRegion)
{
  int i, j, id, ligne, colonne, valeurs[9] = {1,2,3,4,5,6,7,8,9};
  Case *region = (Case*)malloc(9*sizeof(Case));
  for (i = 0; i < 9; i++)
  {
    region[i].valeur = grille->regions[idRegion][i].valeur;
    region[i].deBase = grille->regions[idRegion][i].deBase;
  }

  srand(time(NULL));

  //Supprime les valeurs de base dans le tableau valeurs
  for (i = 0; i < 9; i++)
  {
    if (region[i].deBase == true)
    {
      for(j = 0; j < 9; j++)
        if(valeurs[j] == region[i].valeur)
          valeurs[j] = 0;
    }
  }

  for (i = 0; i < 9; i++)
  {
    if (region[i].deBase == false)
    {
      id = rand()%9;
      while(valeurs[id] == 0)
        id = rand()%9;
      region[i].valeur = valeurs[id];
      valeurs[id] = 0;
    }
  }

  //Rempli grille->lignes
  if (idRegion == 0 || idRegion == 3 || idRegion == 6)
    colonne = 0;
  else if (idRegion == 1 || idRegion == 4 || idRegion == 7)
    colonne = 3;
  else
    colonne = 6;

  if (idRegion < 3)
    ligne = 0;
  else if (idRegion < 6)
    ligne = 3;
  else
    ligne = 6;

  int compteur = 0;

  for(i = ligne; i < ligne+3; i++)
    for(j = colonne; j < colonne+3; j++, compteur++)
      grille->lignes[i][j].valeur = region[compteur].valeur;

}

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

  printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  print_opt      = option(argc, argv, "--print");
  verbose_opt    = option(argc, argv, "--verbose");
  time_alert_opt = option(argc, argv, "--timeAlert");

  if (time_alert_opt)
    timeAlert(argc, argv, &time_alert);

  // +----------------------------------------------+
  // | Boucle lisant chacune des grilles du fichier |
  // +----------------------------------------------+
  for (i = 0; i < nbLignes; i++) {
    charger(nom_fichier, grille, i);

    if (print_opt)
      printf("Grille %d\n", i+1);

    debut = temps();
    total += debut;

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

    if (print_opt)
      afficher(grille);

    ecrire(grille);

    if (print_opt)
      printf("\nLa grille n°%d a ete resolue en %lf secondes.\n\n", i+1, (fin - debut));
  }

  return 0;
}
