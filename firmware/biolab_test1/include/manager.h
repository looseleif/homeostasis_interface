#ifndef MANAGER_H
#define MANAGER_H

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
      uint8_t gameTimeTotal = 45;
      uint8_t speed = 1;
      int8_t direction = 1;
      uint8_t refreshFlag = 0;
      uint8_t refreshCount = 0;
      uint8_t crankFlag = 0;
      uint8_t mod = 0;
      uint8_t switchFlag = 0;
      uint8_t switchCount = 0;
      uint8_t patternFlag = 0;
      uint8_t patternCount = 0;
      uint8_t patternIndex = 0;
      uint8_t patternUserIndex = 0;
      uint8_t patternTime = 0;
      uint8_t gameFlag = 0;
      uint8_t gameCount = 0;
      uint8_t poi;
      uint8_t poin;
      uint8_t poip;
      uint8_t pointOfInterest;
      uint8_t width = 1;
      uint8_t entered = 0;
      uint8_t exists = 1;
      uint8_t score = 0;
      uint8_t scoreFlag = 0;
      TURN patTurn;

};

#endif