#include <manager.h>>

manager::manager(menu *menuptr, oled *oledptr, strip *stripptr){

  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;

  // max width 3
  width = 2;

}

void manager::updateObjective(void){

    switch(game_selected){
        case(zone):
            poi = 30+(rand()%30);
            poin = (poi-width);
            poip = (poi+width);
            exists = 1;
            entered = 0;
            break;
        case(memory):
            break;
        case(chase):
            break;
    }


}

void manager::checkInside(uint8_t pos){

    if((pos>=poin && pos<=poip) && entered){

        scoreFlag = 1;
        entered = 0;
        exists = 0;

    }

    if((pos>=poin && pos<=poip) && !entered){

        entered = 1;

    }

}

void manager::plotObjective(void){

    if(exists){
    
        if(entered){
            
            for(int i=poin; i<=poip; i++){
                _strip->leds[i%30] = CRGB(100,100,100);
            }

        } else {

            for(int i=poin; i<=poip; i++){
                _strip->leds[i%30] = CRGB(100,0,0);
            }

        }
    
    }

}

void manager::plotAffector(uint8_t pos, int dev){

    switch(dev){
        case 0: _strip->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
        case 1: _strip->leds[pos%NUM_LEDS] = CRGB(50,50,0); break;
        case 2: _strip->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
    }

}

void manager::endGame(void){

    _oled->clearAll();
    delay(500);
    _oled->printGameOver();
    _oled->clearAll();
    delay(500);
    
    if(score>5){
        _oled->printWin();
    }else{
        _oled->printLose(); 
    }

    score = 0;
    delay(1500);

}