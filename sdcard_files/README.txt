Fichiers a copier sur la carte SD de la Gamebuino AKA (meme convention que les
autres jeux, ex. PAKAMAN).

Copier le dossier BUB/ a la racine de la carte SD :

  SD:/BUB/
    firmware.bin     <- a generer : build ESP-IDF (idf.py build) puis copier
                        build/BUB.bin ici sous le nom firmware.bin
    meta.json        <- titre / description / auteur / version (pour le loader)
    screen.bmp       <- vignette 160x120, BMP 16 bits RGB565 (affichee par le Launcher)
    lang/fr.json ... <- textes du jeu (5 langues) au format AKA
    Sons/            <- bruitages optionnels (voir Sons/README.txt)
    CFG.DAT          <- cree par le jeu dans ce dossier (langue, son, niveau)

Les textes de l'interface commune du Launcher restent dans SD:/AKA/lang/*.json
(partages par tous les jeux) : ne pas les dupliquer ici.

NB : le firmware embarque deja ses textes (i18n compile). Les lang/*.json sont
fournis pour respecter la convention et permettre l'edition ; brancher leur
lecture depuis la SD est une evolution possible.
