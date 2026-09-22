/**
 * @file Level.cpp
 * @brief Chargement/parsing d'un niveau depuis LEVELS[].
 */

#include "Level.h"
#include "Levels.h"

#include <string.h>

namespace
{
    TileType charToTile(char c)
    {
        switch (c)
        {
            case '#': return TileType::Wall;
            case 'H': return TileType::Ladder;
            case 'o': return TileType::Bubble;
            case '-': return TileType::Key;
            case 'X': return TileType::Door;
            case '=': return TileType::Crate;
            case '<': return TileType::ConveyorLeft;
            case '>': return TileType::ConveyorRight;
            case '4': return TileType::Goal;
            case '@': return TileType::Empty;   // spawn : la case reste vide
            default:  return TileType::Empty;   // espace ou symbole inconnu
        }
    }
}

bool Level::load(uint16_t levelIndex)
{
    if (levelIndex >= LEVEL_COUNT) return false;

    const LevelDef& def = LEVELS[levelIndex];

    difficulty = static_cast<uint8_t>(def.difficulty);
    startX = 0;
    startY = 0;
    bubbles = 0;

    for (int y = 0; y < GRID_H; ++y)
    {
        const char* row = def.rows[y];
        int len = row ? (int)strlen(row) : 0;

        for (int x = 0; x < GRID_W; ++x)
        {
            char c = (x < len) ? row[x] : ' ';

            if (c == '@') { startX = x; startY = y; }

            TileType t = charToTile(c);
            grid[y][x] = t;

            if (t == TileType::Bubble) ++bubbles;
        }
    }

    return true;
}

TileType Level::getTile(int x, int y) const
{
    if (x < 0 || x >= GRID_W || y < 0 || y >= GRID_H)
        return TileType::Wall;   // hors grille = mur (bordures solides)
    return grid[y][x];
}

void Level::setTile(int x, int y, TileType tile)
{
    if (x < 0 || x >= GRID_W || y < 0 || y >= GRID_H) return;
    grid[y][x] = tile;
}
