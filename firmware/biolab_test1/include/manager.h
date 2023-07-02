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
      
      void manager::createObjective(void);
      void manager::plotAffector(uint8_t pos, int dev);

      _device *manager_main_ptr;
      strip *manager_strip_ptr;
      oled *manager_oled_ptr;
      menu *manager_menu_ptr;

};

#endif