/**
 * @file Level.h
 * @brief Un niveau charge en memoire (grille 8x8 de tuiles).
 */

#pragma once

#include <stdint.h>

#include "TileType.h"
#include "../core/Constants.h"

class Level
{
public:
    //! Charge le niveau @levelIndex depuis la base LEVELS[]. false si hors bornes.
    bool load(uint16_t levelIndex);

    //! Tuile a (x,y). Hors grille => Wall (bordures solides).
    TileType getTile(int x, int y) const;

    //! Ecrit une tuile (no-op hors grille).
    void setTile(int x, int y, TileType tile);

    int getStartX() const { return startX; }
    int getStartY() const { return startY; }

    uint8_t getDifficulty() const { return difficulty; }

    //! Nombre de bulles presentes au chargement.
    int bubbleCount() const { return bubbles; }

private:
    TileType grid[GRID_H][GRID_W];

    int startX = 0;
    int startY = 0;

    uint8_t difficulty = 0;
    int     bubbles     = 0;
};
