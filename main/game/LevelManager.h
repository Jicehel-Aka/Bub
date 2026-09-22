/**
 * @file LevelManager.h
 * @brief Acces a la base de niveaux LEVELS[].
 */

#pragma once

#include <stdint.h>

class Level;

class LevelManager
{
public:
    bool     loadLevel(uint16_t id, Level& level);
    uint16_t getLevelCount() const;
};
