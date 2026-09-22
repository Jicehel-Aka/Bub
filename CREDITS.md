# Credits & attribution

This project is a **port of BUB**, a "bubble-slurping platform puzzle game".

## Original work

- **Title:** BUB
- **Author / copyright holder:** Owen Swerkstrom (a.k.a. *penduin*), under the
  *smogheap* project.
- **Copyright:** © 2014–2019 Owen Swerkstrom.
- **Original source:** https://gitlab.com/smogheap/bub
  (mirror formerly at https://github.com/smogheap/bub)
- **Play the original:** http://bub.penduin.net
- **License:** GNU General Public License v3.0 **only** (GPL-3.0-only).

The original game (HTML5/JavaScript prototype) includes the level designs, the
game rules, and the artwork/sound. The **level layouts** and the **game logic**
reproduced here are derived directly from that original and remain
© Owen Swerkstrom under the GPL.

## This port

- A re-implementation of BUB's game logic in **C++** for the **Gamebuino AKA**
  console (ESP32-S3), wrapped in a reusable shell (title/menu, 5-language
  interface, SD save, return-to-loader).
- The 111 level layouts in `main/game/Levels.cpp` are taken from the original
  `index.html` `LEVELS` array (converted by `tools/update.py`).
- The gameplay in `main/core/Game.cpp` faithfully reproduces the original
  mechanics: 2-item inventory, bubble/key *slurp*, *plop-and-climb* to gain
  height, pushable crates, gravity, one-way `<`/`>` barriers, key/door, and
  "reach the flag to win".

### Summary of changes from the original (GPLv3 §5a)

- Rewrote the JavaScript/DOM logic as C++ for the AKA hardware.
- Replaced the original PNG/sound assets with **vector rendering** built from
  `gb_graphics` primitives. **No original artwork or audio is included** in this
  repository.
- Added a Gamebuino AKA shell: menu, 5-language i18n, sound toggle, level-resume
  save on SD, and return-to-loader.
- Dropped the in-browser level editor / sharing and the speedrun timer.

## License

Because the original is GPL-3.0-only, **this port is also distributed under the
GNU General Public License v3.0 only**. See the `LICENSE` file for the full
text. If you distribute this software (source or as a flashed binary), you must
pass on the same freedoms and make the corresponding source available.

If you are the original author and would like the attribution adjusted, please
open an issue on the port's repository.

## PC (SDL2) build

The desktop version under `pc/` uses a small SDL2 backend implementing the same
`gb_*` API. It bundles no game assets. Third-party components of that target:

- **SDL2** — zlib license (GPL-compatible).
- **font8x8** by Daniel Hepper — Public Domain.

The game code and level data remain under **GPL-3.0-only**.
