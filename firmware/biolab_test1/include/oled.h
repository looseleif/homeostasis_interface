#ifndef OLED_H
#define OLED_H

/*
*
* This is the driver (or better put, the wrapper) for the Adafruit SH110X series 
* of monochrome OLED. Most of the functions in this class are meant to assist
* in our device's application specific tasks.
*
*/

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <SPI.h>
#include <ssd1327.h>
#include <Adafruit_GrayOLED.h>
#include <string.h>

#define OLED_MOSI     5
#define OLED_CLK      7
#define OLED_DC       2
#define OLED_CS       4
#define OLED_RST      3

static const char * numberWords[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight","nine", "ten", "eleven", "twelve", "thirteen", "many", "a lot", "all"};

class oled: public _device 
{

    private: 

        menu *_oled_menu_ptr;

    public:

        oled(menu *ptr);

        void bootingPrint(void);
        void resetPrint(void);
        void pleaseWaitPrint(void);
		void goingHomePrint(void);
        void clear(void);
        void printGameMenu(void);
        void printAffectorMenu(void);
        void printPortMenu(void);
        void printAdditionMenu(void);
		void playingInfo(int game);
		void turnPrint(int turn);
        void printAgainMenu(void);
        void printDemo(int8_t demo_type, int8_t demo_val1, int8_t demo_val2);
        void printGameOver(void);
        void printWin(void);
        void printNumber(int score);

};

#endif