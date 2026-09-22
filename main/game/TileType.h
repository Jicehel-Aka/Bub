/**
 * @file TileType.h
 * @brief BUB tile definitions.
 */

#pragma once

#include <stdint.h>

enum class TileType : uint8_t
{
    Empty,

    Wall,
    Ladder,

    Bubble,
    Key,
    Door,
    Crate,

    ConveyorLeft,
    ConveyorRight,

    Goal
};
