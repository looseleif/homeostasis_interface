#ifndef OLED_H
#define OLED_H

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1325.h>
#include <Adafruit_SH110X.h>

#define OLED_MOSI     5
#define OLED_CLK      7
#define OLED_DC       2
#define OLED_CS       4
#define OLED_RST      3

inline Adafruit_SH1107 screen(128, 128, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

static const unsigned char images[3][1300] PROGMEM = { 

{

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xc0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xf0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x07,0xff,0xfe,0x7f,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1f,0xfc,0x07,0xff,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1f,0xf8,0x01,0xff,0xe0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x3f,0xf0,0x00,0xff,0xf0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x7f,0xe0,0x00,0x7f,0xf0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x7f,0xc0,0x00,0x3f,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x7f,0xc0,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xff,0x80,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xff,0x80,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xff,0x80,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0xff,0x80,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0xff,0x80,0x00,0x1f,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0xff,0xc0,0x00,0x1f,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xff,0xc0,0x00,0x3f,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xff,0xe0,0x00,0x7f,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xff,0xf0,0x00,0xff,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0xff,0xf8,0x01,0xff,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0xff,0xfe,0x07,0xff,0xbf,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0xe7,0xff,0xff,0xff,0x3f,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe3,0xdf,0xff,0xfe,0x3f,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe0,0xef,0xff,0xf8,0x1f,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xc0,0x3f,0xff,0xf0,0x1f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xc0,0x07,0xff,0x80,0x1f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xc0,0x00,0x30,0x00,0x1f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x07,0xff,0x80,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x0f,0xff,0xc0,0x00,0x00,0x00,0x0f,0x80,0x00,0x00,0x00
,0x00,0x00,0x0f,0xfc,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00
,0x00,0x00,0x0f,0xfe,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xfe,0x00,0x00,0x00,0x00,0x40,0x00,0x40,0x00,0x00
,0x00,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x3e,0xf8,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x3f,0xf0,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x7f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x7f,0xf0,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00
,0x00,0x00,0x7f,0xe0,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00
,0x00,0x00,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0xff,0xe0,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00
,0x00,0x00,0xff,0xc0,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00
,0x00,0x01,0xff,0xc0,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00
,0x00,0x01,0xff,0xc0,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00
,0x00,0x01,0xff,0x40,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00
,0x00,0x03,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x03,0xff,0x80,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00
,0x00,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00
,0x00,0x07,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xfc,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00
,0x00,0x0f,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x0f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00
,0x00,0x0f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00
,0x00,0x1f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00
,0x00,0x1f,0xe8,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00
,0x00,0x1f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00
,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00
,0x00,0x7f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x7f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x7f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00
,0x00,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x01,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x01,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00
,0x01,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x03,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00
,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x07,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00
,0x07,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00
,0x07,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00
,0x0f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x0f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x0f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x1f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x1f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
,0x1f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x3f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40
,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x40
,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x7f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40
,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x0f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

},

{  

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x06,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x66,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xf6,0xb0,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xfc,0x27,0xe1,0xf0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x02,0xdd,0xaf,0xe1,0x78,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x6c,0xa7,0xb3,0x58,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x60,0x27,0xff,0xf0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x91,0xa7,0x80,0xf3,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x90,0x2c,0x00,0x1f,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xc8,0x38,0x00,0x3e,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x40,0x30,0x00,0x1f,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x61,0x60,0x00,0x07,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x23,0xc0,0x05,0x03,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x31,0xc0,0x3e,0x01,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x31,0x80,0x7f,0xfd,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x13,0x00,0x60,0x7f,0xf1,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x33,0x00,0x40,0x00,0x0d,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x33,0x80,0x80,0x08,0x6f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x33,0x03,0xa0,0x02,0xff,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x23,0x01,0x20,0x00,0xb3,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x63,0x01,0x50,0x00,0x00,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x62,0x03,0xa0,0x00,0x03,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xc2,0x03,0x40,0x7f,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0xc2,0x03,0x80,0xfc,0x4e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x9a,0x07,0x80,0xec,0x7e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xc2,0x06,0x01,0xe0,0x67,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x03,0x06,0x81,0x60,0x46,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x06,0x06,0x04,0x05,0x40,0x4e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x06,0x06,0x04,0x07,0x40,0x1e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x07,0x06,0x03,0x00,0x1f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0c,0x07,0xbe,0x03,0x80,0x03,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x08,0x06,0x63,0x82,0xc4,0x07,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x08,0x16,0x18,0xf2,0x7c,0x1e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x08,0x16,0x02,0x1a,0xfe,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x06,0x04,0x0f,0x83,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x0c,0x00,0x06,0x71,0xe0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x3a,0x41,0x86,0x00,0xe0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1c,0x70,0x00,0x06,0x00,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1c,0xc0,0x03,0x0f,0x00,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1e,0xc0,0x00,0x0f,0x04,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x80,0x20,0xb6,0x86,0x70,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x40,0x00,0xe4,0x80,0xb0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x00,0x01,0x2c,0x40,0x70,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x40,0x00,0x4c,0x60,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x60,0x03,0x9e,0x50,0x90,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x20,0x06,0x5c,0x10,0x10,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x10,0x04,0xac,0x01,0x10,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x06,0x00,0x08,0x5c,0x00,0x90,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x06,0x20,0x00,0x9e,0x00,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x02,0x10,0x01,0x2c,0x01,0xb0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x00,0x02,0x2a,0x00,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x00,0x06,0x2b,0x01,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x88,0x04,0x49,0x00,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x80,0x00,0x49,0x80,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xc8,0x00,0x51,0x00,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x60,0x00,0x58,0x06,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x22,0x00,0x58,0x00,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x30,0x00,0x40,0x08,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x18,0x00,0x40,0x05,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0e,0x00,0x40,0x01,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x03,0x00,0x40,0x1b,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0x60,0x06,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x24,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x0c,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x48,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x98,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x0c,0x44,0x30,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x06,0x1e,0x20,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x03,0x86,0xe0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0xe3,0x80,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  
},

{

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xff,0xfb,0xfb,0xfc,0x7e,0xba,0x38,0x00,0x00,0x00,0x00
,0x00,0x03,0xff,0xff,0xff,0xf0,0x00,0x1f,0xff,0xff,0xfd,0x80,0x00
,0x00,0x07,0xff,0x83,0xff,0xe0,0x00,0x0f,0xff,0xff,0xff,0x80,0x00
,0x00,0x07,0xf8,0x00,0x7f,0xc0,0x00,0x07,0xff,0x80,0x7f,0x80,0x00
,0x00,0x3f,0xe0,0x00,0x1f,0x80,0x00,0x07,0xfc,0x00,0x0f,0xd0,0x00
,0x00,0x3f,0xc0,0x78,0x07,0x80,0x00,0x07,0xf8,0x00,0x03,0xf0,0x00
,0x00,0x3f,0x03,0xff,0x83,0xe0,0x00,0x07,0xe0,0x7f,0xc1,0xf0,0x00
,0x00,0x3e,0x0f,0xff,0xc1,0xd0,0x00,0x07,0xc1,0xff,0xf0,0xf0,0x00
,0x00,0x3e,0x1f,0xff,0xf0,0xec,0xbf,0xcf,0x83,0xff,0xf8,0x70,0x00
,0x00,0x3c,0x3f,0x77,0xf8,0x7f,0xff,0xff,0x0f,0xff,0xfc,0x30,0x00
,0x00,0x38,0x7c,0x01,0xfc,0x7f,0xff,0xff,0x0e,0xfb,0xfe,0x30,0x00
,0x00,0x38,0xf9,0x6c,0xfc,0x3f,0xff,0xfe,0x1f,0xef,0x7f,0x10,0x00
,0x00,0x30,0xf0,0x82,0x7e,0x3f,0xff,0xfe,0x3f,0xc1,0xff,0x10,0x00
,0x00,0x31,0xf2,0x00,0x9e,0x3f,0xff,0xfe,0x3f,0x01,0xff,0x80,0x00
,0x00,0x31,0xec,0x00,0x8f,0x1f,0xff,0xfc,0x7f,0xa3,0xff,0x80,0x00
,0x00,0x21,0xd0,0x01,0x7f,0x1f,0xff,0xfc,0x7f,0xc7,0xff,0xc0,0x00
,0x00,0x63,0xc8,0x02,0x5f,0x17,0xff,0xfc,0x7f,0xe3,0xef,0xc0,0x00
,0x00,0x63,0xbe,0x12,0x7f,0x1f,0xff,0xfc,0x7f,0xff,0xbf,0xc0,0x00
,0x00,0x63,0xd9,0x24,0xff,0x1f,0xff,0xfc,0x7f,0xf7,0x5f,0xc0,0x00
,0x00,0x63,0xe8,0x78,0x6f,0x1f,0xff,0xfc,0x7e,0x3f,0xcf,0xc0,0x00
,0x00,0x61,0xda,0x79,0x7f,0x1f,0xff,0xfc,0x7e,0x7f,0xff,0xc0,0x00
,0x00,0x71,0xec,0x9e,0x5f,0x1f,0xff,0xfc,0x7f,0xff,0xff,0x80,0x00
,0x00,0x71,0xf7,0x39,0xfe,0x3f,0xff,0xfc,0x3f,0xff,0xff,0x80,0x00
,0x00,0x71,0xff,0xbf,0xfe,0x3f,0xff,0xfe,0x3f,0xff,0xff,0x80,0x00
,0x00,0x78,0xff,0xff,0xfc,0x3f,0xff,0xfe,0x1f,0xff,0xff,0x10,0x00
,0x00,0x78,0x7f,0xff,0xfc,0x7f,0xff,0xff,0x1f,0xff,0xff,0x10,0x00
,0x00,0x7c,0x7f,0xff,0xf8,0xff,0xff,0xff,0x0f,0xff,0xfe,0x30,0x00
,0x00,0x7c,0x3f,0xff,0xf0,0xff,0xff,0xff,0x87,0xff,0xfc,0x70,0x00
,0x00,0x7e,0x0f,0xff,0xe1,0xff,0xff,0xff,0xc3,0xff,0xf8,0x70,0x00
,0x00,0x7f,0x07,0xff,0x83,0xff,0xff,0xff,0xe0,0xff,0xe0,0xf0,0x00
,0x00,0x7f,0x80,0xfc,0x07,0xff,0xff,0xff,0xf0,0x3f,0x01,0xf0,0x00
,0x00,0x7f,0xe0,0x00,0x1f,0xff,0xff,0xff,0xf8,0x00,0x07,0xf0,0x00
,0x00,0x7f,0xf8,0x00,0x7f,0xff,0xff,0xff,0xfe,0x00,0x1f,0xf0,0x00
,0x00,0x4f,0xff,0x87,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0x80,0x00
,0x00,0x07,0xff,0xff,0xff,0xf7,0xfb,0xdf,0xff,0xff,0xff,0x80,0x00
,0x00,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00
,0x00,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

}

};

static const unsigned char thumbsUp [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x18, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x07, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x18, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
	0x18, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x0c, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0c, 0x18, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x3c, 0x00, 
	0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

static const unsigned char unoCard [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x87, 
	0xff, 0xff, 0xf8, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x07, 0xff, 0xff, 0x80, 
	0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x07, 0xff, 0xfe, 0x00, 0xf0, 0x0f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x37, 0xff, 0xf8, 0x1f, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xf8, 0x7f, 0xff, 0xe0, 0x7f, 0xff, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 
	0xff, 0xff, 0xc1, 0xff, 0xff, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf9, 0x3f, 0xff, 0x07, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x1f, 0xfe, 0x1f, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xe8, 0x3f, 0xf0, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xc0, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc1, 0xff, 0xc3, 
	0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc1, 0xff, 0x87, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc1, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf8, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf0, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 
	0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x0f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xfc, 0x3f, 0xff, 0xf8, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xfc, 0x7f, 0xff, 0xe0, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x7f, 0xff, 
	0xf0, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0xff, 0xff, 0xf8, 0x03, 0xff, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf1, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xe1, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xe3, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc3, 0xff, 
	0xff, 0x80, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc7, 0xff, 0xfe, 0x00, 0x07, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0xff, 0xfe, 0x00, 0x47, 0xff, 0xfc, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x8f, 0xff, 0xfc, 0x01, 0xe7, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x0f, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 
	0xff, 0xf8, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1f, 0xff, 0xf8, 0x0f, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3f, 0xff, 0xf8, 0x19, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3f, 0xff, 0xf8, 0x70, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x04, 0x7f, 0xff, 0xf8, 0xe0, 0xff, 0xff, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xfd, 0xc0, 0xff, 0xff, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0x80, 0xff, 0xff, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 
	0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7c, 0x00, 0xff, 0xff, 0xc7, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x38, 0x01, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 
	0x00, 0x07, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x0f, 0xff, 
	0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xfe, 0x3f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xfe, 0x3f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
	0xfe, 0x00, 0xff, 0xff, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x7f, 
	0xff, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xf0, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc7, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf8, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
	0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0x1f, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xfe, 0x1f, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfc, 0x1f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xff, 0xc1, 0xff, 0xf0, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0x87, 0xff, 0xe1, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x3f, 0xff, 0xfe, 0x0f, 0xff, 0xe2, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0xff, 0xf8, 0x3f, 0xff, 0xe4, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x07, 0xff, 0xe0, 0x7f, 0xff, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0x80, 0xfe, 0x01, 0xff, 0xff, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 
	0x0f, 0xff, 0xff, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x3f, 0xff, 0xff, 
	0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x03, 0xff, 0xff, 0xff, 0x07, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

static const char * numberWords[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight","nine", "ten", "eleven", "twelve", "thirteen", "many", "a lot", "all"};

class oled: public _device 
{

    private: 

        menu *_oled_menu_ptr;

    public:

        Adafruit_SH1107* _screen;
        oled(menu *ptr);
        void sendBitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);
        void sendString(String toSend);
        void bootingPrint(void);
        void rebootingPrint(void);
        void pleaseWaitPrint(void);
        void clearAll(void);
        void printGameMenu(void);
        void printDemoMenu(void);
        void printDeviceMenu(void);
        void printAdditionMenu(void);
        void printAgainMenu(void);
        void printSelector(int prev, int next, bool clear);
        void printDemo(int8_t demo_type, int8_t demo_val1, int8_t demo_val2);
        void printGameOver(void);
        void printWin(void);
        void printLose(void);
        void printNumber(int score);

};

#endif