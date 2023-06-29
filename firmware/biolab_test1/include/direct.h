#ifndef DIRECT_H
#define DIRECT_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>

class direct: public _affector
{

    private:
    
    public:

        direct(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr);

        void direct::captureData(void) override;
        void direct::updateGame(void) override;
        int direct::returnVal(void) override;
        
        _device *direct_main_ptr;
        strip *direct_strip_ptr;
        oled *direct_oled_ptr;
        menu *direct_menu_ptr;
        int8_t portNum = -1; //used to save the port number that this object is instantiated on.
        
        int8_t direct_pin1;
        int8_t direct_pin2;

        int distance;

        bool prevAVal;
        bool prevBVal;
        bool pinAVal;
        bool pinBVal;

};

#endif

