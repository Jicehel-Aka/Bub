/**
 * @file Renderer.cpp
 * @brief Implementation : delegue a shell::g_gfx.
 */

#include "Renderer.h"
#include "ShellCore.h"   // shell::g_gfx

#include <string.h>

using shell::g_gfx;

void Renderer::begin() {}

void Renderer::clear(uint16_t color) { g_gfx.clear(color); }

uint16_t Renderer::rgb(uint8_t r, uint8_t g, uint8_t b) { return g_gfx.makeColor(r, g, b); }

void Renderer::setColor(uint16_t color) { g_gfx.setColor(color); }

void Renderer::fillRect(int x, int y, int w, int h)
{
    g_gfx.fillRect((int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h);
}

void Renderer::drawRect(int x, int y, int w, int h)
{
    g_gfx.drawRect((int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h);
}

void Renderer::line(int x0, int y0, int x1, int y1)
{
    g_gfx.drawLine((int16_t)x0, (int16_t)y0, (int16_t)x1, (int16_t)y1);
}

void Renderer::fillCircle(int x, int y, int r)
{
    g_gfx.fillCircle((int16_t)x, (int16_t)y, (int16_t)r);
}

void Renderer::drawCircle(int x, int y, int r)
{
    g_gfx.drawCircle((int16_t)x, (int16_t)y, (int16_t)r);
}

void Renderer::fillTriangle(int x0,int y0,int x1,int y1,int x2,int y2)
{
    g_gfx.fillTriangle((int16_t)x0,(int16_t)y0,(int16_t)x1,(int16_t)y1,(int16_t)x2,(int16_t)y2);
}

void Renderer::text(int x, int y, const char* s)
{
    g_gfx.move_cursor((uint16_t)x, (uint16_t)y);
    g_gfx.print_str(s);
}

void Renderer::text(int x, int y, const char* s, uint16_t color)
{
    g_gfx.setColor(color);
    text(x, y, s);
}

void Renderer::textCenter(int y, const char* s, uint16_t color)
{
    int w = (int)strlen(s) * 8;
    int x = (320 - w) / 2;
    if (x < 0) x = 0;
    text(x, y, s, color);
}

void Renderer::blit(const uint8_t* rgba, int w, int h, int x, int y)
{
    for (int j = 0; j < h; ++j)
        for (int i = 0; i < w; ++i)
        {
            const uint8_t* p = rgba + (j * w + i) * 4;
            if (p[3] < 128) continue;   // transparent
            g_gfx.drawPixel((int16_t)(x + i), (int16_t)(y + j),
                            g_gfx.makeColor(p[0], p[1], p[2]));
        }
}
