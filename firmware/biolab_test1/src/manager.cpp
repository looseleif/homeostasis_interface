#include <manager.h>>

manager::manager(_device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  manager_main_ptr = mainptr;
  manager_menu_ptr = menuptr;
  manager_oled_ptr = oledptr;
  manager_strip_ptr = stripptr;

}

void manager::updateObjective(void){

    poi = 30+(rand()%30);
    poin = (poi-1)%30;
    poip = (poi+1)%30;
    poi = poi%30;
    exists = 1;
    entered = 0;

}

void manager::checkInside(uint8_t pos){

    if((pos==poi||pos==poin||pos==poip) && entered){

        entered = 0;
        exists = 0;

    }

    if((pos==poi||pos==poin||pos==poip) && !entered){

        entered = 1;

    }

}

void manager::plotObjective(void){

    if(exists){
    
        if(entered){
            
            manager_strip_ptr->leds[poi] = CRGB(100,100,100);
            manager_strip_ptr->leds[poin] = CRGB(100,100,100);
            manager_strip_ptr->leds[poip] = CRGB(100,100,100);

        } else {

            manager_strip_ptr->leds[poi] = CRGB(100,0,0);
            manager_strip_ptr->leds[poin] = CRGB(100,0,0);
            manager_strip_ptr->leds[poip] = CRGB(100,0,0);

        }
    
    }

}

void manager::plotAffector(uint8_t pos, int dev){

    switch(dev){
        case 0: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
        case 1: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(50,50,0); break;
        case 2: manager_strip_ptr->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
    }

}

void manager::endGame(void){

    manager_oled_ptr->printGameOver();


}