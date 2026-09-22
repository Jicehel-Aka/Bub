# BUB — version PC (SDL2)

Portage bureau de BUB. Le jeu et la coquille sont **exactement les mêmes** que
sur la Gamebuino AKA : seul le « bas niveau » change. `backend_sdl.cpp`
implémente l'API `gb_core` / `gb_graphics` / `gb_audio_player` avec SDL2, et
`main_sdl.cpp` lance la même `shell::run()`.

## Prérequis

- Un compilateur C++17 (g++ / clang / MinGW).
- SDL2 (développement) :
  - Debian/Ubuntu : `sudo apt install libsdl2-dev`
  - Fedora : `sudo dnf install SDL2-devel`
  - macOS (Homebrew) : `brew install sdl2`
  - Windows (MSYS2) : `pacman -S mingw-w64-x86_64-SDL2`

## Compiler & lancer

```sh
cd pc
make          # produit ./bub
make run      # compile puis lance
```

Le `Makefile` détecte SDL2 via `pkg-config` (ou `sdl2-config`).

## Commandes

| Touche(s)              | Action                          |
|------------------------|---------------------------------|
| Flèches                | déplacement / navigation menu   |
| Z ou Entrée            | A (valider / niveau suivant)    |
| X ou Retour arrière    | B (annuler / recommencer)       |
| M ou Tab               | MENU (retour au menu)           |
| Maj (gauche/droite)    | RUN                             |
| Maj + M (≥ 0,5 s)      | « retour loader » → quitte      |
| Échap ou Q             | quitter                         |

## Notes

- La fenêtre est en 320×240 logiques, agrandie ×3 (960×720), redimensionnable.
- Rendu **vectoriel** (primitives SDL) et police 8×8 — pas d'assets externes.
- La configuration (langue, son, niveau atteint) est sauvegardée dans
  `pc/bub_save.dat` (au lieu de `/sdcard/CFG.DAT` sur la console).
- Aucune modification du code du jeu : `-DBUB_PC` ne change que le chemin de
  sauvegarde (`Config.cpp`) et le « retour loader » (`Loader.cpp`, qui quitte).

## Licences des composants tiers de cette cible

- **SDL2** — licence zlib (compatible GPL).
- **font8x8** (Daniel Hepper) — domaine public.

Le jeu lui-même reste sous **GNU GPL v3** (voir `../LICENSE` et `../CREDITS.md`).
