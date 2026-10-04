# BUB Game Logic

| Symbole | Description |
|----------|-------------|
| # | Wall |
| H | Ladder |
| o | Bubble |
| - | Key |
| X | Door |
| = | Crate |
| < | Conveyor Left |
| > | Conveyor Right |
| @ | Player Spawn |
| 4 | Goal |
| space | Empty |

## Mecaniques

Puzzle-plateforme sur grille 8x8. Le joueur (l'ork) subit la gravite.

- **Deplacement** : Gauche/Droite pour marcher.
- **Aspirer** : marcher dans une bulle/cle la met dans l'inventaire (2 max), sans avancer.
- **Monter** : HAUT/BAS (hors echelle) pose une bulle sous soi et grimpe dessus.
- **Echelles (H)** : Haut/Bas pour monter/descendre ; on ne tombe pas dessus.
- **Caisses (=)** : se poussent horizontalement vers une case vide ; elles tombent.
- **Cle (-) / Porte (X)** : la porte est solide tant que la cle n'est pas ramassee.
- **Tapis (< >)** : sol solide qui transporte le joueur pose dessus.
- **Bulles (o)** : a collecter toutes avant de pouvoir valider le drapeau.
- **Drapeau (4)** : atteint avec 0 bulle restante => niveau reussi.

Boucle : niveau reussi -> A (suivant) / B (rejouer). Dernier niveau -> ecran final.
En jeu : B recommence le niveau, MENU revient au menu, HOME(RUN)+MENU (500 ms) au Launcher.
La progression (niveau atteint) est sauvegardee dans /sdcard/BUB/CFG.DAT.
