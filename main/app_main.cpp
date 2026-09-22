/*
 * Part of the BUB port to the Gamebuino AKA console.
 *
 * BUB and its level designs (c) 2014-2019 Owen Swerkstrom (penduin / smogheap).
 * Original: https://gitlab.com/smogheap/bub
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * This file is free software under the GNU GPL v3; see the LICENSE file.
 */
/**
 * @file app_main.cpp
 * @brief Point d'entree : demarre la coquille BUB (titre / menu / jeu).
 */

#include "shell/Shell.h"

extern "C" void app_main(void)
{
    shell::run();   // ne revient pas
}
