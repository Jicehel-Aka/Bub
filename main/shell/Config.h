/**
 * @file Config.h
 * @brief Configuration persistante (langue, son, niveau) sur SD : /sdcard/CFG.DAT.
 *
 * Nom 8.3 impose (CONFIG_FATFS_LFN_NONE). SD absente => valeurs par defaut,
 * sauvegarde ignoree.
 */

#pragma once

#include <stdint.h>
#include "I18n.h"

struct Config
{
    Lang     lang  = LANG_FR;
    bool     sound = true;
    uint16_t level = 0;    // niveau de reprise (0-based)
};

namespace config
{
    void load(Config& out);
    bool save(const Config& in);
}
