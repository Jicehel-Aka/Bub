#pragma once
#include <stdint.h>
#include <stddef.h>
#include "gb_common.h"
class gb_buttons { public:
  enum gb_key { KEY_RUN=GB_KEY_RUN,KEY_MENU=GB_KEY_MENU,KEY_L1=GB_KEY_L1,KEY_R1=GB_KEY_R1,
    KEY_RIGHT=GB_KEY_RIGHT,KEY_UP=GB_KEY_UP,KEY_DOWN=GB_KEY_DOWN,KEY_LEFT=GB_KEY_LEFT,
    KEY_A=GB_KEY_A,KEY_B=GB_KEY_B,KEY_C=GB_KEY_C,KEY_D=GB_KEY_D};
  void update(); uint16_t state(); uint16_t pressed(); bool pressed(gb_key);
  uint16_t released(); bool released(gb_key); void set_run_power_off(bool);
};
class gb_joystick { public: void update(); };
class gb_core { public: gb_core(); ~gb_core();
  int init(); void pool(); gb_buttons buttons; gb_joystick joystick;
  void delay_ms(uint32_t); uint32_t get_millis(); int64_t get_micros();
  size_t free_psram(); size_t free_sram(); void power_down(); };
