/**
 * @file Menu.h
 * @brief Ecrans de la coquille : titre, menu principal, langue, regles.
 */

#pragma once

namespace menu
{
    enum Action
    {
        ACT_PLAY = 0,
        ACT_LANGUAGE,
        ACT_SOUND,
        ACT_RULES,
        ACT_CREDITS,
        ACT_QUIT
    };

    //! Ecran-titre. Revient quand A est presse.
    void title();

    //! Menu principal. Renvoie l'action choisie (enum Action).
    Action mainMenu();

    //! Selecteur de langue (sauvegarde a la validation). B = annuler.
    void language();

    //! Ecran des regles. A ou B pour revenir.
    void rules();

    //! Ecran des credits / attribution. A ou B pour revenir.
    void credits();
}
