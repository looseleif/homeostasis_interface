#ifndef CONDUCT_H
#define CONDUCT_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>

class sense: public _affector
{

    private:

        Adafruit_ADXL343* sense_accel;

    public:

        sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);

        void sense::captureData(void) override;
        void sense::updateGame(int x) override;
        int8_t sense::returnVal(void) override;
        uint8_t sense::returnPos(void) override;
        
        strip *_strip;
        oled *_oled;
        menu *_menu;

};

#endif

