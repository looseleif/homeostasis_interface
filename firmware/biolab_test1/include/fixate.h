#ifndef FIXATE_H
#define FIXATE_H

/*
*
* This is the driver for the fixate affector, a HCSR-04 ultrasonic sensor that's used
* to measure how far a way a given object is. This sensor works by standing at the entrance
* of a cave, taking your phone timer out, yelling really loud, listening for your echo 
* and then stopping your timer when you hear it, except not really. We drive the trigger
* pin, telling the sensor to 'yell', then we listen for the 'echo' on the echo pin. The
* library for this sensor covers essentially all the details of that process for us.
*
*/

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