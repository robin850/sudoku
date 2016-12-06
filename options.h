#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <sys/time.h>
#include <sys/resource.h>

void afficherOptions(char *name);

bool option(int argc, char** argv, char* option);

void timeAlert(int argc, char** argv, float *valeur);

double temps();
