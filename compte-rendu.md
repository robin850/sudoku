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

Le dépôt est disponible ici : https://github.com/robin850/sudoku.

### Structuration de la grille

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
| Tableau 9\*3\*3 | 1 531 541 i/s | ± 3.789% |
| Représentations multiples | 1 593 707 i/s | ± 2.87% |

La représentation en multiples tableau de la grille permet de réaliser près de 61 705 itérations de plus par seconde en moyenne.

### Réalité

En réalité, cette structuration en différentes représentations ne nous permet pas d'avoir de réelles meilleures performances. Le *benchmark* ne teste pas ce qu'il se passe en réalité car on n'incrémente bêtement l'indice de la région, il n'y a pas besoin de la déterminer alors que lorsque l'on résoud une grille, il faut soit déterminer la région à partir de la position soit la passer en paramètre à la fonction de résolution mais il faut alors vérifier s'il y a besoin de l'incrémenter ou non à chaque nouvel appel récursif.

Nous avions implémenté la détermination du numéro de région de cette façon :

~~~c
int region;

if (colonne < 3)
  region = ligne < 3 ? 0 : (ligne < 6 ? 3 : 6);
else if (colonne < 6)
  region = ligne < 3 ? 1 : (ligne < 6 ? 4 : 7);
else
  region = ligne < 3 ? 2 : (ligne < 6 ? 5 : 8);
~~

Nous n'avons pas réalisé de réel *benchmark* de cette implémentation car la différence du temps de résolution avec une implémentation “classique” était visible d'un point de vue humain. Les performances étaient drastiquement moins bonnes ; une grille mettait parfois plus de deux secondes à être resolue.

Au final, nous avons décidé de conserver tout de même la représentation sous forme de régions car elle était pratique pour l'implémentation de la résolution Stochastique.

## Implémentation

### Back-tracking

L'implémentation du *backtracking* a été en réalité assez simple. On tente simplement de placer des valeurs et tant que la grille est valide, on réalisé des appels récursifs pour tenter de placer d'autres coups. L'avantage d'avoir implémenté le *backtracking*  en récursif est que du coup, il est très simple d'annuler des coups joués ; si la grille n'est pas valide, on remet simplement la valeur de la case à 0 et la ligne de remise à zéro n'est appelé que si aucun appel récursif n'a été fait (i.e. aucun coup valide n'a pu être placé).

Dans un premier temps, nous pensions que l'ajout du champ `deBase` à la structure aurait pu être utile pour savoir si une case devait être remise à zéro ou non lorsque l'on annuler un coup mais au fur et à mesure de l'implémentation, l'utilisation du récursif permet d'éviter l'implémentation d'un tel champ. Il était cependant toujours nécessaire pour l'implémentation de l'algorithme stochastique. 

### Algorithme stochastique

#### Principe

Dans un premier temps, cet algorithme va remplir aléatoirement les cases vides de la grille. Ensuite, il calculera le nombre d'erreurs en ligne et en colonne. Grâce à ces calculs, nous pouvons identifier la région où il y a le plus d'erreurs (en additionnant le nombre d'erreurs de chaque ligne et de chaque colonne de la région).

Une fois cette région déterminée, il faudra la remplir aléatoirement sans doublons (donc de 1 à 9).

Enfin, nous faisons boucler le programme afin de recalculer les erreurs, déterminer la région avec le plus d'erreurs et la remplir, jusqu'à ce qu'il n'y ait plus d'erreurs et donc que la grille soit résolue.

#### Explication du code

La fonction `remplirRandom` permet de remplir les éléments n'étant pas de base dans la grille. Nous pouvons vérifier cette condition grâce au booléen placé dans la structure `Case` :

- Si le booléen est vrai, alors on ne touche pas à la valeur
- S'l est faux, on peut le générer aléatoirement.

La fonction `nbErreursLignes` (respectivement `nbErreursColonnes`) permet de calculer, pour chaque ligne (resp. colonne), le nombre d'erreurs. Pour chaque case de la ligne (resp. colonne), on compare la valeur avec celles du tableau `valeurs` qui contient les chiffres de 1 à 9. Lorsqu'on trouve que la valeur est égale à une des valeurs du tableau, on passe la cellule du tableau à 0. Le nombre de valeurs restantes du tableau sera donc le nombre d'erreurs de la ligne (resp. colonne).

La fonction `maxErreurs` permet de déterminer la région qui a le plus d'erreurs. En effet, pour chaque région, elle calcule la somme des erreurs en ligne et en colonne. Ensuite, on cherche le maximum entre ces 9 valeurs, puis on renvoie l'id de la région où il y a le plus d'erreurs. 

La fonction `remplirRandomRegion` permet de remplir aléatoirement une région sans aucun doublon. Pour cela, nous utilisons un tableau de valeurs allant de 1 à 9.

Nous supprimons les valeurs déjà présentes dans la grille fournie (pour éviter les doublons), et nous plaçons le reste des valeurs aléatoirement dans les cases dont le booléen est à faux.

#### Execution

Pour résoudre une grille, nous faisons appel à toutes les fonctions citées ci-dessus.

```c
remplirRandom(grille); // Remplissage aléatoire de la grille
nbErreursLigne   = nbErreursLignes(grille); //Calcul des erreurs en ligne
nbErreursColonne = nbErreursColonnes(grille); //Calcul des erreurs en colonne
maximumErreurs   = maxErreurs(nbErreursLigne, nbErreursColonne); // Détermination de la région avec le plus d'erreurs
remplirRandomRegion(grille, maximumErreurs);//Génération aléatoire sans doublons de la région avec le plus d'erreurs

do {
  nbErreursLigne   = nbErreursLignes(grille);
  nbErreursColonne = nbErreursColonnes(grille);
  maximumErreurs   = maxErreurs(nbErreursLigne, nbErreursColonne);
  remplirRandomRegion(grille, maximumErreurs);
} while (maximumErreurs != -1); // Tant que la grille n'est pas valide, on boucle
```

Malheureusement, nous n'avons pas réussi à implémenter correctement cet algorithme car nous n'arrivons pas à sortir de la boucle `while`. Peu importe la difficulté de la grille, nous avons une boucle infinie qui nous empêche de la résoudre.

## Bibliographie es différents algorithmes

* https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
