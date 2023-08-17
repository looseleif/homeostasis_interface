#include <manager.h>

manager::manager(menu *menuptr, oled *oledptr, strip *stripptr){
  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;
  width = 2;
  patternPoints.add(5);
  patternPoints.add(10);
  patternPoints.add(15);
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
            if(patternFlag){
                switch (patTurn){
                    case cpuTurn:
                        poi = 30+patternPoints.get(patternIndex);
                        poin = (poi-width);
                        poip = (poi+width);
                        patternIndex++;
                        break;
                    default:
                        break;
                    }
                    break;
            }
            break;
        case(chase):
            poi = 30+(((poi+(direction*speed))%30));
            poin = (poi-width);
            poip = (poi+width);
            break;
    }
}

void manager::checkInside(uint8_t pos){
    switch(game_selected){
        case(zone):
            if((pos+30>=poin && pos+30<=poip) && entered){
                scoreFlag = 1;
                entered = 0;
                exists = 0;
            }
            if((pos+30>=poin && pos+30<=poip) && !entered){
                entered = 1;
            }
            break;
        case(memory):
            break;
        case(chase):
            if((pos+30>=poin && pos+30<=poip) && entered){
                scoreFlag = 1;
                entered = 0;
                exists = 0;
            }
            if((pos+30>=poin && pos+30<=poip)){
                scoreFlag = 1;
            }
            break;
    }
}

void manager::plotObjective(void){
    switch(game_selected){
        case(zone):
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
            break;
        case(memory):
            switch (patTurn){
                case cpuTurn:
                    for(int i=poin; i<=poip; i++){
                        _strip->leds[i%30] = CRGB(30,30,30);
                    }
                    break;
                default:
                    break;
                }
                break;
        case(chase):
            for(int i=poin; i<=poip; i++){
                _strip->leds[i%30] = CRGB(100,0,0);
            }
            break;
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
    cli();
    OCR2A = 255;
    sei();
    _oled->printGameOver();
    _oled->clearAll();
    delay(500);
    switch (game_selected){
        case (zone):
            if(score>5)
                _oled->printWin();
            break;
        case (memory):
            if(score>5)
                _oled->printWin();
            break;
        case (chase):
            if(score>50)
                _oled->printWin();
            break;        
        default:
            break; 
    }
    score = 0;
    speed = 1;
    width = 2;
    direction = 1;
    delay(1500);
}