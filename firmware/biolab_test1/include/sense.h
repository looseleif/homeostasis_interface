#ifndef SENSE_H
#define SENSE_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>


#include <NewPing.h>
#include <HCSR04.h>

class sense: public _affector
{

    private:
    
        strip *_strip;
        oled *_oled;
        menu *_menu;
        
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        
        int8_t trigPin;
        int8_t echoPin;

        uint8_t pos;

        UltraSonicDistanceSensor *sense_ultra;

        bool prevAVal;
        bool prevBVal;
        bool pinAVal;
        bool pinBVal;    

    public:

        sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);

        void sense::captureData(void) override;
        void sense::updateGame(int x) override;
        int8_t sense::returnVal(void) override;
        uint8_t sense::returnPos(void) override;

};

#endif