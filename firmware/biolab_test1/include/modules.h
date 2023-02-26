#ifndef MODULES_H
#define MODULES_H

#include <stdint.h>

//pin association
#define D1_pin1 3 //PB2
#define D1_pin2 4 //PB3
#define D2_pin1 8 //PD0
#define D2_pin2 9 //PD1
#define D3_pin1 22 //PC6
#define D3_pin2 23 //PC7
#define A1_pin1 24 //PA0
#define A1_pin2 25 //PA1
#define A2_pin1 26 //PA2
#define A2_pin2 27 //PA3
#define A3_pin1 28 //PA4
#define A3_pin2 29 //PA5

//device types
#define grip_TYPE 0
#define direct_TYPE 1
#define sense_TYPE 2
#define speak_TYPE 3
#define hold_TYPE 4
#define menu_TYPE 5
#define oled_TYPE 6
#define strip_TYPE 7
#define debug_TYPE 8


class _device {
  
  private:

  public:

    uint8_t DCON1_mode = 0;
    uint8_t ACON1_mode = 0;
    uint8_t DACON1_mode = 0;
    uint8_t DCON2_mode = 0;
    uint8_t ACON2_mode = 0;
    uint8_t DACON2_mode = 0;
    
    _device(){};

    void createObject(int objtype, int portnum);
    
    virtual ~_device(){} // must have a virtualized destructor

    //these virtual functions will be overwritten by derived class objects. 
    virtual void calculateRate(int8_t modifier){}

};

class _affector: public _device
{
  public: 
    virtual ~_affector(){} //must have a virtualized destructor
};


#endif