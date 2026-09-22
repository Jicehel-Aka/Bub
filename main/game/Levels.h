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
 * @file Levels.h
 * @brief Base de niveaux embarquée (BUB).
 *
 * Généré par tools/update.py depuis la version HTML5 (index.html).
 * Le format DOIT rester synchrone avec ce que produit update.py :
 *   { Difficulty, bool experimental, rows[8] }.
 */

#pragma once

#include <stdint.h>

enum class Difficulty : uint8_t
{
    Beginner,
    Easy,
    Intermediate,
    Advanced,
    Experimental
};

struct LevelDef
{
    Difficulty  difficulty;
    bool        experimental;
    const char* rows[8];
};

extern const LevelDef LEVELS[];
extern const uint16_t LEVEL_COUNT;
