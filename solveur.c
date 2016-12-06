#include "solveur.h"

/**
 * Résoud une grille passée en paramètre avec la méthode
 * du backtracking. L'algorithme est implémenté de manière
 * récursive.
 *
 * Le premier appel est fait en passant 0 en position et
 * la fonction est appelée récursivement en incrémentant
 * la position.
 *
 * Elle renvoie un booléen afin de savoir si elle est
 * toujours valide ou non et dès que la grille n'y ait
 * plus, le fait que la fonction soit récursive permet
 * d'annuler les coups joués qui rendent la grille
 * invalide.
 *
 * @param  grille   - La grille à résoudre.
 * @param  position - Position à laquelle tenter de placer
 *                    un coup.
 * @return bool
 */
bool backtracking(Grille *grille, int position) {
  int ligne   = position / 9;
  int colonne = position % 9;
  int valeur;

  if (position == 81)
    return true;

  if (grille->lignes[ligne][colonne].deBase)
    return backtracking(grille, position+1);

  for (valeur = 1; valeur <= 9; valeur++) {
    if (absentLigne(grille, valeur, ligne)     &&
        absentColonne(grille, valeur, colonne) &&
        absentRegion(grille, valeur, ligne, colonne)) {
      grille->lignes[ligne][colonne].valeur = valeur;

      if (backtracking(grille, position+1))
        return true;
    }
  }

  grille->lignes[ligne][colonne].valeur = 0;

  return false;
}
