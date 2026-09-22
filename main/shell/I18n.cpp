/**
 * @file I18n.cpp
 * @brief Tables de traduction (FR/EN/DE/ES/IT) de la coquille BUB.
 */

#include "I18n.h"

namespace
{
    Lang g_lang = LANG_FR;

    // Ordre des colonnes : FR, EN, DE, ES, IT (cf enum Lang).
    const char* const TABLE[S_COUNT][LANG_COUNT] =
    {
        /* S_PRESS_START */ { "APPUYEZ SUR A", "PRESS A",     "DRUECKE A",   "PULSA A",     "PREMI A"      },
        /* S_PLAY        */ { "JOUER",         "PLAY",        "SPIELEN",     "JUGAR",       "GIOCA"        },
        /* S_LANGUAGE    */ { "LANGUE",        "LANGUAGE",    "SPRACHE",     "IDIOMA",      "LINGUA"       },
        /* S_SOUND       */ { "SON",           "SOUND",       "TON",         "SONIDO",      "AUDIO"        },
        /* S_RULES       */ { "REGLES",        "RULES",       "REGELN",      "REGLAS",      "REGOLE"       },
        /* S_QUIT        */ { "QUITTER",       "QUIT",        "BEENDEN",     "SALIR",       "ESCI"         },
        /* S_ON          */ { "OUI",           "ON",          "AN",          "SI",          "SI"           },
        /* S_OFF         */ { "NON",           "OFF",         "AUS",         "NO",          "NO"           },
        /* S_BACK        */ { "B = RETOUR",    "B = BACK",    "B = ZURUECK", "B = VOLVER",  "B = INDIETRO" },
        /* S_RULES_TITLE */ { "REGLES",        "RULES",       "REGELN",      "REGLAS",      "REGOLE"       },
        /* S_LEVEL       */ { "NIVEAU",        "LEVEL",       "EBENE",       "NIVEL",       "LIVELLO"      },
        /* S_COMPLETE    */ { "BRAVO !",       "WELL DONE!",  "GESCHAFFT!",  "MUY BIEN!",   "BRAVO!"       },
        /* S_WIN         */ { "TOUT FINI !",   "YOU WIN!",    "GEWONNEN!",   "GANASTE!",    "HAI VINTO!"   },
        /* S_CONTINUE    */ { "A = SUITE",     "A = NEXT",    "A = WEITER",  "A = SIGUE",   "A = AVANTI"   },
        /* S_RESTART     */ { "B = REESSAYER", "B = RETRY",   "B = NEU",     "B = REINTENTAR","B = RIPROVA" },
        /* S_CLIMB       */ { "MONTER",        "CLIMB",       "STEIGEN",     "SUBIR",       "SALIRE"       },
        /* S_CREDITS     */ { "CREDITS",       "CREDITS",     "CREDITS",     "CREDITOS",    "CREDITI"      },
    };

    const char* const LANG_NAMES[LANG_COUNT] =
    {
        "FRANCAIS", "ENGLISH", "DEUTSCH", "ESPANOL", "ITALIANO"
    };

    const char* const RULES[LANG_COUNT][5] =
    {
        { "BUT : ATTEINDRE LE DRAPEAU.", "MARCHE SUR BULLE = ASPIRE.", "HAUT : POSE BULLE, MONTE.", "CLE OUVRE LA PORTE.",  "INVENTAIRE : 2 OBJETS MAX." },
        { "GOAL: REACH THE FLAG.",       "STEP ON BUBBLE = SLURP.",    "UP: DROP BUBBLE, CLIMB.",   "KEY OPENS THE DOOR.",  "INVENTORY: 2 ITEMS MAX." },
        { "ZIEL: ERREICHE DIE FLAGGE.",  "AUF BLASE = AUFSAUGEN.",     "HOCH: BLASE LEGEN, STEIGEN.","SCHLUESSEL OEFFNET TUER.","INVENTAR: MAX 2 TEILE." },
        { "META: LLEGA A LA BANDERA.",   "PISA BURBUJA = ABSORBE.",    "ARRIBA: PON BURBUJA, SUBE.","LLAVE ABRE LA PUERTA.", "INVENTARIO: MAX 2." },
        { "META: RAGGIUNGI BANDIERA.",   "SU BOLLA = ASSORBI.",        "SU: POSA BOLLA, SALI.",    "CHIAVE APRE LA PORTA.", "INVENTARIO: MAX 2." },
    };
}

namespace i18n
{
    Lang current()      { return g_lang; }
    void set(Lang lang) { if (lang < LANG_COUNT) g_lang = lang; }

    const char* tr(Str id)
    {
        if (id >= S_COUNT) return "";
        return TABLE[id][g_lang];
    }

    const char* langName(Lang lang)
    {
        if (lang >= LANG_COUNT) return "";
        return LANG_NAMES[lang];
    }

    uint8_t rulesLineCount()
    {
        uint8_t n = 0;
        for (uint8_t i = 0; i < 5; ++i)
            if (RULES[g_lang][i][0] != '\0') ++n;
        return n;
    }

    const char* rulesLine(uint8_t index)
    {
        if (index >= 5) return "";
        return RULES[g_lang][index];
    }
}
