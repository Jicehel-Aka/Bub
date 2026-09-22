/**
 * @file Player.h
 * @brief Etat de l'ork (position, inventaire, pose).
 *
 * Fidele a l'original BUB : l'ork porte au plus MAX_INV objets (bulles + cles).
 */

#pragma once

#include <stdint.h>

enum class PlayerState
{
    Idle,
    Walk,
    Climb,
    Fall
};

struct Player
{
    int x = 0;
    int y = 0;

    bool facingLeft = false;

    uint8_t bubbles = 0;   // bulles portees
    uint8_t keys    = 0;   // cles portees

    PlayerState state = PlayerState::Idle;
};

// Capacite d'inventaire (bulles + cles), comme l'original.
constexpr uint8_t MAX_INV = 2;
