# BUB sur PC via le backend SDL officiel (jmp42)

Cette methode fait tourner **le vrai code AKA** de BUB sur PC : le backend
`Gamebuino_AKA_lib_sdl` recompile le `gb_lib` embarque dans
`components/gamebuino` et remplace la couche `gb_ll_*` (ecran, audio, SD,
boutons) par SDL2. Rendu, mixeur 44100 Hz mono, police, taches : identiques a
la console. C'est preferable au dossier `pc/` (backend ecrit a la main) qui
reste comme solution de repli autonome.

## Prerequis (MSYS2 MinGW64)

```
pacman -S mingw-w64-x86_64-{gcc,cmake,ninja,SDL2}
```

Recuperer le backend, p.ex. dans `C:/github/Gamebuino_AKA_lib_sdl`.

## Compiler

Depuis le dossier `BUB/` :

```
cmake -S sdl -B sdl/build -G Ninja -DAKA_SDL_BACKEND=C:/github/Gamebuino_AKA_lib_sdl
cmake --build sdl/build
```

Produit `sdl/build/bub.exe` (ou `bub` sous Linux/macOS). Aucun `main` a ecrire :
le backend appelle `app_main`.

## La carte SD = un dossier

BUB lit/ecrit sous `/sdcard`. On pointe cette racine vers un dossier hote qui
contient l'arborescence de la carte (dont `BUB/`) :

```
# Windows (cmd)
set GB_SDL_SDCARD=%CD%\sdcard_files
# Linux / macOS
export GB_SDL_SDCARD="$PWD/sdcard_files"
```

`sdcard_files/` (fourni dans le repo) contient deja `BUB/meta.json`,
`BUB/screen.bmp`, `BUB/lang/*.json`, etc. La sauvegarde `CFG.DAT` y sera creee.
Sans variable, le backend cree un dossier `sdcard/` a cote de l'executable.

## Lancer / options

```
sdl/build/bub          # ou bub.exe
```

Variables d'environnement du backend : `GB_SDL_SCALE=4` (fenetre plus grande),
`GB_SDL_MUTE=1` (silence), `GB_SDL_EXIT_AFTER=5` (quitte apres 5 s).
Les touches (nommees selon ton clavier) sont affichees au demarrage ;
**Echap = RUN** (extinction => fin du programme).
