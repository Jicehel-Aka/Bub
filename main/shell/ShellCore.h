/**
 * @file ShellCore.h
 * @brief Etat interne partage de la coquille (instances materielles, helpers).
 *        Inclus par Shell.cpp et Menu.cpp — pas par le reste du jeu.
 */

#pragma once

#include <stdint.h>
#include "gamebuino.h"     // gb_core, gb_graphics, gb_audio_player
#include "Config.h"

namespace shell
{
    // Instances materielles globales (convention "g_core" du projet).
    extern gb_core          g_core;
    extern gb_graphics      g_gfx;
    extern gb_audio_player  g_audio;

    // Configuration courante (langue, son).
    extern Config           g_cfg;

    // Palette (initialisee au demarrage).
    extern uint16_t COL_BG;
    extern uint16_t COL_FG;
    extern uint16_t COL_HL;   // surbrillance
    extern uint16_t COL_DIM;  // texte attenue

    // Applique le volume master selon g_cfg.sound.
    void applyVolume();

    // Debut de frame : lit les entrees et gere HOME(RUN)+MENU 500 ms -> Launcher.
    // Ne revient pas si le combo loader est declenche.
    void frameBegin();

    // Fin de frame : envoi ecran + cadence.
    void frameEnd();

    // Texte 8x8 (police ASCII de base). Largeur glyphe = 8 px.
    void text(int x, int y, const char* s);
    void textCenter(int y, const char* s);
}
