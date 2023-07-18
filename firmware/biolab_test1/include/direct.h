#ifndef DIRECT_H
#define DIRECT_H

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
    
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        
        int8_t direct_pin1;
        int8_t direct_pin2;

        bool prevAVal;
        bool prevBVal;
        bool pinAVal;
        bool pinBVal;

        int8_t quadratureLookupTable[16] = {0,0,0,-1,0,0,1,0,0,1,0,0,-1,0,0,0};
        float overallRate = 0;
        float movingAverage = 0; //holds the moving average for the production of the hand crank. 
        int8_t crankSum = 0; //sums the number of valid pulses from the encoder
        int8_t encoderPinA = -1; //stores object pin configuration
        int8_t encoderPinB = -1; //stores object pin configuration
        uint8_t pos = 0;
        int8_t direction = 0;

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

