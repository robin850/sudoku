#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int ligne[3];
	unsigned int colonne[3];
} region;

typedef struct {
	region regions[9];
} grille;

FILE *chargerFichier(char *f)
{
	FILE *fic= NULL;
	
	fic = fopen(f, "r");

	if(fic != NULL)
		return fic;
	else
		return NULL;
}

int nombreLignes(FILE *f)
{
	char c;
	int nbLignes = 0;
	while((c = fgetc(f)) != EOF)
	{
		if(c == '\n')
			nbLignes++;
	}
	return nbLignes;
}

int *recupererChaine(FILE *f)
{
	int d, n = 0;
	int *chaine = (int*)malloc(81 * sizeof(int));
    while (fscanf(f, "%1d", &d) == 1 && n < 81)
    {
	   	chaine[n] = d;
	   	n++;
    } 
    return chaine;
}

void afficherGrille(int *grille) {
	int i = 0;
	printf("++---+---+---++\n");
	do
    {
        printf("%d - ", i); 
        printf("%d \n", grille[i]); 
        i++;
    } while (i < 81);
    printf("++---+---+---++\n");
    printf("\n\n");
}


FILE *solve (char *grille)
{
	return;
}

void main (int argc, char **argv)
{
	int i;

	FILE *fichier = chargerFichier("grilles.txt");
	int nbLignes = nombreLignes(fichier);
	printf("Nombres de grilles dans le fichier : %d\n", nbLignes);


	int *tab = (int *)malloc(nbLignes * sizeof(int));

	for(i = 0; i < nbLignes; i++)
	{
		tab = recupererChaine(fichier);
		afficherGrille(tab);
	}
	return;
}
