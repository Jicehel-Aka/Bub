/**
 * @file I18n.h
 * @brief Multilingue (5 langues) de la coquille BUB.
 *
 * Textes volontairement SANS accents : ils s'affichent avec la police 8x8
 * ASCII de base (gb_graphics::print_str). Pour des accents, generer une
 * police accentuee (gen_font.py) puis fournir les variantes accentuees.
 */

#pragma once

#include <stdint.h>

enum Lang : uint8_t
{
    LANG_FR = 0,
    LANG_EN,
    LANG_DE,
    LANG_ES,
    LANG_IT,
    LANG_COUNT
};

enum Str : uint8_t
{
    S_PRESS_START = 0,  // ecran-titre
    S_PLAY,             // menu : jouer
    S_LANGUAGE,         // menu : langue
    S_SOUND,            // menu : son
    S_RULES,            // menu : regles
    S_QUIT,             // menu : quitter (retour loader)
    S_ON,
    S_OFF,
    S_BACK,             // B = retour
    S_RULES_TITLE,
    S_LEVEL,            // jeu : "NIVEAU"
    S_COMPLETE,         // jeu : niveau reussi
    S_WIN,              // jeu : tout termine
    S_CONTINUE,         // jeu : A = suite
    S_RESTART,          // jeu : B = recommencer
    S_CLIMB,            // jeu : action monter/poser
    S_CREDITS,          // menu : credits
    S_COUNT
};

namespace i18n
{
    Lang        current();
    void        set(Lang lang);
    const char* tr(Str id);
    const char* langName(Lang lang);
    uint8_t     rulesLineCount();
    const char* rulesLine(uint8_t index);
}
