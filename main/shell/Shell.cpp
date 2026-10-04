/**
 * @file Shell.cpp
 * @brief Implementation de la coquille BUB.
 */

#include "Shell.h"
#include "ShellCore.h"
#include "Menu.h"
#include "I18n.h"
#include "Config.h"
#include "Loader.h"

#include "core/Game.h"

#include <string.h>

namespace shell
{
    // --- Instances materielles globales ---
    gb_core         g_core;
    gb_graphics     g_gfx;
    gb_audio_player g_audio;
    Config          g_cfg;

    // --- Palette ---
    uint16_t COL_BG  = 0;
    uint16_t COL_FG  = 0;
    uint16_t COL_HL  = 0;
    uint16_t COL_DIM = 0;

    void applyVolume()
    {
        g_audio.set_master_volume(g_cfg.sound ? 200 : 0);
    }

    // --- Helpers texte (police 8x8 ASCII, glyphe large de 8 px) ---
    void text(int x, int y, const char* s)
    {
        g_gfx.move_cursor((uint16_t)x, (uint16_t)y);
        g_gfx.print_str(s);
    }

    void textCenter(int y, const char* s)
    {
        int w = (int)strlen(s) * 8;
        int x = (320 - w) / 2;
        if (x < 0) x = 0;
        text(x, y, s);
    }

    // --- HOME (RUN) + MENU maintenus 500 ms : retour immediat au Launcher ---
    static bool loaderComboHeld()
    {
        static uint32_t t0 = 0;

        uint16_t s    = g_core.buttons.state();
        bool     both = (s & gb_buttons::KEY_RUN) && (s & gb_buttons::KEY_MENU);

        if (!both)
        {
            t0 = 0;
            return false;
        }

        uint32_t now = g_core.get_millis();
        if (t0 == 0) t0 = now;
        return (now - t0) >= 500;
    }

    static void goToLauncher()
    {
        // Attend le relachement des deux touches (3 s max) : sinon le Launcher
        // demarre avec MENU encore enfonce et ouvre ses options.
        const uint16_t both = gb_buttons::KEY_RUN | gb_buttons::KEY_MENU;
        const uint32_t t0   = g_core.get_millis();
        while ((g_core.buttons.state() & both) && (g_core.get_millis() - t0) < 3000)
        {
            g_core.delay_ms(10);
            g_core.pool();
        }
        loader::returnToLoader();         // ne revient pas
    }

    void frameBegin()
    {
        g_core.pool();
        if (loaderComboHeld())
            goToLauncher();
    }

    void frameEnd()
    {
        g_gfx.update();
        g_core.delay_ms(16);              // ~60 fps
    }

    // --- Boucle de jeu ---
    // MENU (appui court sans RUN) revient au menu. HOME(RUN)+MENU 500 ms -> Launcher.
    // Le niveau atteint est sauvegarde dans la config (reprise via /sdcard/BUB/CFG.DAT).
    static void gameLoop()
    {
        Game game;
        game.begin(g_cfg.level);

        for (;;)
        {
            frameBegin();

            uint16_t runHeld = g_core.buttons.state() & gb_buttons::KEY_RUN;
            if (!runHeld && g_core.buttons.pressed(gb_buttons::KEY_MENU))
                return;                   // retour menu

            game.update();

            // Sauvegarde de la progression quand on change de niveau.
            if (game.levelNumber() != g_cfg.level)
            {
                g_cfg.level = game.levelNumber();
                config::save(g_cfg);
            }

            game.render();

            frameEnd();

            if (game.wantsMenu()) return; // partie terminee (dernier niveau)
        }
    }

    static void init()
    {
        g_core.init();
        g_gfx.set_backlight_percent(100);
        g_gfx.set_refresh_rate(60);

        COL_BG  = g_gfx.makeColor(16, 16, 32);
        COL_FG  = g_gfx.makeColor(230, 230, 230);
        COL_HL  = g_gfx.makeColor(255, 210, 60);
        COL_DIM = g_gfx.makeColor(140, 140, 160);

        config::load(g_cfg);
        i18n::set(g_cfg.lang);
        applyVolume();
    }

    void run()
    {
        init();

        for (;;)
        {
            menu::title();

            for (;;)
            {
                switch (menu::mainMenu())
                {
                    case menu::ACT_PLAY:
                        gameLoop();
                        break;

                    case menu::ACT_LANGUAGE:
                        menu::language();
                        break;

                    case menu::ACT_SOUND:
                        g_cfg.sound = !g_cfg.sound;
                        applyVolume();
                        config::save(g_cfg);
                        break;

                    case menu::ACT_RULES:
                        menu::rules();
                        break;

                    case menu::ACT_CREDITS:
                        menu::credits();
                        break;

                    case menu::ACT_QUIT:
                        loader::returnToLoader();   // ne revient pas
                        break;
                }
            }
        }
    }
}
