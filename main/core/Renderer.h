/**
 * @file Renderer.h
 * @brief Fine couche de dessin au-dessus de gb_graphics (coquille).
 */

#pragma once

#include <stdint.h>

class Renderer
{
public:
    void begin();

    //! Efface avec une couleur.
    void clear(uint16_t color);

    //! Fabrique une couleur BGR565 a partir de composantes 0..255.
    uint16_t rgb(uint8_t r, uint8_t g, uint8_t b);

    void setColor(uint16_t color);

    void fillRect(int x, int y, int w, int h);
    void drawRect(int x, int y, int w, int h);
    void line(int x0, int y0, int x1, int y1);
    void fillCircle(int x, int y, int r);
    void drawCircle(int x, int y, int r);
    void fillTriangle(int x0,int y0,int x1,int y1,int x2,int y2);

    //! Texte 8x8 a la couleur courante.
    void text(int x, int y, const char* s);
    //! Texte 8x8 dans une couleur donnee.
    void text(int x, int y, const char* s, uint16_t color);
    //! Texte centre horizontalement.
    void textCenter(int y, const char* s, uint16_t color);

    //! Affiche une image RGBA (4 octets/pixel) ; alpha < 128 = transparent.
    //! Chaque pixel est converti via makeColor (correct BGR565/RGB565).
    void blit(const uint8_t* rgba, int w, int h, int x, int y);
};
