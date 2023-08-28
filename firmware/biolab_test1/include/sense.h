#ifndef CONDUCT_H
#define CONDUCT_H

/*
*
* This is the incomplete driver for the sense affector, a Adafruit ADXL343 accelerometer
* that will be used as another physical interface for playing the game demos.
*
*/

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include <SlowSoftI2CMaster.h>
#include <avr/io.h>

class sense: public _affector
{

    private:

        SlowSoftI2CMaster *sense_soft;

    public:

        sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);
        void sense::captureData(void) override;
        void sense::updateGame(int x) override;
        int8_t sense::returnVal(void) override;
        uint8_t sense::returnPos(void) override;
        unsigned long _X;
        unsigned long _Y;
        unsigned long _Z;
        int xval, yval, zval;
        strip *_strip;
        oled *_oled;
        menu *_menu;

};

#endif

