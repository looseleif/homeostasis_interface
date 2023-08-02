#ifndef MANAGER_H
#define MANAGER_H

#include <Arduino.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>

enum GAME : uint8_t {
  zone,
  memory,
  chase
};
class manager: public _device
{

    private:

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

      uint8_t refreshFlag = 0;
      uint8_t refreshCount = 0;
      uint8_t crankFlag = 0;
      uint8_t mod = 0;
      uint8_t switchFlag = 0;
      uint8_t switchCount = 0;
      uint8_t gameFlag = 0;
      uint8_t gameCount = 0;

      uint8_t poi;
      uint8_t poin;
      uint8_t poip;
      
      uint8_t width;

      uint8_t entered = 0;
      uint8_t exists = 1;

      uint8_t score = 0;
      uint8_t scoreFlag = 0;

};

#endif