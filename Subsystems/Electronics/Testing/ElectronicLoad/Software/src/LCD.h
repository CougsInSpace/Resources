/*
$Id:$

ST7565 LCD library!

Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

// some of this code was written by <cstone@pobox.com> originally; it is in the
public domain.
*/

#ifndef _st7565LCD_H_
#define _st7565LCD_H_

#include "mbed.h"

#define swap(a, b)                                                             \
  {                                                                            \
    uint8_t t = a;                                                             \
    a         = b;                                                             \
    b         = t;                                                             \
  }

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define INITIAL_CONTRAST 0x18

#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON 0xAF

#define CMD_SET_DISP_START_LINE 0x40
#define CMD_SET_PAGE 0xB0

#define CMD_SET_COLUMN_UPPER 0x10
#define CMD_SET_COLUMN_LOWER 0x00

#define CMD_SET_ADC_NORMAL 0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON 0xA5
#define CMD_SET_BIAS_9 0xA2
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW 0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET 0xE2
#define CMD_SET_COM_NORMAL 0xC0
#define CMD_SET_COM_REVERSE 0xC8
#define CMD_SET_POWER_CONTROL 0x28
#define CMD_SET_RESISTOR_RATIO 0x20
#define CMD_SET_VOLUME_FIRST 0x81
#define CMD_SET_VOLUME_SECOND 0x00
#define CMD_SET_STATIC_OFF 0xAC
#define CMD_SET_STATIC_ON 0xAD
#define CMD_SET_STATIC_REG 0x0
#define CMD_SET_BOOSTER_FIRST 0xF8
#define CMD_SET_BOOSTER_234 0
#define CMD_SET_BOOSTER_5 1
#define CMD_SET_BOOSTER_6 3
#define CMD_NOP 0xE3
#define CMD_TEST 0xF0

class ST7565 {
private:
  SPI        _spi;
  DigitalOut _cs;
  DigitalOut _rst;
  DigitalOut _a0;
  void       spiwrite(uint8_t c);
  void       my_setpixel(uint8_t x, uint8_t y, uint8_t color);

  // uint8_t buffer[128*64/8];
public:
  ST7565(PinName mosi, PinName sclk, PinName cs, PinName rst, PinName a0);
  ~ST7565() {};
  void st7565_init(void);
  void begin(uint8_t contrast);
  void st7565_command(uint8_t c);
  void st7565_data(uint8_t c);
  void st7565_set_brightness(uint8_t val);
  void clear_display(void);
  void clear();
  void display();

  void    setpixel(uint8_t x, uint8_t y, uint8_t color);
  uint8_t getpixel(uint8_t x, uint8_t y);
  void    fillcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
  void    drawcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
  void    drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
  void    fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
  void drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
  void drawchar(uint8_t x, uint8_t line, char c);
  void drawstring(uint8_t x, uint8_t line, const char * c);
  /*void drawbitmap(uint8_t x, uint8_t y,
          const uint8_t *bitmap, uint8_t w, uint8_t h,
          uint8_t color);*/
  uint8_t _BV(uint8_t bit);
  uint8_t _nBV(uint8_t bit);
};

#endif