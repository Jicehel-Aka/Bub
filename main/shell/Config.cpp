/**
 * @file Config.cpp
 * @brief Lecture/ecriture de /sdcard/CFG.DAT.
 */

#include "Config.h"

#include <stdio.h>
#include <string.h>

#include "gb_ll_sdcard.h"   // gb_ll_sd_is_mounted()

namespace
{
#ifdef BUB_PC
    const char* CFG_PATH = "bub_save.dat";   // version PC : fichier local
#else
    const char* CFG_PATH = "/sdcard/CFG.DAT";
#endif

    struct CfgFile
    {
        char     magic[4];   // "BUB2"
        uint8_t  lang;
        uint8_t  sound;
        uint16_t level;
    };
}

namespace config
{
    void load(Config& out)
    {
        out = Config{};
        if (!gb_ll_sd_is_mounted()) return;

        FILE* f = fopen(CFG_PATH, "rb");
        if (!f) return;

        CfgFile c{};
        size_t n = fread(&c, 1, sizeof(c), f);
        fclose(f);

        if (n != sizeof(c) || memcmp(c.magic, "BUB2", 4) != 0) return;

        if (c.lang < LANG_COUNT) out.lang = static_cast<Lang>(c.lang);
        out.sound = (c.sound != 0);
        out.level = c.level;
    }

    bool save(const Config& in)
    {
        if (!gb_ll_sd_is_mounted()) return false;

        FILE* f = fopen(CFG_PATH, "wb");
        if (!f) return false;

        CfgFile c{};
        memcpy(c.magic, "BUB2", 4);
        c.lang  = static_cast<uint8_t>(in.lang);
        c.sound = in.sound ? 1 : 0;
        c.level = in.level;

        size_t n = fwrite(&c, 1, sizeof(c), f);
        fclose(f);
        return n == sizeof(c);
    }
}
