/*
 * Part of the BUB port to the Gamebuino AKA console.
 *
 * BUB and its level designs (c) 2014-2019 Owen Swerkstrom (penduin / smogheap).
 * Original: https://gitlab.com/smogheap/bub
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * This file is free software under the GNU GPL v3; see the LICENSE file.
 */
/**
 * @file Levels.cpp
 * @brief Base de niveaux embarquée (BUB) — 111 niveaux.
 *
 * NE PAS éditer à la main : régénérer via tools/update.py.
 */

#include "Levels.h"

const LevelDef LEVELS[] =
{
    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            " >      ",
            "###     ",
            "       4",
            "      ##",
            "oo @ ###",
            "########",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            " >      ",
            "###     ",
            "       4",
            "      ##",
            "oo @    ",
            "########",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            "    4   ",
            "  H###H ",
            "  H   H ",
            "  H     ",
            "@ H o o ",
            "########",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            "    4   ",
            "   ###H ",
            "      H ",
            "        ",
            "@   o o ",
            "########",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            "        ",
            "@       ",
            "o       ",
            "oo    4 ",
            "ooo  ###",
            "oooo ###",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            "        ",
            "        ",
            "        ",
            "@     4 ",
            "o    ###",
            "o    ###",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "4       ",
            "#H      ",
            " H # o  ",
            " H # o  ",
            "######H#",
            "      H ",
            "o @ # H ",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "@       ",
            "#H      ",
            "oH #    ",
            "oH #    ",
            "######H#",
            "      H ",
            "  4 # H ",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "4       ",
            "####### ",
            " oo     ",
            " #######",
            "     oo ",
            "####### ",
            "@oo     ",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "4       ",
            "######o ",
            "  o     ",
            " o######",
            "     o  ",
            "######o ",
            "@ o     ",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "     4  ",
            "    ###H",
            "o    ##H",
            "o @   XH",
            "#####H##",
            "#####H##",
            "##-  H##",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "     4  ",
            "    ###H",
            "o    ##H",
            "o @   XH",
            "#####H##",
            "#####H##",
            "##o  H##",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "      4 ",
            "    @ #H",
            "  # - #H",
            "  #####H",
            "    X  H",
            " o- #  H",
            "########",
            "########",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "     #4 ",
            "  X @ #H",
            "  # oo#H",
            "  #####H",
            "    X  H",
            "-o- #   ",
            "########",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            "  =     ",
            "H##     ",
            "H       ",
            "H@=   4 ",
            "#### ###",
            "#### ###",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "  =     ",
            "  o     ",
            "H##     ",
            "H       ",
            "H@    4 ",
            "#### ###",
            "#### ###",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "     4  ",
            " H## ##H",
            " H #   H",
            " H #   H",
            "@H #  o ",
            "#  #  o ",
            "#  #   o",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "   X 4X ",
            " H## ##H",
            " H #  -H",
            " H #   H",
            "@H #  o ",
            "o  #  o ",
            "o -#   o",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            " -  4   ",
            "H## # #H",
            "H   ###H",
            " -     H",
            " #H#   H",
            "  H @   ",
            "#####H  ",
            "oooXXH##",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            " -  4 X ",
            "H## # #H",
            "H   ###H",
            " -     H",
            " #H#   H",
            "  H @   ",
            "#####H  ",
            "oooXXH-#",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "    o   ",
            "   o  # ",
            "  o  ## ",
            " o  ##  ",
            "o  ##   ",
            "o@##    ",
            " ##     ",
            "##4     ",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "    o   ",
            "   o  # ",
            "  o  ## ",
            " o  ##  ",
            "-  ##   ",
            "o@##    ",
            " ##     ",
            "##4X    ",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            " o    # ",
            "  o @ # ",
            "####### ",
            "        ",
            " 4   =  ",
            "### ##H#",
            "#   =oH#",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "-     X ",
            " o    # ",
            "  o @ # ",
            "####### ",
            "        ",
            " 4   =  ",
            "##  ##H#",
            "#   =oH#",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "########",
            "########",
            "########",
            "        ",
            "o @ >  4",
            "###### #",
            "########",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "########",
            "########",
            "########",
            "o   =   ",
            "o @ >  4",
            "###### #",
            "###### #",
            "###### #",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "- <  >  ",
            " ##H### ",
            " @ H  o ",
            "####  ##",
            "        ",
            "  ######",
            "    X 4 ",
            "### ####",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "- <  >  ",
            " ##H### ",
            " @ H  o ",
            "####  ##",
            "        ",
            "  ######",
            "    = 4 ",
            "### X###",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            "     =  ",
            "4 =  =  ",
            "##=##=#H",
            "  =  = H",
            "  =  o H",
            "  o @  H",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            "     =  ",
            "4 =  =  ",
            "##=# =#H",
            "  =  = H",
            "  =  o H",
            "  o @  H",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            " @=     ",
            "H##     ",
            "H       ",
            "H##   4 ",
            "H    ###",
            "H       ",
            "H = o o ",
            "HHHHH###",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "  =     ",
            "H #     ",
            "H@      ",
            "H##   4 ",
            "H    ###",
            "H       ",
            "H = o o ",
            "H#HHH###",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            " HHHHHH ",
            " H    H ",
            " H HH H ",
            " H 4H H ",
            " H  H H ",
            " HHHH H ",
            "      H@",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            " oooooo ",
            " o    o ",
            " o oo o ",
            " o 4o o ",
            " o  o o ",
            " oooo o ",
            "      o@",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " @=    -",
            "##HHH  o",
            "    ## o",
            "    #   ",
            "    ####",
            " -   ###",
            "     XX4",
            "     ###",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " @=    o",
            " #HHH  o",
            "    ## o",
            "    #-  ",
            " -  ####",
            "     ###",
            "     XX4",
            "     ###",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "########",
            "-   o   ",
            " H ## H ",
            "H # 4# H",
            " H#X #H ",
            "H o#H  H",
            "H   @  H",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "########",
            "o  #-   ",
            " H ## H ",
            "H # 4# H",
            " H#X #H ",
            "H o#H  H",
            "H   @  H",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "        ",
            "        ",
            "   @    ",
            "  oooo  ",
            " oo ooo ",
            "oo ooooo",
            "ooooo4oo",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "        ",
            "        ",
            "   @    ",
            "  oooo  ",
            "ooo<ooo ",
            " o>ooooo",
            "ooooo4oo",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " -  - o ",
            " ----4o ",
            " -  -oo ",
            " ----@o ",
            "  H  H  ",
            "  H##H  ",
            "  H  H  ",
            "  HHHH  ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " o  o # ",
            " oooo4# ",
            " o  o## ",
            " oooo@# ",
            "  =  =  ",
            "  =##=  ",
            "  =  =  ",
            "  ====  ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "########",
            "########",
            "#####   ",
            "   ooooo",
            "@ ooooo4",
            "########",
            "########",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "########",
            "########",
            "   #####",
            "  ooooo ",
            "@oooooo4",
            "########",
            "########",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "####    ",
            "- @    o",
            "####    ",
            "   # H##",
            "   # H o",
            "  =X  H ",
            " ###    ",
            "  4#####",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "####    ",
            "- @    o",
            "####    ",
            " o # H##",
            "oo # H o",
            "  =X  H ",
            " ###    ",
            " o4#####",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "###### @",
            "   Xoo #",
            " o#### 4",
            "oo   # H",
            "###H # H",
            "    -# H",
            "H#####  ",
            "H    <  ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "###### @",
            "    o# #",
            "  #### 4",
            "oo   o #",
            "###H # H",
            "    o# H",
            "H#####  ",
            "H       ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "@o      ",
            "Ho= = =4",
            "Ho= = = ",
            "Ho= = = ",
            "Ho= = = ",
            "Ho= = = ",
            "Ho= = = ",
            "Ho= = = ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "@o      ",
            "Ho= = = ",
            "Ho= = =4",
            "H = = = ",
            "H== = = ",
            "H== = = ",
            "H==== = ",
            "H==== = ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "   -    ",
            "  ooo   ",
            " ooooo  ",
            "#     #H",
            " # X # H",
            "  #4#  H",
            "   #   H",
            "@      H",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "   -    ",
            "  ooo   ",
            " o   o  ",
            "#     #H",
            " # X # H",
            "  #4#  H",
            "   #   H",
            "@  o   H",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "   H 4 #",
            "   H ###",
            "   H    ",
            "   H#   ",
            "   H    ",
            "   H    ",
            "  oH    ",
            "  oH@   ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "   H 4 #",
            "   H ###",
            "   H    ",
            "   H    ",
            "   H    ",
            "   H    ",
            "  oH    ",
            "  oH@   ",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "#       ",
            "##     #",
            "###   ##",
            "4X   ###",
            "###H = @",
            "## H ###",
            "#     ##",
            "  ooo -#",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "#       ",
            "##     #",
            "###   ##",
            "4X   ###",
            "###H = @",
            "## H ###",
            "#     ##",
            "  oo-  #",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "  X4    ",
            "#H###   ",
            " H      ",
            " H      ",
            " H     -",
            "      o ",
            " @  oooo",
            "########",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "  X4    ",
            "#####   ",
            " H      ",
            " H      ",
            " H     -",
            "      o ",
            " @  oooo",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "      = ",
            " =   ##H",
            "H##    H",
            "H  = @ H",
            "H# # # H",
            "H##### H",
            "H ###- H",
            "H X4#  H",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "   -  = ",
            " -   ##H",
            "H##o  oH",
            "H    @ H",
            "H#   # H",
            "H## ## H",
            "H ###- H",
            "HXXX4# H",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " HHHHH  ",
            " H  = = ",
            " H  ####",
            " H=     ",
            " H#     ",
            "@H     4",
            "###   ##",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " HHHHH  ",
            " H  = o ",
            " H  ####",
            " H=     ",
            " H#     ",
            "@H     4",
            "###   ##",
            "###  ###",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " #  -   ",
            " #      ",
            " X   #H#",
            " ###  H ",
            " #  @ H ",
            " # o# H ",
            "4# o  H ",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " ## -   ",
            " ##    o",
            " XX  #H#",
            " ###  H ",
            " #- @ H ",
            " # o# H ",
            "4#    H ",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " o      ",
            " o=   = ",
            "H##  ##H",
            "Ho     H",
            "H   ####",
            "H@     4",
            "## # ###",
            "## # ###",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            " o    - ",
            " o=   = ",
            "H##  ##H",
            "H-     H",
            "H   ####",
            "H@   XX4",
            "## # ###",
            "## # ###",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "4ooooooo",
            "oo  oooo",
            " oooo o ",
            "o oooo o",
            "ooo oooo",
            "ooo o oo",
            " ooooooo",
            " oo@oo o",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "4ooooooo",
            "oo  oooo",
            " #ooo o ",
            "o oooo o",
            "ooo oooo",
            "ooo o oo",
            " ooooooo",
            " oo@oo o",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "    4   ",
            "    H   ",
            " o o o  ",
            " # # # #",
            "o o o   ",
            "# # # # ",
            " @   oo ",
            "########",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "    4   ",
            "    H   ",
            "o       ",
            " # # # #",
            "o o     ",
            "# # # # ",
            " @   oo ",
            "########",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "    =   ",
            "    =   ",
            " =  =   ",
            "H# H# ##",
            "H  H  X4",
            "H# H# ##",
            "H@ H   -",
            "## ## ##",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            " =  =   ",
            " =  =   ",
            " =  =   ",
            "H# H# ##",
            "H  H  X4",
            "H# ##  #",
            "H@ o   -",
            "## ## ##",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "       4",
            "     ###",
            "   o o  ",
            "   o    ",
            "     o  ",
            " o      ",
            "@   o   ",
            "########",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "       4",
            "     ###",
            "      o ",
            "    ooo ",
            "  o oo  ",
            " oo     ",
            "@   o   ",
            "########",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "o   # 4 ",
            " H# # # ",
            "H - # X ",
            "H   o##H",
            " H o   H",
            "H o    H",
            "H      @",
            "########",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "    # 4 ",
            " H# # # ",
            "H - # X ",
            "H   o##H",
            " H o   H",
            "H o    H",
            "H      @",
            "########",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@      4",
            "##o   ##",
            "  o     ",
            "  o     ",
            "  o     ",
            "  o     ",
            "  o     ",
            "  o     ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@      4",
            "##    ##",
            "        ",
            "        ",
            "        ",
            "        ",
            "        ",
            "ooooooo ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "     =  ",
            "   ##=# ",
            "  ###=##",
            " o###=##",
            " =@  o 4",
            " o### ##",
            "   ## # ",
            "o       ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "     =  ",
            "   ##=# ",
            "  ###=##",
            " o###=##",
            " =@  oX4",
            " o### ##",
            "   ## # ",
            "o    -  ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@ -X-X-X",
            "X--XX-- ",
            " X---XXX",
            "####### ",
            "----    ",
            "  -     ",
            "  ######",
            "  XXXXX4",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@o-X-X-X",
            "X--XX-- ",
            " X---XXX",
            "####### ",
            "----    ",
            "  -     ",
            "       #",
            "  XXXXX4",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            " XXXXXX4",
            "H#######",
            "H  --   ",
            "H    -  ",
            "H   --  ",
            "H   -   ",
            "o       ",
            "@   o   ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            " XX>XXX4",
            "H#######",
            "H  --   ",
            "H    -  ",
            "H   <-  ",
            "H   -   ",
            "o       ",
            "@   o   ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@  > o  ",
            "#oH#  o ",
            "##### # ",
            " 4#=### ",
            "H##=  < ",
            "H#=X ## ",
            "  o H-# ",
            "  # H###",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@  > o  ",
            "#-H#  - ",
            "##### # ",
            " 4#=### ",
            "H##=  < ",
            " #oX ## ",
            "  o H-X ",
            "  # Ho##",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@      4",
            "oooooo  ",
            "        ",
            " ooooooo",
            "        ",
            "ooooooo ",
            "        ",
            " ooooooo",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "@      4",
            "o#o#o#  ",
            "        ",
            " ooo#o#o",
            "        ",
            "o#o#ooo ",
            "        ",
            " ooo#o#o",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "    4   ",
            "    H   ",
            "        ",
            " o     o",
            " o # # o",
            "o  # #o ",
            " H## ##H",
            " H <@> H",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "    4   ",
            "        ",
            "        ",
            " o     o",
            " o = = o",
            "o  # #o ",
            " Hoo ooH",
            " H <@> H",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            " 4 ##   ",
            " -###   ",
            "   ##@  ",
            "  # ##  ",
            "  # ##  ",
            "  # ### ",
            "   oo   ",
            "  oooo  ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            " @ o#   ",
            " ####   ",
            "  -##   ",
            "  # ##  ",
            "  # ##4 ",
            "  # ### ",
            "   oo   ",
            "  oooo  ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "####@###",
            "### H ##",
            "4X  H  X",
            "### H H#",
            "- # H Ho",
            "#H oo H#",
            "#H    H#",
            "#H######",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "####@###",
            "### H ##",
            "4X  H  X",
            "### H H#",
            "- # H Ho",
            "#H  o H#",
            "#H    H#",
            "#H######",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "    = 4 ",
            "  H## #H",
            " oHo# #H",
            " o o< #H",
            "H#### #H",
            "H  >=  H",
            "H####  #",
            "H @##  #",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "-   = 4 ",
            "  H## #H",
            " -H-# #H",
            " o o< #H",
            "H###  #H",
            "H  >=  X",
            "H####  #",
            "H @##  #",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            "-   # - ",
            "  o X   ",
            "  # ###H",
            "H###oHHH",
            "H   # # ",
            "H  o# ##",
            " @ o# X4",
            "########",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            "-   # - ",
            "  o X   ",
            "  # ### ",
            "H###oHH ",
            "H     H ",
            "H  o# ##",
            " @ o# X4",
            "##### ##",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            "       4",
            "      ##",
            "        ",
            "    ##  ",
            "        ",
            "  ## ooo",
            "@    ooo",
            "########",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            "-     X4",
            "      ##",
            "        ",
            "    ##  ",
            "        ",
            "  ## ooo",
            "@    ooo",
            "########",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            " H=    4",
            "oH#     ",
            "oH      ",
            "oH #    ",
            "oH      ",
            "oH  #   ",
            "oH      ",
            "oH@  =  ",
        }
    },

    {
        Difficulty::Experimental,
        true,
        {
            " H=    4",
            "oH#     ",
            "oH      ",
            "oH #    ",
            "oH      ",
            "oH  #   ",
            "oH      ",
            "oH@     ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "       4",
            "    o   ",
            " o      ",
            "      o ",
            "   o    ",
            "o       ",
            "     o  ",
            "@ o     ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "       4",
            "        ",
            "        ",
            "   o    ",
            " o   o  ",
            "   o    ",
            " o   o  ",
            "@  o    ",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            "H######H",
            "H >   #H",
            "H#### #H",
            "H     #H",
            "oooooooH",
            "      #H",
            "4> > > H",
        }
    },

    {
        Difficulty::Easy,
        false,
        {
            "        ",
            "H######H",
            "H >   #H",
            "H#### #H",
            "H     #H",
            "oooooooH",
            "     #oH",
            "4> > > H",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "        ",
            " #####o ",
            " #    o ",
            " # ## o ",
            " # 4# o ",
            " #  # o ",
            " #### o ",
            "      o@",
        }
    },

    {
        Difficulty::Intermediate,
        false,
        {
            "        ",
            " ###### ",
            " =    = ",
            " = #= = ",
            " = 4= = ",
            " =  = o ",
            " #### o ",
            "      o@",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "o #    4",
            "o #     ",
            "o #     ",
            "o #     ",
            "o #     ",
            "o #     ",
            "o #     ",
            "o       ",
        }
    },

    {
        Difficulty::Advanced,
        false,
        {
            "o #    4",
            "o #     ",
            "o ####  ",
            "o #     ",
            "o #  ###",
            "o #     ",
            "o ####  ",
            "o       ",
        }
    },

    {
        Difficulty::Beginner,
        false,
        {
            "        ",
            "        ",
            "        ",
            "        ",
            "        ",
            "        ",
            "        ",
            "@      4",
        }
    },

};

const uint16_t LEVEL_COUNT = sizeof(LEVELS)/sizeof(LevelDef);
