/**
 * @file Input.cpp
 * @brief Lecture des boutons AKA via les instances globales de la coquille.
 */

#include "Input.h"
#include "ShellCore.h"   // shell::g_core

using shell::g_core;

void Input::update()
{
    uint16_t s = g_core.buttons.state();

    state.up    = s & gb_buttons::KEY_UP;
    state.down  = s & gb_buttons::KEY_DOWN;
    state.left  = s & gb_buttons::KEY_LEFT;
    state.right = s & gb_buttons::KEY_RIGHT;
    state.a     = s & gb_buttons::KEY_A;
    state.b     = s & gb_buttons::KEY_B;
    state.menu  = s & gb_buttons::KEY_MENU;
    state.run   = s & gb_buttons::KEY_RUN;

    state.upP    = g_core.buttons.pressed(gb_buttons::KEY_UP);
    state.downP  = g_core.buttons.pressed(gb_buttons::KEY_DOWN);
    state.leftP  = g_core.buttons.pressed(gb_buttons::KEY_LEFT);
    state.rightP = g_core.buttons.pressed(gb_buttons::KEY_RIGHT);
    state.aP     = g_core.buttons.pressed(gb_buttons::KEY_A);
    state.bP     = g_core.buttons.pressed(gb_buttons::KEY_B);
}
