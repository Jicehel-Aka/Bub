/**
 * @file Game.h
 * @brief Controleur de BUB : puzzle "bubble-slurping" fidele a l'original.
 *
 * Portage de BUB par Owen Swerkstrom (penduin / smogheap), sous GNU GPL v3.
 * Original : https://gitlab.com/smogheap/bub
 */

#pragma once

#include <stdint.h>

#include "../game/Level.h"
#include "../game/Player.h"
#include "../game/LevelManager.h"
#include "Input.h"
#include "Renderer.h"

class Game
{
public:
    void begin(uint16_t startLevel);
    void update();
    void render();

    uint16_t levelNumber() const { return levelIndex; }
    bool     wantsMenu()   const { return exitToMenu; }

    // Accesseurs (tests / HUD).
    int playerX()  const { return player.x; }
    int playerY()  const { return player.y; }
    int invBub()   const { return player.bubbles; }
    int invKey()   const { return player.keys; }

private:
    enum class Phase : uint8_t { Playing, Complete, AllDone };

    LevelManager levels;
    Level        level;
    Player       player;
    Input        input;
    Renderer     renderer;

    uint16_t levelIndex = 0;
    Phase    phase      = Phase::Playing;
    bool     exitToMenu = false;
    uint8_t  difficulty = 0;

    int moveTimer = 0;

    // Palette (fond, plateau, HUD, overlays) — les tuiles/joueur sont des sprites.
    uint16_t cBg, cBoard, cWallEdge, cBubble, cKey, cGoal, cDim, cHud, cOverlay;

    void loadLevel(uint16_t idx);

    // Helpers de grille
    bool inBounds(int x, int y) const;
    bool isEmpty(int x, int y) const;      // Empty ou Goal (traversable, sans caisse)
    bool canOrkEnter(int x, int y) const;  // Empty/Goal/Ladder/Conveyor
    bool orkAt(int x, int y) const { return player.x == x && player.y == y; }

    // Actions (fideles a l'original : chaque action resout la gravite)
    bool moveOrkTo(int nx, int ny);        // gere slurp/porte/drapeau ; true si deplace
    void actLeft();
    void actRight();
    void actUp();
    void actDown();
    void settle();                         // gravite : caisses + ork

    void winReached();

    // rendu
    void drawTile(int gx, int gy);
    void drawPlayer();
    void drawHud();
    void drawOverlay(const char* msg, uint16_t msgColor);
};
