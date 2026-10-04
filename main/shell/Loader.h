/**
 * @file Loader.h
 * @brief Retour au loader AKA.
 */

#pragma once

namespace loader
{
    //! Bascule le boot sur la partition du Launcher (app1/OTA_1, ou factory dans
    //! l'ancienne organisation) puis redemarre. Ne revient jamais.
    [[noreturn]] void returnToLoader();
}
