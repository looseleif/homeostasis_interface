#ifndef FIXATE_H
#define FIXATE_H

#include <string.h>
#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>
#include <NewPing.h>
#include <HCSR04.h>

class fixate: public _affector
{

    private:
    
        strip *_strip;
        oled *_oled;
        menu *_menu;
        int8_t trigPin, echoPin;
        uint8_t pos;
        UltraSonicDistanceSensor *fixate_ultra;
        bool prevAVal, prevBVal;
        bool pinAVal, pinBVal;

    public:

        fixate(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);
        void fixate::captureData(void) override;
        void fixate::updateGame(int x) override;
        int8_t fixate::returnVal(void) override;
        uint8_t fixate::returnPos(void) override;
        
};

#endif