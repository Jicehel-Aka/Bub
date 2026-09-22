/**
 * @file LevelManager.cpp
 * @brief Implementation : delegue a Level::load et expose LEVEL_COUNT.
 */

#include "LevelManager.h"
#include "Level.h"
#include "Levels.h"

bool LevelManager::loadLevel(uint16_t id, Level& level)
{
    return level.load(id);
}

uint16_t LevelManager::getLevelCount() const
{
    return LEVEL_COUNT;
}
