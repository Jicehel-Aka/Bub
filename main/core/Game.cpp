/**
 * @file Game.cpp
 * @brief Logique et rendu de BUB, fideles a l'original.
 *
 * BUB, "bubble-slurping platform puzzle game", (c) Owen Swerkstrom
 * (penduin / smogheap), GNU GPL v3. Original : https://gitlab.com/smogheap/bub
 * Ce fichier est un portage de la logique JavaScript d'origine vers la
 * console Gamebuino AKA (C++).
 *
 * Mecanique centrale : l'ork porte au plus MAX_INV objets. Marcher dans une
 * bulle/cle l'ASPIRE (sans avancer). HAUT/BAS (hors echelle) POSE une bulle
 * sous soi et grimpe dessus : c'est ainsi qu'on prend de la hauteur. La cle
 * ouvre la porte. Les caisses se poussent. Tout subit la gravite. Les tuiles
 * < et > sont des barrieres a sens unique. Atteindre le drapeau = gagne.
 */

#include "Game.h"
#include "Constants.h"
#include "I18n.h"
#include "../game/Sprites.h"

#include <stdio.h>

namespace
{
    constexpr int MOVE_PERIOD = 6;   // cadence de repetition quand une touche est maintenue

    inline int px(int gx) { return BOARD_X + gx * TILE_SIZE; }
    inline int py(int gy) { return BOARD_Y + gy * TILE_SIZE; }
}

// --------------------------------------------------------------------------
// Cycle de vie
// --------------------------------------------------------------------------

void Game::begin(uint16_t startLevel)
{
    renderer.begin();

    cWallEdge   = renderer.rgb(52, 52, 74);
    cBubble     = renderer.rgb(80, 205, 240);
    cKey        = renderer.rgb(245, 215, 70);
    cGoal       = renderer.rgb(80, 220, 120);
    cDim        = renderer.rgb(140, 140, 160);
    cHud        = renderer.rgb(200, 200, 220);
    cOverlay    = renderer.rgb(10, 10, 18);

    uint16_t count = levels.getLevelCount();
    if (count == 0) count = 1;
    if (startLevel >= count) startLevel = 0;

    exitToMenu = false;
    loadLevel(startLevel);
}

void Game::loadLevel(uint16_t idx)
{
    levelIndex = idx;
    levels.loadLevel(idx, level);

    player = Player{};
    player.x = level.getStartX();
    player.y = level.getStartY();

    difficulty = level.getDifficulty();
    phase      = Phase::Playing;
    moveTimer  = 0;

    // Teinte selon la difficulte (pair = bleu nuit, impair = rouge sombre),
    // clin d'oeil aux modes dark/evil de l'original.
    if (difficulty & 1) { cBg = renderer.rgb(40, 10, 10); cBoard = renderer.rgb(60, 20, 20); }
    else                { cBg = renderer.rgb(14, 14, 26); cBoard = renderer.rgb(24, 24, 40); }
}

// --------------------------------------------------------------------------
// Helpers de grille
// --------------------------------------------------------------------------

bool Game::inBounds(int x, int y) const
{
    return x >= 0 && x < GRID_W && y >= 0 && y < GRID_H;
}

bool Game::isEmpty(int x, int y) const
{
    if (!inBounds(x, y)) return false;
    TileType t = level.getTile(x, y);
    return t == TileType::Empty || t == TileType::Goal;
}

bool Game::canOrkEnter(int x, int y) const
{
    if (!inBounds(x, y)) return false;
    switch (level.getTile(x, y))
    {
        case TileType::Empty:
        case TileType::Goal:
        case TileType::Ladder:
        case TileType::ConveyorLeft:
        case TileType::ConveyorRight:
            return true;
        default:
            return false;
    }
}

void Game::winReached()
{
    phase = Phase::Complete;
}

// --------------------------------------------------------------------------
// Deplacement de l'ork (slurp / porte / drapeau)
// --------------------------------------------------------------------------

bool Game::moveOrkTo(int nx, int ny)
{
    if (!inBounds(nx, ny)) return false;

    TileType t = level.getTile(nx, ny);

    switch (t)
    {
        case TileType::Wall:
        case TileType::Crate:
            return false;                       // bloque

        case TileType::Bubble:
            if (player.bubbles + player.keys < MAX_INV)
            {
                level.setTile(nx, ny, TileType::Empty);
                ++player.bubbles;
            }
            return false;                       // aspire : on ne bouge pas

        case TileType::Key:
            if (player.bubbles + player.keys < MAX_INV)
            {
                level.setTile(nx, ny, TileType::Empty);
                ++player.keys;
            }
            return false;

        case TileType::Door:
            if (player.keys > 0)
            {
                --player.keys;
                level.setTile(nx, ny, TileType::Empty);   // porte ouverte = retiree
            }
            return false;                       // verrouillee ou ouverte : on reste

        default:                                // Empty / Goal / Ladder / Conveyor
            player.x = nx;
            player.y = ny;
            if (t == TileType::Goal) winReached();
            return true;
    }
}

// --------------------------------------------------------------------------
// Gravite (caisses + ork), resolue jusqu'a stabilite
// --------------------------------------------------------------------------

void Game::settle()
{
    bool changed = true;
    while (changed)
    {
        changed = false;

        // Caisses : de bas en haut pour vider les colonnes.
        for (int y = GRID_H - 2; y >= 0; --y)
            for (int x = 0; x < GRID_W; ++x)
                if (level.getTile(x, y) == TileType::Crate
                    && isEmpty(x, y + 1) && !orkAt(x, y + 1))
                {
                    level.setTile(x, y, TileType::Empty);
                    level.setTile(x, y + 1, TileType::Crate);
                    changed = true;
                }

        // Ork : tombe s'il n'est pas sur une echelle et que le dessous est vide.
        if (level.getTile(player.x, player.y) != TileType::Ladder)
        {
            int by = player.y + 1;
            if (isEmpty(player.x, by) && !(level.getTile(player.x, by) == TileType::Crate))
            {
                player.y = by;
                player.state = PlayerState::Fall;
                changed = true;
                if (level.getTile(player.x, player.y) == TileType::Goal) winReached();
            }
        }
    }
}

// --------------------------------------------------------------------------
// Actions
// --------------------------------------------------------------------------

void Game::actLeft()
{
    player.facingLeft = true;
    int nx = player.x - 1;

    // Barriere : on ne peut pas entrer par la gauche dans un ">".
    if (!inBounds(nx, player.y) || level.getTile(nx, player.y) == TileType::ConveyorRight)
        return;

    if (level.getTile(nx, player.y) == TileType::Crate)
    {
        int bx = nx - 1;
        if (isEmpty(bx, player.y) && !orkAt(bx, player.y))
        {
            level.setTile(nx, player.y, TileType::Empty);
            level.setTile(bx, player.y, TileType::Crate);
        }
        settle();
        return;                                 // l'ork ne bouge pas en poussant
    }

    player.state = PlayerState::Walk;
    moveOrkTo(nx, player.y);
    settle();
}

void Game::actRight()
{
    player.facingLeft = false;
    int nx = player.x + 1;

    if (!inBounds(nx, player.y) || level.getTile(nx, player.y) == TileType::ConveyorLeft)
        return;

    if (level.getTile(nx, player.y) == TileType::Crate)
    {
        int bx = nx + 1;
        if (isEmpty(bx, player.y) && !orkAt(bx, player.y))
        {
            level.setTile(nx, player.y, TileType::Empty);
            level.setTile(bx, player.y, TileType::Crate);
        }
        settle();
        return;
    }

    player.state = PlayerState::Walk;
    moveOrkTo(nx, player.y);
    settle();
}

void Game::actUp()
{
    if (!inBounds(player.x, player.y - 1)) return;

    // Monter a l'echelle.
    bool onLadder = level.getTile(player.x, player.y) == TileType::Ladder;
    if (onLadder && (level.getTile(player.x, player.y - 1) == TileType::Ladder
                     || isEmpty(player.x, player.y - 1)))
    {
        player.state = PlayerState::Climb;
        moveOrkTo(player.x, player.y - 1);
        return;
    }

    // Sinon : si le dessous n'est pas une echelle, on tente le "poser+grimper".
    if (!inBounds(player.x, player.y + 1)
        || level.getTile(player.x, player.y + 1) != TileType::Ladder)
        actDown();
}

void Game::actDown()
{
    // Descendre l'echelle.
    if (inBounds(player.x, player.y + 1)
        && level.getTile(player.x, player.y + 1) == TileType::Ladder)
    {
        player.state = PlayerState::Climb;
        moveOrkTo(player.x, player.y + 1);
        return;
    }

    // Sur un tapis : on ne peut pas poser.
    TileType cur = level.getTile(player.x, player.y);
    if (cur == TileType::ConveyorLeft || cur == TileType::ConveyorRight) return;

    // Sortie d'echelle vers le bas (dans du vide).
    if (cur == TileType::Ladder && inBounds(player.x, player.y + 1)
        && isEmpty(player.x, player.y + 1))
    {
        moveOrkTo(player.x, player.y + 1);
        settle();
        return;
    }

    // Les mains vides : on tombe simplement.
    if (player.bubbles == 0 && player.keys == 0)
    {
        settle();
        return;
    }

    // Poser un objet sous soi et grimper dessus.
    int ty = player.y - 1;
    if (!inBounds(player.x, ty)) return;

    TileType above = level.getTile(player.x, ty);
    bool climbable = isEmpty(player.x, ty) || above == TileType::Ladder
                     || above == TileType::ConveyorLeft || above == TileType::ConveyorRight;
    if (!climbable) return;

    if (player.bubbles > 0) { level.setTile(player.x, player.y, TileType::Bubble); --player.bubbles; }
    else                    { level.setTile(player.x, player.y, TileType::Key);    --player.keys; }

    player.state = PlayerState::Climb;
    moveOrkTo(player.x, player.y - 1);
    settle();
}

// --------------------------------------------------------------------------
// Update
// --------------------------------------------------------------------------

void Game::update()
{
    input.update();
    const InputState& in = input.getState();

    if (phase == Phase::Complete)
    {
        if (in.aP)
        {
            uint16_t count = levels.getLevelCount();
            if (levelIndex + 1 >= count) phase = Phase::AllDone;
            else                         loadLevel(levelIndex + 1);
        }
        else if (in.bP) loadLevel(levelIndex);
        return;
    }

    if (phase == Phase::AllDone)
    {
        if (in.aP) exitToMenu = true;
        return;
    }

    // --- Playing ---
    if (moveTimer > 0) --moveTimer;

    if (in.bP) { loadLevel(levelIndex); return; }   // B = recommencer

    bool canRepeat = (moveTimer <= 0);

    if      (in.upP)    { actUp();    moveTimer = MOVE_PERIOD; }
    else if (in.downP)  { actDown();  moveTimer = MOVE_PERIOD; }
    else if (in.leftP)  { actLeft();  moveTimer = MOVE_PERIOD; }
    else if (in.rightP) { actRight(); moveTimer = MOVE_PERIOD; }
    else if (canRepeat)
    {
        if      (in.up)    { actUp();    moveTimer = MOVE_PERIOD; }
        else if (in.down)  { actDown();  moveTimer = MOVE_PERIOD; }
        else if (in.left)  { actLeft();  moveTimer = MOVE_PERIOD; }
        else if (in.right) { actRight(); moveTimer = MOVE_PERIOD; }
        else               { moveTimer = 0; player.state = PlayerState::Idle; }
    }
}

// --------------------------------------------------------------------------
// Rendu
// --------------------------------------------------------------------------

void Game::drawTile(int gx, int gy)
{
    TileType t = level.getTile(gx, gy);
    const uint8_t* spr = nullptr;
    switch (t)
    {
        case TileType::Wall:          spr = SPR_WALL;   break;
        case TileType::Ladder:        spr = SPR_LADDER; break;
        case TileType::Bubble:        spr = SPR_BUBBLE; break;
        case TileType::Key:           spr = SPR_KEY;    break;
        case TileType::Door:          spr = SPR_DOOR;   break;
        case TileType::Crate:         spr = SPR_CRATE;  break;
        case TileType::ConveyorLeft:  spr = SPR_CONV_L; break;
        case TileType::ConveyorRight: spr = SPR_CONV_R; break;
        case TileType::Goal:          spr = SPR_FLAG;   break;
        default: return;   // Empty : rien (fond du plateau)
    }
    renderer.blit(spr, SPRITE_W, SPRITE_H, px(gx), py(gy));
}

void Game::drawPlayer()
{
    const uint8_t* spr;
    if (player.state == PlayerState::Climb)      spr = SPR_ORK_UP;
    else if (player.state == PlayerState::Fall)  spr = SPR_ORK_DOWN;
    else spr = player.facingLeft ? SPR_ORK_L : SPR_ORK_R;

    renderer.blit(spr, SPRITE_W, SPRITE_H, px(player.x), py(player.y));
}

void Game::drawHud()
{
    char buf[24];

    // Niveau (gauche)
    snprintf(buf, sizeof(buf), "%s %u", i18n::tr(S_LEVEL), (unsigned)(levelIndex + 1));
    renderer.text(6, 10, buf, cHud);

    // Inventaire (centre) : MAX_INV emplacements
    renderer.text(120, 10, "INV", cHud);
    for (int i = 0; i < MAX_INV; ++i)
    {
        int sx = 150 + i * 18, sy = 8;
        renderer.setColor(cDim);
        renderer.drawRect(sx, sy, 14, 14);
        if (i < player.bubbles)
        {
            renderer.setColor(cBubble);
            renderer.fillCircle(sx + 7, sy + 7, 4);
        }
        else if (i < player.bubbles + player.keys)
        {
            renderer.setColor(cKey);
            renderer.fillRect(sx + 6, sy + 4, 2, 7);
            renderer.drawCircle(sx + 7, sy + 4, 2);
        }
    }

    // Aide (bas) : HAUT pose/grimpe, B recommence
    snprintf(buf, sizeof(buf), "^=%s  %s", i18n::tr(S_CLIMB), i18n::tr(S_RESTART));
    renderer.textCenter(226, buf, cDim);
}

void Game::drawOverlay(const char* msg, uint16_t msgColor)
{
    renderer.setColor(cOverlay);
    renderer.fillRect(40, 96, 240, 52);
    renderer.setColor(cDim);
    renderer.drawRect(40, 96, 240, 52);

    renderer.textCenter(108, msg, msgColor);
    renderer.textCenter(128, i18n::tr(S_CONTINUE), cDim);
}

void Game::render()
{
    renderer.clear(cBg);

    renderer.setColor(cBoard);
    renderer.fillRect(BOARD_X, BOARD_Y, GRID_W * TILE_SIZE, GRID_H * TILE_SIZE);
    renderer.setColor(cWallEdge);
    renderer.drawRect(BOARD_X - 1, BOARD_Y - 1, GRID_W * TILE_SIZE + 2, GRID_H * TILE_SIZE + 2);

    for (int gy = 0; gy < GRID_H; ++gy)
        for (int gx = 0; gx < GRID_W; ++gx)
            drawTile(gx, gy);

    drawPlayer();
    drawHud();

    if (phase == Phase::Complete)      drawOverlay(i18n::tr(S_COMPLETE), cGoal);
    else if (phase == Phase::AllDone)  drawOverlay(i18n::tr(S_WIN), cKey);
}
