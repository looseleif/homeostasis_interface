#ifndef SENSE_H
#define SENSE_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>


#include <NewPing.h>

class sense: public _affector
{

    private:
    
    public:

        sense(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr);

        void calculateRate(int8_t mod);

        _device *sense_main_ptr;
        strip *sense_strip_ptr;
        oled *sense_oled_ptr;
        menu *sense_menu_ptr;
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        
        int8_t trigPin;
        int8_t echoPin;

        float distance;
        
        NewPing *sense_sensor;

        bool prevAVal;
        bool prevBVal;
        bool pinAVal;
        bool pinBVal;

};

#endif