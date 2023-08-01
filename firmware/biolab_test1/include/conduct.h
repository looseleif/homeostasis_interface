#ifndef CONDUCT_H
#define CONDUCT_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>

class conduct: public _affector
{

    private:

        Adafruit_ADXL343* conduct_accel;

    public:

        conduct(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);

        void conduct::captureData(void) override;
        void conduct::updateGame(int x) override;
        int8_t conduct::returnVal(void) override;
        uint8_t conduct::returnPos(void) override;
        
        strip *_strip;
        oled *_oled;
        menu *_menu;

};

#endif

