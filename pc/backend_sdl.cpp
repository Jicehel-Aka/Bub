/*
 * backend_sdl.cpp — implementation SDL2 de l'API gb_core / gb_graphics /
 * gb_audio_player pour la version PC de BUB. Le jeu et la coquille ne sont pas
 * modifies : ils parlent a cette meme API (comme sur la Gamebuino AKA).
 *
 * Part of the BUB port. SPDX-License-Identifier: GPL-3.0-only
 */

#include "gamebuino.h"
#include "gb_ll_sdcard.h"

#include <SDL.h>

#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cmath>

// Police 8x8 domaine public (Daniel Hepper) : char font8x8_basic[128][8].
#include "font8x8_basic.h"

namespace
{
    const int LOGICAL_W = 320;
    const int LOGICAL_H = 240;
    const int SCALE     = 3;      // fenetre 960x720

    SDL_Window*   g_win = nullptr;
    SDL_Renderer* g_ren = nullptr;

    uint16_t g_pen  = 0xFFFF;
    int      g_curx = 0, g_cury = 0, g_linex = 0;

    uint16_t g_held = 0, g_prev = 0;

    inline void applyColor(uint16_t c)
    {
        int r = (c >> 8) & 0xF8;
        int g = (c >> 3) & 0xFC;
        int b = (c << 3) & 0xF8;
        SDL_SetRenderDrawColor(g_ren, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    }

    void pumpEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) { SDL_Quit(); std::exit(0); }
            if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode k = e.key.keysym.sym;
                if (k == SDLK_ESCAPE || k == SDLK_q) { SDL_Quit(); std::exit(0); }
            }
        }
    }

    uint16_t readKeys()
    {
        const Uint8* s = SDL_GetKeyboardState(nullptr);
        uint16_t m = 0;
        if (s[SDL_SCANCODE_UP])                             m |= GB_KEY_UP;
        if (s[SDL_SCANCODE_DOWN])                           m |= GB_KEY_DOWN;
        if (s[SDL_SCANCODE_LEFT])                           m |= GB_KEY_LEFT;
        if (s[SDL_SCANCODE_RIGHT])                          m |= GB_KEY_RIGHT;
        if (s[SDL_SCANCODE_Z] || s[SDL_SCANCODE_RETURN])    m |= GB_KEY_A;   // valider
        if (s[SDL_SCANCODE_X] || s[SDL_SCANCODE_BACKSPACE]) m |= GB_KEY_B;   // annuler / rejouer
        if (s[SDL_SCANCODE_M] || s[SDL_SCANCODE_TAB])       m |= GB_KEY_MENU;
        if (s[SDL_SCANCODE_LSHIFT] || s[SDL_SCANCODE_RSHIFT]) m |= GB_KEY_RUN;
        return m;
    }
}

// ------------------------------------------------------------------ gb_buttons
void     gb_buttons::update() {}
uint16_t gb_buttons::state()   { return g_held; }
uint16_t gb_buttons::pressed() { return (uint16_t)(g_held & ~g_prev); }
bool     gb_buttons::pressed(gb_key k)  { return (g_held & k) && !(g_prev & k); }
uint16_t gb_buttons::released() { return (uint16_t)(~g_held & g_prev); }
bool     gb_buttons::released(gb_key k) { return !(g_held & k) && (g_prev & k); }
void     gb_buttons::set_run_power_off(bool) {}

// ----------------------------------------------------------------- gb_joystick
void gb_joystick::update() {}

// ---------------------------------------------------------------------- gb_core
gb_core::gb_core() {}
gb_core::~gb_core() {}

int gb_core::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError()); return -1; }
    g_win = SDL_CreateWindow("BUB",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             LOGICAL_W * SCALE, LOGICAL_H * SCALE,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!g_win) { std::fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError()); return -1; }
    g_ren = SDL_CreateRenderer(g_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_ren) { std::fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError()); return -1; }
    SDL_RenderSetLogicalSize(g_ren, LOGICAL_W, LOGICAL_H);
    g_held = g_prev = 0;
    return 0;
}

void gb_core::pool()
{
    pumpEvents();
    g_prev = g_held;
    g_held = readKeys();
}

void     gb_core::delay_ms(uint32_t ms) { SDL_Delay(ms); }
uint32_t gb_core::get_millis()          { return SDL_GetTicks(); }
int64_t  gb_core::get_micros()          { return (int64_t)SDL_GetTicks() * 1000; }
size_t   gb_core::free_psram()          { return 0; }
size_t   gb_core::free_sram()           { return 0; }
void     gb_core::power_down()          { SDL_Quit(); std::exit(0); }

// ------------------------------------------------------------------ gb_graphics
gb_graphics::gb_graphics() {}
gb_graphics::~gb_graphics() {}

void gb_graphics::clear(uint16_t c) { applyColor(c); SDL_RenderClear(g_ren); }
void gb_graphics::clear()           { applyColor(g_pen); SDL_RenderClear(g_ren); }

void gb_graphics::setColor(uint16_t c) { g_pen = c; }

uint16_t gb_graphics::makeColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

void gb_graphics::fillRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
    applyColor(g_pen);
    SDL_Rect r{ x, y, w, h };
    SDL_RenderFillRect(g_ren, &r);
}

void gb_graphics::drawRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
    applyColor(g_pen);
    SDL_Rect r{ x, y, w, h };
    SDL_RenderDrawRect(g_ren, &r);
}

void gb_graphics::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    applyColor(g_pen);
    SDL_RenderDrawLine(g_ren, x0, y0, x1, y1);
}

void gb_graphics::drawFastVLine(int16_t x, int16_t y, int16_t h)
{ applyColor(g_pen); SDL_RenderDrawLine(g_ren, x, y, x, y + h - 1); }

void gb_graphics::drawFastHLine(int16_t x, int16_t y, int16_t w)
{ applyColor(g_pen); SDL_RenderDrawLine(g_ren, x, y, x + w - 1, y); }

void gb_graphics::fillCircle(int16_t cx, int16_t cy, int16_t r)
{
    applyColor(g_pen);
    for (int dy = -r; dy <= r; ++dy)
    {
        int dx = (int)std::lround(std::sqrt((double)(r * r - dy * dy)));
        SDL_RenderDrawLine(g_ren, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

void gb_graphics::drawCircle(int16_t cx, int16_t cy, int16_t r)
{
    applyColor(g_pen);
    int x = r, y = 0, err = 1 - r;
    while (x >= y)
    {
        SDL_RenderDrawPoint(g_ren, cx + x, cy + y); SDL_RenderDrawPoint(g_ren, cx - x, cy + y);
        SDL_RenderDrawPoint(g_ren, cx + x, cy - y); SDL_RenderDrawPoint(g_ren, cx - x, cy - y);
        SDL_RenderDrawPoint(g_ren, cx + y, cy + x); SDL_RenderDrawPoint(g_ren, cx - y, cy + x);
        SDL_RenderDrawPoint(g_ren, cx + y, cy - x); SDL_RenderDrawPoint(g_ren, cx - y, cy - x);
        ++y;
        if (err < 0) err += 2 * y + 1;
        else { --x; err += 2 * (y - x) + 1; }
    }
}

void gb_graphics::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    applyColor(g_pen);
    SDL_RenderDrawLine(g_ren, x0, y0, x1, y1);
    SDL_RenderDrawLine(g_ren, x1, y1, x2, y2);
    SDL_RenderDrawLine(g_ren, x2, y2, x0, y0);
}

void gb_graphics::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    applyColor(g_pen);
    int minx = x0 < x1 ? (x0 < x2 ? x0 : x2) : (x1 < x2 ? x1 : x2);
    int maxx = x0 > x1 ? (x0 > x2 ? x0 : x2) : (x1 > x2 ? x1 : x2);
    int miny = y0 < y1 ? (y0 < y2 ? y0 : y2) : (y1 < y2 ? y1 : y2);
    int maxy = y0 > y1 ? (y0 > y2 ? y0 : y2) : (y1 > y2 ? y1 : y2);
    auto edge = [](int ax, int ay, int bx, int by, int px, int py)
    { return (px - ax) * (by - ay) - (py - ay) * (bx - ax); };
    for (int py = miny; py <= maxy; ++py)
        for (int px = minx; px <= maxx; ++px)
        {
            int w0 = edge(x1, y1, x2, y2, px, py);
            int w1 = edge(x2, y2, x0, y0, px, py);
            int w2 = edge(x0, y0, x1, y1, px, py);
            bool neg = (w0 <= 0 && w1 <= 0 && w2 <= 0);
            bool pos = (w0 >= 0 && w1 >= 0 && w2 >= 0);
            if (neg || pos) SDL_RenderDrawPoint(g_ren, px, py);
        }
}

void gb_graphics::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t)
{ drawRect(x, y, w, h); }
void gb_graphics::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t)
{ fillRect(x, y, w, h); }

void gb_graphics::drawPixel(int16_t x, int16_t y, uint16_t c) { applyColor(c); SDL_RenderDrawPoint(g_ren, x, y); }
void gb_graphics::drawPixel(int16_t x, int16_t y)             { applyColor(g_pen); SDL_RenderDrawPoint(g_ren, x, y); }

void gb_graphics::draw_char(uint16_t x, uint16_t y, char ch)
{
    unsigned idx = (unsigned char)ch;
    if (idx >= 128) idx = 0;
    const unsigned char* g = font8x8_basic[idx];
    applyColor(g_pen);
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
            if (g[row] & (1 << col))
                SDL_RenderDrawPoint(g_ren, x + col, y + row);
}

void gb_graphics::move_cursor(uint16_t x, uint16_t y) { g_curx = x; g_cury = y; g_linex = x; }

void gb_graphics::print_str(const char* s)
{
    for (; *s; ++s)
    {
        if (*s == '\n') { g_cury += 8; g_curx = g_linex; continue; }
        draw_char((uint16_t)g_curx, (uint16_t)g_cury, *s);
        g_curx += 8;
    }
}

void gb_graphics::printf(const char* fmt, ...)
{
    char buf[256];
    va_list ap; va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    print_str(buf);
}

void     gb_graphics::set_backlight(uint16_t) {}
uint16_t gb_graphics::get_backlight() { return 0; }
void     gb_graphics::set_backlight_percent(uint8_t) {}
uint8_t  gb_graphics::get_backlight_percent() { return 100; }
void     gb_graphics::set_refresh_rate(uint8_t) {}
float    gb_graphics::get_fps() { return 60.0f; }

void gb_graphics::update()
{
    SDL_RenderPresent(g_ren);
    pumpEvents();
}

// ------------------------------------------------------------- gb_audio_player
gb_audio_player::gb_audio_player() {}
gb_audio_player::~gb_audio_player() {}
void     gb_audio_player::pool() {}
void     gb_audio_player::set_master_volume(uint8_t) {}
uint8_t  gb_audio_player::get_master_volume() { return 0; }
void     gb_audio_player::vibrator(uint32_t) {}

// -------------------------------------------------------------------- gb_ll_sd
extern "C" int  gb_ll_sd_init(void)       { return 0; }
extern "C" bool gb_ll_sd_is_mounted(void) { return true; }  // sauvegarde locale autorisee
