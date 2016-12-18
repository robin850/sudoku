/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#ifndef SOLVEUR_H
#define SOLVEUR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "grille.h"

bool backtracking(Grille *grille, int position);

void remplirRandom(Grille *grille);

int *nbErreursRegions(Grille *grille);

int sommeErreursRegions(int *nbErreursRegions);

int *nbErreursLignes(Grille *grille);

int *nbErreursColonnes(Grille *grille);

int maxErreurs(int *nbErreursLigne, int *nbErreursColonne);

void remplirRandomRegion(Grille *grille, int idRegion);

#endif
