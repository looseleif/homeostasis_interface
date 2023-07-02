#include <manager.h>>

manager::manager(_device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  manager_main_ptr = mainptr;
  manager_menu_ptr = menuptr;
  manager_oled_ptr = oledptr;
  manager_strip_ptr = stripptr;

}

void manager::createObjective(void){

    uint8_t point = 30+(rand()%30);
    manager_strip_ptr->leds[point%30] = CRGB(100,0,0);
    manager_strip_ptr->leds[(point-1)%30] = CRGB(100,0,0);
    manager_strip_ptr->leds[(point+1)%30] = CRGB(100,0,0);

}

void manager::plotAffector(uint8_t pos, int dev){

    switch(dev){
        case 0: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
        case 1: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(50,50,0); break;
        case 2: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
    }

}