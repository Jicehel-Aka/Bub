#!/usr/bin/env python3
"""
gen_sprites.py — convertit les PNG 16x16 RGBA de assets/sprites/ en tableaux C
(RGBA, 4 octets/pixel) dans main/game/Sprites.{h,cpp}.

Le rendu (Renderer::blit) saute les pixels dont alpha < 128 et convertit chaque
pixel via gb_graphics::makeColor(r,g,b) : correct quel que soit l'ordre de la
cible (BGR565 sur AKA, RGB565 sur SDL).

Usage : python3 tools/gen_sprites.py
"""
import os
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC  = os.path.join(ROOT, "assets", "sprites")
OUTH = os.path.join(ROOT, "main", "game", "Sprites.h")
OUTC = os.path.join(ROOT, "main", "game", "Sprites.cpp")

# fichier PNG -> symbole C
MAP = [
    ("wall01",       "SPR_WALL"),
    ("bubble01",     "SPR_BUBBLE"),
    ("ladder01",     "SPR_LADDER"),
    ("key01",        "SPR_KEY"),
    ("door01",       "SPR_DOOR"),
    ("flag01",       "SPR_FLAG"),
    ("crate01",      "SPR_CRATE"),
    ("left01",       "SPR_CONV_L"),
    ("right01",      "SPR_CONV_R"),
    ("ork-stand01",  "SPR_ORK_R"),     # face a droite
    ("ork-stand02",  "SPR_ORK_L"),     # face a gauche
    ("ork-up01",     "SPR_ORK_UP"),    # grimpe
    ("ork-down01",   "SPR_ORK_DOWN"),  # descend / chute
]

W = H = 16

def emit_array(name, img):
    px = img.convert("RGBA").load()
    vals = []
    for y in range(H):
        for x in range(W):
            r, g, b, a = px[x, y]
            vals += [r, g, b, a]
    body = ",".join(str(v) for v in vals)
    return "const uint8_t %s[%d] = {%s};\n" % (name, W * H * 4, body)

def main():
    lines_c = [
        "/* Auto-genere par tools/gen_sprites.py — NE PAS EDITER A LA MAIN. */",
        "/* Sprites BUB (c) Owen Swerkstrom, GPL-3.0-only. */",
        '#include "Sprites.h"',
        "",
    ]
    lines_h = [
        "/* Auto-genere par tools/gen_sprites.py — NE PAS EDITER A LA MAIN. */",
        "#pragma once",
        "#include <stdint.h>",
        "",
        "constexpr int SPRITE_W = %d;" % W,
        "constexpr int SPRITE_H = %d;" % H,
        "",
    ]
    for fname, sym in MAP:
        path = os.path.join(SRC, fname + ".png")
        img = Image.open(path)
        if img.size != (W, H):
            img = img.resize((W, H), Image.NEAREST)
        lines_c.append(emit_array(sym, img))
        lines_h.append("extern const uint8_t %s[%d];" % (sym, W * H * 4))

    with open(OUTH, "w", newline="\r\n") as f:
        f.write("\n".join(lines_h) + "\n")
    with open(OUTC, "w", newline="\r\n") as f:
        f.write("\n".join(lines_c) + "\n")
    print("Ecrit:", OUTH)
    print("Ecrit:", OUTC, "(%d sprites)" % len(MAP))

if __name__ == "__main__":
    main()
