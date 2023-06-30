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
    
    public:

        direct(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr);

        void direct::captureData(void) override;
        void direct::updateGame(int x) override;
        int8_t direct::returnVal(void) override;
        
        _device *direct_main_ptr;
        strip *direct_strip_ptr;
        oled *direct_oled_ptr;
        menu *direct_menu_ptr;
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        
        int8_t direct_pin1;
        int8_t direct_pin2;

        bool prevAVal;
        bool prevBVal;
        bool pinAVal;
        bool pinBVal;

        // http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html
        int8_t quadratureLookupTable[16] = {0,0,0,-1,0,0,1,0,0,1,0,0,-1,0,0,0};
        float overallRate = 0;
        float movingAverage = 0; //holds the moving average for the production of the hand crank. 
        uint8_t movingAveragePeriod = 1000/STRIPREFRESHDELAY; 
        uint8_t maxProductionRate = 60; //used in the rate calculation
        uint8_t consumptionRate = 70; ///used in the rate calculation
        int8_t crankSum = 0; //sums the number of valid pulses from the encoder
        int8_t encoderPinA = -1; //stores object pin configuration
        int8_t encoderPinB = -1; //stores object pin configuration

};

#endif

