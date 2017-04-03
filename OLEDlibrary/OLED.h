/*
 * OLED.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Dinh
 */

/*
 * This is the library ported from Arduino's MicroLCD library
 * with some extra features added by me (including print and printwrap)
 */

#ifndef OLEDSAMPLEAPP_OLEDLIBRARY_OLED_H_
#define OLEDSAMPLEAPP_OLEDLIBRARY_OLED_H_

#include "../wrappedI2C/wrappedi2c.h"

  #define SSD1306_LCDWIDTH                  128
  #define SSD1306_LCDHEIGHT                 32

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


void OLEDbegin();
void WriteCommand(unsigned char ins);
void OLEDclear(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void setCursor(uint8_t x, uint8_t y);
void draw(const uint8_t* buffer, uint8_t width, uint8_t height);
uint8_t write(uint8_t c);
void writeDigit(uint8_t n);
void OLEDprint(char *theString);
void OLEDprintln(char *theString);
void OLEDprintwrap(char *theString);
void OLEDsinglePrint(char *theString);
void ShowLoadingScreen();
void OLEDreset();

void drawArrow();
void drawCAN();
void drawLAN();
void drawTS();

void deleteCAN();
void deleteLAN();
void deleteTS();


void drawSDCSOK();
void drawSDCSunreachable();

extern uint8_t m_col;
extern uint8_t m_row;
extern uint8_t OLEDbroken;
#endif /* OLEDSAMPLEAPP_OLEDLIBRARY_OLED_H_ */
