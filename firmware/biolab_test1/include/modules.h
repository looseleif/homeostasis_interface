#ifndef MODULES_H
#define MODULES_H

#include <stdint.h>

//pin association
#define D1_A 1 //PB1
#define D1_B 0 //PB0
#define D2_A 31 //PA7
#define D2_B 30 //PA6
#define D3_A 18 //PC2
#define D3_B 19 //PC3

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

    uint8_t D1_mode = 0;
    uint8_t D2_mode = 0;
    uint8_t D3_mode = 0;
    
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
    virtual void captureData(void);
    virtual void updateGame(int x);
    virtual int8_t returnVal(void);
};


#endif