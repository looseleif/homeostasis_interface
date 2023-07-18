#include <manager.h>>

manager::manager(menu *menuptr, oled *oledptr, strip *stripptr){

  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;

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

        scoreFlag = 1;
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
            
            _strip->leds[poi] = CRGB(100,100,100);
            _strip->leds[poin] = CRGB(100,100,100);
            _strip->leds[poip] = CRGB(100,100,100);

        } else {

            _strip->leds[poi] = CRGB(100,0,0);
            _strip->leds[poin] = CRGB(100,0,0);
            _strip->leds[poip] = CRGB(100,0,0);

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