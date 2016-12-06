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
  int i, j, v, compteur = 0, debut, debut_ligne, k;
  for (i = 0; i < 81; i++)
    if (grille->tableau[i].deBase == false) {
      do {
        v = (rand() %10);
      } while (v == 0);
      grille->tableau[i].valeur = v;
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

int nbErreursRegion(Grille *grille, int idRegion)
{
  int i, j, nbErreur = 0, valeurs[9] = {1,2,3,4,5,6,7,8,9};

  //Création de la région demandée
  int *region = (int*)malloc(9*sizeof(int));
  for (i = 0; i < 9; i++)
    region[i] = grille->regions[idRegion][i].valeur;

  for (i = 0; i < 9; i++)
    printf("%d ", grille->regions[idRegion][i].valeur);

  //Met les valeurs à 0 quand il la trouve dans la région
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
     if(grille->regions[idRegion][i].valeur == valeurs[j])
        valeurs[j] = 0;

  //Compte les erreurs
  for(i = 0; i < 9; i++)
    if(valeurs[i] != 0)
      nbErreur++;

  return nbErreur;
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
  int i, j, ligne, colonne;
  Case *region = (Case*)malloc(9*sizeof(Case));
  for (i = 0; i < 9; i++)
  {
    region[i].valeur = grille->regions[idRegion][i].valeur;
    region[i].deBase = grille->regions[idRegion][i].deBase;
  }

  srand(time(NULL));
  int v;

  for (i = 0; i < 9; i++)
    if (region[i].deBase == false) {
      do {
        v = rand() % 10;
      } while (v == 0);

      region[i].valeur = v;
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

void verifierFicher() {
  // Checker si c'est la bonne taille
  // Si elle est valide de base
  //   - Si c'est les bons caractères
  //   - Si les caractères sont bien placés (pas deux fois le même
  //     sur la même ligne ou la même colonne.
}

int main(int argc, char** argv) {
  Grille *grille = (Grille *)malloc(sizeof(Grille));

  int i = 0;
  bool  verbose;
  float time_alert;
  double debut, fin, total = 0.0;

  if (argc == 1 || option(argc, argv, "--help"))
    afficherOptions(argv[0]);

  char *nom_fichier = argv[1];
  int nbLignes = nombreLignes(nom_fichier);

  printf("Nombres de grilles dans le fichier : %d\n", nbLignes);

  verbose = option(argc, argv, "--verbose");

  if (option(argc, argv, "--timeAlert"))
    timeAlert(argc, argv, &time_alert);

  // +------------------------------------------------+
  // | Boucle résolvant toutes les grilles du fichier |
  // +------------------------------------------------+
  for (i = 0; i < nbLignes; i++) {
    charger(nom_fichier, grille, i);
    printf("Grille %d\n", i+1);

    debut = temps();
    total += debut;

    backtracking(grille, 0);

    fin = temps();

    afficher(grille);
    ecrire(grille);

    printf("\nLa grille n°%d a ete resolue en %lf secondes.\n\n", i+1, (fin - debut));
  }


  //Remplissage aléatoire
  // remplirRandom(grille);
  // afficher(grille);

  //Calculs des erreurs en lignes et colonnes
  // int *nbErreursLigne;
  // int *nbErreursColonne;
  // int maximumErreurs; //Renvoie la région à random

  // do {
  //   nbErreursLigne = nbErreursLignes(grille);
  //   nbErreursColonne = nbErreursColonnes(grille);
  //   maximumErreurs = maxErreurs(nbErreursLigne, nbErreursColonne);
  //   remplirRandomRegion(grille, maximumErreurs);

  //   printf("Région : %d.\n", maximumErreurs);
  // } while (maximumErreurs != -1);

  //Affichage du nombre d'erreurs
  //printf("%d erreurs dans la région %d.\n", nbErreursRegionId, idRegion);
  // for (i = 0; i < 9; i++)
  //   printf("Il y a %d erreurs dans la ligne %d\n", nbErreursLigne[i], i+1);
  // for (i = 0; i < 9; i++)
   // printf("Il y a %d erreurs dans la colonne %d\n", nbErreursLigne[i], i+1);
  // printf("Région : %d\n", maximumErreurs);
  // remplirRandomRegion(grille, maximumErreurs);
  // afficher(grille);
  return 0;
}
