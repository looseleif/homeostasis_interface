#ifndef MENU_H
#define MENU_H

#include <modules.h>
#include <Arduino.h>

#define UP_PIN 10 //PD2
#define DOWN_PIN 11 //PD3
#define LEFT_PIN 12 //PD4
#define RIGHT_PIN 13 //PD5
#define SELECT_PIN 14 //PD6
#define HOME_PIN 15 // PD7

#define GRIP_DEMO 0
#define DIRECT_DEMO 1
#define SENSE_DEMO 2
#define SPEAK_DEMO 3
#define HOLD_DEMO 4
#define DEBUG_DEMO 5

#define D1_DEVICE 0
#define D2_DEVICE 1
#define D3_DEVICE 2
#define A1_DEVICE 3
#define A2_DEVICE 4
#define A3_DEVICE 5

enum DEMO : uint8_t {
  stopped,
  started,
  lost
};

enum SYSTEM : uint8_t {
  welcome,
  demo,
  device,
  running,
  debug
};

class menu: public _device 
{

    private:

    public:

        menu(void);

        SYSTEM system_state;
        DEMO demo_state;
        bool home_state;
        bool printed;
        int8_t cursor_prev;
        int8_t cursor_current;
        int8_t selected_demo;
        int8_t selected_device;



};

#endif