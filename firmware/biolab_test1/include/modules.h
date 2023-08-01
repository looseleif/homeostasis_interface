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
#define conduct_TYPE 0
#define direct_TYPE 1
#define fixate_TYPE 2
#define menu_TYPE 5
#define oled_TYPE 6
#define strip_TYPE 7
#define manager_TYPE 8

enum AFFECTOR : uint8_t {
  conduct_affector,
  direct_affector,
  fixate_affector
};

class _device {
  
  private:

  public:
    
    _device(){};

    void createObject(int objtype, int portnum);
    
    virtual ~_device(){} // must have a virtualized destructor

    //these virtual functions will be overwritten by derived class objects. 
    virtual void calculateRate(int8_t modifier){}

};

class _affector: public _device
{
  public: 

    AFFECTOR current_affector;

    virtual ~_affector(){} //must have a virtualized destructor
    virtual void captureData(void);
    virtual void updateGame(int x);
    virtual int8_t returnVal(void);
    virtual uint8_t returnPos(void);
};


#endif