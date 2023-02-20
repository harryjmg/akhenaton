#akhenaton
Résolveur de problèmes d'échecs (langage C, sans GUI)

=====================---------

Overview :
Modeste et loin d'être parfait, akhenaton résoud des problèmes d'échecs.
Les problèmes en 1 ou 2 coups sont résolus instantanément.
Les problèmes en 3 coups ou plus mettent beaucoup de temps à être résolus et sont parfois non résolus.

Je le met en ligne car sa simplicité est suceptible d'aider les débutants en la matière.

=====================---------

How To Use :
Au lancement le programme attendra un problème d'échecs suivant ces exemples (notation FEN) :
- "8/8/8/5k2/2Q2P2/5P2/3K4/8 w 1" (blanc mat en 1 coup)
- "6k1/P1R2ppp/b7/8/8/7P/2r2PPK/r7 w 2" (blanc mat en 2 coup)
- "3n4/6K1/5R1r/6k1/7p/6pP/5P2/8 w -" (blanc mat en x coups)

Puis le programme affichera une solution (ou pas si elle n'est pas trouvée)

=====================---------

Not implemented :
- Le programme ne gère pas le roque et les captures "en passant".
- La recherche (un simple minimax) n'intègre pas d'alpha beta ou de tables de transpositions.

Harry Jmg.
