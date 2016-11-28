# Compte rendu - Algorithme et programmation

**Samuel Bazniar** - **Robin Dupret**

Le but de ce projet est de réaliser un solveur de Sudoku le plus rapide
possible. Nous avons étudié les différents algorithmes existants et réalisé
l'implémentation de certains d'entre eux afin de tester leur rapidité face
à différentes grilles de test.

Nous avons constaté qu'aucun algorithme n'était le meilleur quelque soit le
type de grille proposé (i.e. grille facile ou complexe).

Les différents algorithmes implémentés sont:

* Backtracking
* Le brute-forcing

## Méthodologie

### Collaboration par le biais de Git

Pour collaborer facilement sur les mêmes portions de code, nous avons mis en place un dépôt Git sur la forge GitHub. Cela nous permet de partager le code facilement et d'éviter de supprimer le travail de l'autre lorsque l'on travaille en même temps sur le même fichier.

### Structuration des données

Nous sommes partit du principe que plutôt que d'essayer de répartir correctement l'utilisation des ressources entre la RAM et le processeur, puisque nous cherchons simplement à être le plus rapide possible, nous stockons plusieurs fois une même grille mais sous différentes représentations (une en tableau de lignes, une en tableau de régions et une en tableau de colonnes).

Ainsi, les parcours sont faits de manière plus rapide car il n'y a pas de boucles imbriquées et il n'y a que deux accès mémoire par parcours plutôt que trois (un accès pour récupérer la région, puis un pour récupérer la ligne ou la colonne puis finalement un pour la valeur de la case).

Optimiser les parcours est très important car on réaliser en permanence des vérifications sur la grille pour savoir si elle est valide au fur et à mesure qu'on la remplit.

Pour vérifier cette hypothèse, nous avons réalisé un *benchmark* où l'on parcours chaque représentation de la grille et l'on additionne chaque élément. On calcul le nombre de fois où chaque fonction peut réaliser cette opération en 5 secondes et on compare le nombre d'itérations.

#### Description du *benchmark* en pseudo-code

Fonction utilisant une représentation "classique" avec

~~~
fonction alancienne(Entrée: grille[9][3][3])
  var i, j, k, somme : entier
début
  somme <- 0;

  // On réalise l'opération trois fois car on a 3 représentations
  // différentes pour parcourir la grille avec l'autre technique.
  faire 3 fois
    pour i de 1 à 9 faire
      pour j de 1 à 3 faire
        pour k de 1 à 3
          somme <- somme + grille[i][j][k];
        fin
      fin
    fin
  fin
fin
~~~

Fonction utilisant un tableau pour chaque représentation (représentation en tableau de lignes, en tableau de colonnes et en tableau de régions):

~~~
fonction nouvelle(Entrée: regions[9][9], lignes[9][9], colonnes[9][9])
  var i, j
début
  somme <- 0;

  pour i de 1 à 9 faire
    pour j de 1 à 9 faire
      somme <- somme + regions[i][j];

  pour i de 1 à 9 faire
    pour j de 1 à 9 faire
      somme <- somme + lignes[i][j];

  pour i de 1 à 9 faire
    pour j de 1 à 9 faire
      somme <- somme + colonnes[i][j];
fin
~~~

### Exécution du *benchmark*

Configuration utilisée pour exécuter le *benchmark*:

* Processeur: 2,7 GHz Intel Core i5
* RAM: 8 Go 1867 MHz DDR3
* Système d'exploitation: macOS Sierra (10.12.1)

Le *benchmark* a été implémenté en C et exécuté 20 fois et les résultats sont les suivants (où "i/s" signifie itération par seconde) :

| Algorithme | Moyenne | Écart type |
|------------|---------|------------|
| Tableau 9*3*3 | 1 531 541 i/s | ± 3.789% |
| Représentations multiples | 1 593 707 i/s | ± 2.87% |

La représentation en multiples tableau de la grille permet de réaliser près de 61 705 itération de plus par seconde en moyenne.

## Bibliographie es différents algorithmes

* https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
