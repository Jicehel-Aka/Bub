# BUB — portage Gamebuino AKA

Portage sur console Gamebuino AKA (ESP32-S3, 320x240) d'un jeu de plateforme
à base de grille (version d'origine HTML5).

## Structure

```
BUB/
  CMakeLists.txt        Projet ESP-IDF (project(BUB))
  sdkconfig
  main/                 Composant applicatif (tout le source du jeu)
    CMakeLists.txt      idf_component_register (SRCS / INCLUDE_DIRS / REQUIRES)
    app_main.cpp        Point d'entree
    core/               Game, Input, Renderer, Constants, Assets
    game/               Level, LevelManager, Player, Bubble, TileType, Levels
    ui/                 (a venir)
    assets/             sprites / fonts / levels (a convertir)
  components/
    gamebuino/          Bibliotheque AKA (gb_core, gb_lib, gb_ll...)
  docs/                 Notes d'architecture, logique de jeu, format des niveaux
  tools/
    update.py           Genere game/Levels.cpp depuis index.html (HTML5)
  tests/                (a venir)
```

## Niveaux

`main/game/Levels.cpp` (111 niveaux) est **genere** par `tools/update.py`.
Ne pas l'editer a la main : modifier la source HTML5 puis relancer le script.
Le format de `LevelDef` (`main/game/Levels.h`) doit rester synchrone avec la
sortie du script : `{ Difficulty, bool experimental, rows[8] }`.

## Coquille (shell)

`main/shell/` fournit l'ossature commune :

- `Shell.*`   init materiel (gb_core/gb_graphics/gb_audio globaux), boucle titre/menu/jeu
- `Menu.*`    ecran-titre, menu principal, selecteur de langue, ecran des regles
- `I18n.*`    5 langues FR/EN/DE/ES/IT (textes sans accents = police 8x8 de base)
- `Config.*`  sauvegarde langue + son + niveau dans /sdcard/BUB/CFG.DAT (dossier de l'appli, nom 8.3)
- `Loader.*`  retour Launcher : selectionne app1 (OTA_1) comme partition de boot + esp_restart

Controles : D-Pad = deplacement menu, A = valider, B = retour,
MENU (court) = retour menu depuis le jeu, HOME (RUN)+MENU maintenus 500 ms = retour immediat au Launcher.


## Jeu

Puzzle-plateforme sur grille 8x8 (`core/Game.*`, `game/*`), fidele a l'original :
inventaire de 2 objets, marcher dans une bulle/cle l'ASPIRE, HAUT/BAS pose une
bulle sous soi et grimpe dessus (c'est ainsi qu'on monte), caisses poussables,
cle/porte, barrieres `<`/`>` a sens unique, gravite. Atteindre le drapeau = gagne.
111 niveaux (`game/Levels.cpp`), progression sauvegardee. **Sprites 16x16**
d'origine (dossier `assets/sprites/`, convertis par `tools/gen_sprites.py` en
`main/game/Sprites.cpp`, affiches via `Renderer::blit`). Details : `docs/game_logic.md`.



## Carte SD

Fichiers a copier sur la SD dans `sdcard_files/BUB/` (meme convention que les
autres jeux AKA) : `meta.json`, `screen.bmp` (160x120, BMP 16 bits RGB565), `lang/*.json` (5 langues),
`Sons/`, et `firmware.bin` (a generer via `idf.py build`). Voir `sdcard_files/README.txt`.

## Version PC (SDL2)

Le meme jeu tourne sur PC via un backend SDL2 (dossier `pc/`) : `backend_sdl.cpp`
implemente l'API `gb_core`/`gb_graphics`/`gb_audio_player` avec SDL, et
`main_sdl.cpp` lance la meme coquille. Aucune ligne du jeu n'est modifiee
(seuls le chemin de sauvegarde et le retour-loader different, via `-DBUB_PC`).
Build : `cd pc && make` (necessite SDL2 de dev). Details : `pc/README.md`.

## Licence & credits

Portage de **BUB** (c) 2014-2019 Owen Swerkstrom (penduin / smogheap),
jeu original sous **GNU GPL v3** : https://gitlab.com/smogheap/bub
Ce portage est donc lui aussi distribue sous **GPL-3.0-only** (voir `LICENSE`).
Les 111 niveaux et la logique de jeu derivent directement de l'original.
Aucun asset graphique/sonore d'origine n'est inclus (rendu vectoriel).
Details et resume des modifications : `CREDITS.md`.

La bibliotheque `components/gamebuino` (c) Gamebuino est sous **LGPL**
(compatible GPLv3) ; voir `components/gamebuino/LICENSE.txt`.
