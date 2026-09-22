/*
 * main_sdl.cpp — point d'entree de la version PC (SDL2) de BUB.
 * Lance exactement la meme coquille que sur la Gamebuino AKA.
 *
 * Part of the BUB port. SPDX-License-Identifier: GPL-3.0-only
 */

#include "shell/Shell.h"

// Sous Windows, SDL2main fournit WinMain qui appelle SDL_main : il faut inclure
// <SDL.h> dans l'unite qui definit main() pour que la macro renomme main ->
// SDL_main. Sans effet nuisible sur Linux/macOS.
#include <SDL.h>

int main(int /*argc*/, char** /*argv*/)
{
    shell::run();   // ne revient pas ; on quitte par la fenetre, Echap ou Q
    return 0;
}
