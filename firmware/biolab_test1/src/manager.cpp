#include <manager.h>

manager::manager(menu *menuptr, oled *oledptr, strip *stripptr){
  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;
  patternPoints.add(rand()%30);
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
                if(patTurn==cpuTurn&&((int)patternIndex==patternPoints.size())){
                    patTurn = preUserTurn;
                } else if(patTurn==preUserTurn){
                    patTurn = userTurn;
                } else if(patTurn==userTurn&&((int)patternIndex==patternPoints.size())){
                    patTurn = postUserTurn;
                }
                switch (patTurn){
                    case cpuTurn:
                        poi = 30+patternPoints.get(patternIndex);
                        poin = (poi-width);
                        poip = (poi+width);
                        patternIndex++;
                        break;
                    case preUserTurn:
                        poin = 0;
                        poip = 0;
                        patternIndex = 0;
                        _strip->setColor(0,0,0);
                        _oled->_screen->drawBitmap(10,10, unoCard, 100, 100, WHITE);
                        _oled->_screen->display();
                        patTurn = userTurn;
                        break;
                    case userTurn:
                        // dont need
                        break;
                    case postUserTurn:
                        _oled->clearAll();
                        _oled->_screen->drawBitmap(10,10, thumbsUp, 100, 100, WHITE);
                        _oled->_screen->display();
                        delay(300);
                        _oled->clearAll();
                        gameCount = 0;
                        gameTimeTotal+= 15; //vulnerable
                        patternPoints.add(rand()%30);
                        patternIndex = 0;
                        patternUserIndex = 0;
                        patTurn = cpuTurn;
                        break;
                }
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
            if(((pos+30>=poin && pos+30<=poip)||(poi%30==0 && pos>=30-width)||(poi%30==29 && pos<=width)) && entered){
                scoreFlag = 1;
                entered = 0;
                exists = 0;
            }
            if(((pos+30>=poin && pos+30<=poip)||(poi%30==0 && pos>=30-width)||(poi%30==29 && pos<=width)) && !entered){
                entered = 1;
            }
            break;
        case(memory):
            pointOfInterest = patternPoints.get(patternUserIndex);
            if(patTurn==userTurn){
                if(pointOfInterest==0 && pos>=30-width){
                    patternTime++;
                } else if(pointOfInterest==29 && pos<=width){
                    patternTime++;
                } else if((pos+30)>=(patternPoints.get(patternUserIndex)+30)-width && (pos+30)<=(patternPoints.get(patternUserIndex)+30)+width){
                    patternTime++;
                } 
                if(patternTime>=10){
                        patternUserIndex++;
                        patternTime = 0;
                }
                if (patternUserIndex==patternPoints.size()){
                    patTurn = postUserTurn;
                    scoreFlag = 1;
                }
            }
            break;
        case(chase):
            PORTD ^= (1 << PD6);
            if((pos+30>=poin && pos+30<=poip)||(poi%30==0 && pos>=30-width)||(poi%30==29 && pos<=width)){
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
                    if(poin!=poip){
                        for(int i=poin; i<=poip; i++){
                            _strip->leds[i%30] = CRGB(30,30,30);
                        }
                    }
                    break;
                case userTurn:
                    for(int i = patternUserIndex; i<patternPoints.size(); i++){
                        for(int j=(patternPoints.get(i)+30)-width; j<=(patternPoints.get(i)+30)+width; j++){
                            _strip->leds[j%30] = CRGB(30,30,30);
                        }
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
    delay(500);
    _oled->clearAll();
    delay(500);
    switch (game_selected){
        case (zone):
            _oled->printNumber(score);
            delay(500);
            _oled->clearAll();
            if(score>5)
                _oled->printWin();
            break;
        case (memory):
            _oled->printNumber(score);
            delay(500);
            _oled->clearAll();
            if(score>5)
                _oled->printWin();
            break;
        case (chase):
            _oled->printNumber(score/10);
            delay(500);
            _oled->clearAll();
            if(score>50)
                _oled->printWin();
            break;        
        default:
            break; 
    }
    patternIndex = 0;
    patternUserIndex= 0;
    score = 0;
    speed = 1;
    direction = 1;
    patTurn = cpuTurn;
    delay(1500);
}