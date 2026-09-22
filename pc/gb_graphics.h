#pragma once
#include <stdint.h>
class gb_graphics { public: gb_graphics(); ~gb_graphics();
  void clear(uint16_t); void clear();
  void drawLine(int16_t,int16_t,int16_t,int16_t);
  void drawFastVLine(int16_t,int16_t,int16_t); void drawFastHLine(int16_t,int16_t,int16_t);
  void drawRect(int16_t,int16_t,int16_t,int16_t); void fillRect(int16_t,int16_t,int16_t,int16_t);
  void drawCircle(int16_t,int16_t,int16_t); void fillCircle(int16_t,int16_t,int16_t);
  void drawTriangle(int16_t,int16_t,int16_t,int16_t,int16_t,int16_t);
  void fillTriangle(int16_t,int16_t,int16_t,int16_t,int16_t,int16_t);
  void drawRoundRect(int16_t,int16_t,int16_t,int16_t,int16_t);
  void fillRoundRect(int16_t,int16_t,int16_t,int16_t,int16_t);
  void drawPixel(int16_t,int16_t,uint16_t); void drawPixel(int16_t,int16_t);
  void setColor(uint16_t); uint16_t makeColor(uint8_t,uint8_t,uint8_t);
  void draw_char(uint16_t,uint16_t,char); void move_cursor(uint16_t,uint16_t);
  void print_str(const char*); void printf(const char*,...);
  void set_backlight(uint16_t); uint16_t get_backlight();
  void set_backlight_percent(uint8_t); uint8_t get_backlight_percent();
  void set_refresh_rate(uint8_t); float get_fps(); void update(); };
