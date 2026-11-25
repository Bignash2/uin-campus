Partie A:
1.Une bibliothèque statique est liée à l'exécutable lors de la compilation.
2.Une bibliothèque dynamique est chargée au lancement du programme. Sans accès à la bibliothèque, l'exécutable ne démarre pas.
3.L'exécutable lié statiquement est généralement plus gros que celui lié dynamiquement.
4.Dans nm :
T : symbole défini
U : symbole utilisé mais défini ailleurs

5.ldd affiche les bibliothèques dynamiques utilisées par un exécutable.
6.Le nom décoré contient le namespace, le nom de la fonction et sa signature.


Partie B
1.Le module doit afficher Bien.
2.Retirer export empêche l'importation du symbole par les autres unités de compilation.
3.Une fonction non exportée n'est pas visible depuis main.cpp.
4.Une macro définie dans un module n'est pas visible à l'extérieur.


Partie C
1.Les en-têtes précompilés réduisent le temps de compilation.
2.Modifier calculs.cpp recompile principalement ce fichier.
3.Modifier regles.hpp entraîne la recompilation des fichiers qui en dépendent
