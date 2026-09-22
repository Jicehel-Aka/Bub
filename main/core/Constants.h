/**
 * @file Constants.h
 * @brief Global project constants.
 */

#pragma once

constexpr int SCREEN_W = 320;
constexpr int SCREEN_H = 240;

// Les niveaux sont des grilles 8x8 (cf main/game/Levels.cpp / tools/update.py).
constexpr int GRID_W = 8;
constexpr int GRID_H = 8;

constexpr int TILE_SIZE = 16;

// Plateau centre : 8*16 = 128 px. (320-128)/2 = 96 ; (240-128)/2 = 56.
constexpr int BOARD_X = 96;
constexpr int BOARD_Y = 56;
