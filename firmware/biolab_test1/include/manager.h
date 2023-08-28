#ifndef MANAGER_H
#define MANAGER_H

/*
*
* This is the manager class used as the game manager for this device. This
* is where affector and game specific features are stored (direction for the direct
* affector, speed for the chase game) With use of a variety of state variables, the
* games are able to be treated very similar at the low level, this will hopefully
* benefit future developers to extend the game options!
*
*/

#include <Arduino.h>
#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>
#include <LinkedList.h>

enum GAME : uint8_t {
  zone,
  memory,
  chase
};

enum TURN : uint8_t {
  cpuTurn,
  preUserTurn,
  userTurn,
  postUserTurn
};

class manager: public _device
{

    private:

      LinkedList<int> patternPoints;
      uint8_t patternIndex = 0;
      uint8_t patternUserIndex = 0;
      uint8_t patternTime = 0;
      uint8_t poi;
      uint8_t poin;
      uint8_t poip;
      uint8_t pointOfInterest;
      uint8_t entered = 0;
      uint8_t exists = 1;
      TURN patTurn;

    public:

      manager(menu *menuptr, oled *oledptr, strip *stripptr);
      void manager::updateObjective(void);
      void manager::checkInside(uint8_t pos);
      void manager::plotObjective(void);
      void manager::plotAffector(uint8_t pos, int dev);
      void manager::endGame(void);
      strip *_strip;
      oled *_oled;
      menu *_menu;
      uint8_t game_selected;
      uint8_t gameTimeTotal;
      int8_t direction;
      uint8_t refreshFlag, refreshCount, crankFlag;
      uint8_t switchFlag, switchCount;
      uint8_t patternFlag, patternCount;
      uint8_t gameFlag, gameCount;
      uint8_t scoreFlag, score;
      uint8_t width;
      uint8_t speed;
      uint8_t mod;
      
};

#endif