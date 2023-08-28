#ifndef MENU_H
#define MENU_H

/*
*
* This is the class for the menu, it is what controls the setup flow when
* first starting the device. Most of all information held in the menu
* class is displayed through the OLED display. The implementation is
* basically a state machine that is usually linear, but we allow for 
* additional affectors which returns the affector selection page, as well as after completing a game, which will reset
* the user to the game selection page.
*
*/

#include <modules.h>
#include <Arduino.h>

#define UP_PIN 10 //PD2
#define DOWN_PIN 9 //PD1
#define LEFT_PIN 8 //PD0
#define RIGHT_PIN 11 //PD3
#define SELECT_PIN 29 //PA5
#define HOME_PIN 12 // PD4
#define GRIP_DEMO 0
#define DIRECT_DEMO 1
#define FIXATE_DEMO 2
#define SPEAK_DEMO 3
#define HOLD_DEMO 4
#define DEBUG_DEMO 5
#define D1_DEVICE 0
#define D2_DEVICE 1
#define D3_DEVICE 2

enum DEMO : uint8_t {
  stopped,
  started,
  lost
};

enum SYSTEM : uint8_t {
  game,
  affector,
  port,
  addition,
  running,
  again
};

class menu: public _device 
{

    public:

        menu(void);
        SYSTEM system_state;
        DEMO demo_state;
        bool home_state;
        bool printed;
        int8_t cursor_prev, cursor_current, cursor_max;
        int8_t selected_demo, selected_port;

};

#endif