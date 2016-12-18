/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#ifndef GRILLE_H
#define GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int valeur;
	bool deBase;
} Case;

typedef struct {
  Case regions[9][9];
  Case lignes[9][9];
  Case tableau[81];
} Grille;

void charger(char *nom_fichier, Grille *grille, int ligne);

bool estValide(Grille *grille);

void afficher(Grille *grille);

bool estDans(Case *tab, int i);

bool absentLigne(Grille *grille, int valeur, int ligne);

bool absentColonne(Grille *grille, int valeur, int colonne);

bool absentRegion(Grille *grille, int valeur, int ligne, int colonne);

#endif
