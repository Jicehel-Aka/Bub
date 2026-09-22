/**
 * @file Shell.h
 * @brief Coquille BUB : initialise le materiel puis enchaine titre / menu / jeu.
 *
 * Gere ecran-titre, menu, multilingue (5 langues), option son, sauvegarde SD
 * et retour au loader (RUN+MENU 500 ms, ou entree QUITTER du menu).
 */

#pragma once

namespace shell
{
    //! Point d'entree unique appele depuis app_main(). Ne revient pas.
    void run();
}
