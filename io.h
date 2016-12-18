/**
 * @author Samuel Bazniar
 * @author Robin Dupret
 */

#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>

#include "grille.h"

void erreur(const char* message);

void affichage(Grille *grille);

void ecrire(Grille *grille);

#endif
