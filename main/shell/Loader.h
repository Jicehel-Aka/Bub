/**
 * @file Loader.h
 * @brief Retour au loader AKA.
 */

#pragma once

namespace loader
{
    //! Bascule le boot sur la partition "factory" (le loader) si presente,
    //! puis redemarre. Ne revient jamais.
    [[noreturn]] void returnToLoader();
}
