#ifndef DIRECT_H
#define DIRECT_H

/*
*
* This is the driver for the direct affector, a crankshaft that uses a (quadrature) rotary encoder to transmits its
* rotation direction (CW/CCW) to our microcontroller. There are a few ways to read the data from a rotary
* encoder (RE), the one used in this instance is a quadrature lookup table, we use a single interrupt to measure
* one of RE pins states, then immidately read the other pin, continuously performing these actions allows you to
* build a series of pin states, from this series you can use an established quadrature table (or make your own)
* to determine the direction the affector is being rotated.
*
* This article was a great resource for how to work with rotary encoders:
* https://docs.nanoframework.net/devicesdetails/RotaryEncoder/README.html
*
*/

#include <string.h>
#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>

#define CRANKRATESCALAR 80.0
#define GENERAL_RATETYPE 0
#define CRANKSUM_RATETYPE 1
#define STRIPREFRESHDELAY 50

class direct: public _affector
{

    private:
        
        int8_t quadratureLookupTable[16] = {0,0,0,-1,0,0,1,0,0,1,0,0,-1,0,0,0};
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        int8_t direct_pin1, direct_pin2;
        bool prevAVal, prevBVal, pinAVal, pinBVal;
        int8_t crankSum; //sums the number of valid pulses from the encoder
        int8_t encoderPinA, encoderPinB; //stores object pin configuration
        uint8_t pos;
        int8_t direction;

    public:
        
        direct(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);
        void direct::captureData(void) override;
        void direct::updateGame(int x) override;
        int8_t direct::returnVal(void) override;
        uint8_t direct::returnPos(void) override;
        strip *_strip;
        oled *_oled;
        menu *_menu;

};

#endif

