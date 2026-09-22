# Build PC (SDL2) de BUB via le backend officiel de jmp42 (Gamebuino_AKA_lib_sdl).
#
# Ce backend EST la vraie bibliotheque AKA : il recompile le gb_lib embarque dans
# components/gamebuino et remplace seulement la couche bas niveau (gb_ll_*) par SDL.
# Aucune source du jeu n'est modifiee ; main() est fourni par le backend (il appelle
# app_main comme le fait ESP-IDF).
#
# Utilisation :
#   cmake -S sdl -B sdl/build -G Ninja -DAKA_SDL_BACKEND=<dossier Gamebuino_AKA_lib_sdl>
#   cmake --build sdl/build
#   sdl/build/bub            (ou bub.exe sous Windows)

cmake_minimum_required(VERSION 3.16)
project(bub C CXX)

# Emplacement du backend SDL (a adapter, ou passer -DAKA_SDL_BACKEND=...).
set(AKA_SDL_BACKEND "C:/github/Gamebuino_AKA_lib_sdl"
    CACHE PATH "Chemin du depot Gamebuino_AKA_lib_sdl")

if(NOT EXISTS "${AKA_SDL_BACKEND}/cmake/AkaGameOnSdl.cmake")
    message(FATAL_ERROR
        "Backend SDL introuvable dans '${AKA_SDL_BACKEND}'.\n"
        "Recupere https://github.com/jmp42/Gamebuino_AKA_lib_sdl et passe "
        "-DAKA_SDL_BACKEND=<dossier>.")
endif()

include("${AKA_SDL_BACKEND}/cmake/AkaGameOnSdl.cmake")

# ROOT = le dossier du jeu (celui qui contient main/ et components/). Le backend
# lit tout seul main/CMakeLists.txt (SRCS/INCLUDE_DIRS), donc Sprites.cpp, la
# coquille, etc. sont pris automatiquement, et il se lie a components/gamebuino.
aka_sdl_game(bub ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
