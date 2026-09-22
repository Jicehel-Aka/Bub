#pragma once
#include <stdint.h>
class gb_audio_player { public: gb_audio_player(); ~gb_audio_player();
  void pool(); void set_master_volume(uint8_t); uint8_t get_master_volume();
  void vibrator(uint32_t); };
