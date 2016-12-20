## Algorithme de Sudoku

Pour compiler le fichier, il faut avoir un compilateur (GCC ici) et l'outil make, puis
pour compiler exécuter simplement

$ make

Puis lancer le fichier main en lui passant un fichier de grille. Par exemple :

$ ./main grilles/grille.txt

Différentes options sont passables :

$ ./main grilles/grille.txt --verbose
$ ./main grilles/grille.txt --timeAlert 2.5

L'option `--verbose` permet d'afficher les grilles une fois qu'elles sont résolues
ainsi que le temps que cela a prit et l'option `--timeAlert` permet d'imposer une
limite de temps pour résoudre les grilles du fichier.