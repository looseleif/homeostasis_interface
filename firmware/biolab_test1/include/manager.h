#ifndef MANAGER_H
#define MANAGER_H

#include <Arduino.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>
#include <math.h>

class manager: public _device
{

    private:

    public:

      manager(_device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr);
      
      void manager::updateObjective(void);
      void manager::checkInside(uint8_t pos);
      void manager::plotObjective(void);
      void manager::plotAffector(uint8_t pos, int dev);
      void manager::endGame(void);

      _device *manager_main_ptr;
      strip *manager_strip_ptr;
      oled *manager_oled_ptr;
      menu *manager_menu_ptr;

      uint8_t poi;
      uint8_t poin;
      uint8_t poip;
      
      uint8_t width;

      uint8_t entered = 0;
      uint8_t exists = 1;

      uint8_t score = 0;

};

#endif