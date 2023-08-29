#ifndef STRIP_H
#define STRIP_H

/*
*
* This is the driver (or better put, the wrapper) for a variety of available 
* programable LED strips. Most of the functions in this class are meant to assist
* in our device's application specific tasks.
*
*/

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <FastLED.h>

#define DATA_PIN 24 //PA0
#define NUM_LEDS 30
class strip: public _device 
{

    public:
        CRGBPalette16 currentPalette;
        TBlendType    currentBlending;
        uint8_t startIndex = 0;
        CRGBPalette16 myRedWhiteBluePalette;
        const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
        menu *_strip_menu_ptr;
        CRGB leds[NUM_LEDS];
        strip(menu *_menu_ptr);
        void setIntensity(int val);
        void setColor(int r, int g, int b);
        void sweepColor(int r, int g, int b, int rate);
        void inverseSweep(int rate);
        void lubDub(void);
        void winAnimation(void);

};

#endif