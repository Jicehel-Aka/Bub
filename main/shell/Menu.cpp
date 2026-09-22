/**
 * @file Menu.cpp
 * @brief Ecrans de la coquille BUB (titre, menu, langue, regles).
 */

#include "Menu.h"
#include "ShellCore.h"
#include "I18n.h"
#include "Config.h"

#include <stdio.h>
#include <string.h>

using namespace shell;

namespace
{
    // Edge (front montant) sur une touche.
    inline bool pressed(gb_buttons::gb_key k)
    {
        return g_core.buttons.pressed(k);
    }

    void drawTitle(const char* s)
    {
        g_gfx.setColor(COL_HL);
        textCenter(28, s);
        g_gfx.setColor(COL_FG);
    }
}

namespace menu
{
    void title()
    {
        for (;;)
        {
            frameBegin();

            g_gfx.clear(COL_BG);
            g_gfx.setColor(COL_HL);
            textCenter(70, "B U B");
            g_gfx.setColor(COL_DIM);
            textCenter(150, i18n::tr(S_PRESS_START));

            // Attribution (jeu original sous GPL v3).
            textCenter(206, "BUB (C) O.SWERKSTROM");
            textCenter(222, "GPL V3 - SMOGHEAP");

            frameEnd();

            if (pressed(gb_buttons::KEY_A)) return;
        }
    }

    Action mainMenu()
    {
        const Str items[6] = { S_PLAY, S_LANGUAGE, S_SOUND, S_RULES, S_CREDITS, S_QUIT };
        const int count = 6;
        int sel = 0;

        for (;;)
        {
            frameBegin();

            g_gfx.clear(COL_BG);
            drawTitle("MENU");

            for (int i = 0; i < count; ++i)
            {
                int y = 70 + i * 20;
                char line[40];

                if (items[i] == S_SOUND)
                    snprintf(line, sizeof(line), "%s: %s",
                             i18n::tr(S_SOUND),
                             i18n::tr(g_cfg.sound ? S_ON : S_OFF));
                else if (items[i] == S_LANGUAGE)
                    snprintf(line, sizeof(line), "%s: %s",
                             i18n::tr(S_LANGUAGE),
                             i18n::langName(g_cfg.lang));
                else
                    snprintf(line, sizeof(line), "%s", i18n::tr(items[i]));

                if (i == sel)
                {
                    g_gfx.setColor(COL_HL);
                    text(60, y, ">");
                    text(80, y, line);
                }
                else
                {
                    g_gfx.setColor(COL_FG);
                    text(80, y, line);
                }
            }

            frameEnd();

            if (pressed(gb_buttons::KEY_UP))   sel = (sel + count - 1) % count;
            if (pressed(gb_buttons::KEY_DOWN)) sel = (sel + 1) % count;
            if (pressed(gb_buttons::KEY_A))    return static_cast<Action>(sel);
        }
    }

    void language()
    {
        int sel = static_cast<int>(i18n::current());

        for (;;)
        {
            frameBegin();

            g_gfx.clear(COL_BG);
            drawTitle(i18n::tr(S_LANGUAGE));

            for (int i = 0; i < LANG_COUNT; ++i)
            {
                int y = 70 + i * 20;
                if (i == sel) { g_gfx.setColor(COL_HL); text(60, y, ">"); }
                else            g_gfx.setColor(COL_FG);
                text(80, y, i18n::langName(static_cast<Lang>(i)));
            }

            g_gfx.setColor(COL_DIM);
            textCenter(210, i18n::tr(S_BACK));

            frameEnd();

            if (pressed(gb_buttons::KEY_UP))   sel = (sel + LANG_COUNT - 1) % LANG_COUNT;
            if (pressed(gb_buttons::KEY_DOWN)) sel = (sel + 1) % LANG_COUNT;

            if (pressed(gb_buttons::KEY_A))
            {
                Lang chosen = static_cast<Lang>(sel);
                i18n::set(chosen);
                g_cfg.lang = chosen;
                config::save(g_cfg);
                return;
            }
            if (pressed(gb_buttons::KEY_B)) return;
        }
    }

    void rules()
    {
        for (;;)
        {
            frameBegin();

            g_gfx.clear(COL_BG);
            drawTitle(i18n::tr(S_RULES_TITLE));

            uint8_t n = i18n::rulesLineCount();
            for (uint8_t i = 0; i < n; ++i)
            {
                g_gfx.setColor(COL_FG);
                text(20, 70 + i * 20, i18n::rulesLine(i));
            }

            g_gfx.setColor(COL_DIM);
            textCenter(210, i18n::tr(S_BACK));

            frameEnd();

            if (pressed(gb_buttons::KEY_A) || pressed(gb_buttons::KEY_B)) return;
        }
    }

    void credits()
    {
        // Attribution du jeu original (BUB, sous GNU GPL v3).
        static const char* const LINES[] = {
            "BUB",
            "(C) 2014-2019",
            "OWEN SWERKSTROM",
            "PENDUIN / SMOGHEAP",
            "",
            "GNU GPL V3",
            "GITLAB.COM/SMOGHEAP/BUB",
            "",
            "PORTAGE GAMEBUINO AKA",
        };
        const int n = (int)(sizeof(LINES) / sizeof(LINES[0]));

        for (;;)
        {
            frameBegin();

            g_gfx.clear(COL_BG);
            drawTitle(i18n::tr(S_CREDITS));

            for (int i = 0; i < n; ++i)
            {
                if (LINES[i][0] == '\0') continue;
                g_gfx.setColor(i < 4 ? COL_FG : COL_DIM);
                textCenter(64 + i * 16, LINES[i]);
            }

            g_gfx.setColor(COL_DIM);
            textCenter(226, i18n::tr(S_BACK));

            frameEnd();

            if (pressed(gb_buttons::KEY_A) || pressed(gb_buttons::KEY_B)) return;
        }
    }
}
