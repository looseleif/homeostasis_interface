#ifndef STRIP_H
#define STRIP_H

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <FastLED.h>

#define DATA_PIN D21 //PC7
#define NUM_LEDS 5
class strip: public _device 
{

    private:

    public:
        
        menu *_strip_menu_ptr;
        CRGB leds[NUM_LEDS];

        strip(menu *_menu_ptr);

        void setIntensity(int val);
        void setColor(int r, int g, int b);
        void sweepColor(int r, int g, int b, int rate);
        void lubDub(void);

};

#endif