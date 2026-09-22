# Build de la version PC (SDL2) de BUB.
#   make            -> compile ./bub
#   make run        -> compile puis lance
#   make clean
#
# Prerequis : un compilateur C++17 et la SDL2 de dev.
#   Debian/Ubuntu : sudo apt install libsdl2-dev
#   macOS (brew)   : brew install sdl2
#   Windows        : MSYS2  pacman -S mingw-w64-x86_64-SDL2

CXX      ?= c++
CXXFLAGS ?= -std=gnu++17 -O2 -Wall -Wextra -DBUB_PC
ROOT     := ..

SDL_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null || sdl2-config --cflags 2>/dev/null)
SDL_LIBS   := $(shell pkg-config --libs   sdl2 2>/dev/null || sdl2-config --libs   2>/dev/null)

INC := -I. \
       -I$(ROOT)/main -I$(ROOT)/main/core -I$(ROOT)/main/game -I$(ROOT)/main/shell

SRC := main_sdl.cpp backend_sdl.cpp \
       $(ROOT)/main/shell/Shell.cpp \
       $(ROOT)/main/shell/Menu.cpp \
       $(ROOT)/main/shell/I18n.cpp \
       $(ROOT)/main/shell/Config.cpp \
       $(ROOT)/main/shell/Loader.cpp \
       $(ROOT)/main/core/Game.cpp \
       $(ROOT)/main/core/Input.cpp \
       $(ROOT)/main/core/Renderer.cpp \
       $(ROOT)/main/game/Level.cpp \
       $(ROOT)/main/game/LevelManager.cpp \
       $(ROOT)/main/game/Levels.cpp \
       $(ROOT)/main/game/Sprites.cpp

bub: $(SRC)
	$(CXX) $(CXXFLAGS) $(INC) $(SDL_CFLAGS) $(SRC) -o bub $(SDL_LIBS)

run: bub
	./bub

clean:
	rm -f bub

.PHONY: run clean
