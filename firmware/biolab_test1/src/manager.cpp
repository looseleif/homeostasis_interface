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
                        // _oled->printMemoryText
                        patTurn = userTurn;
                        break;
                    case userTurn:
                        // dont need
                        break;
                    case postUserTurn:
                        // print nice job!
                        gameCount = 0;
                        gameTimeTotal+= 15; //vulnerable
                        patternPoints.add(rand()%30);
                        patternIndex = 0;
                        patternUserIndex = 0;
                        patTurn = cpuTurn;
                        break;
                    default:
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
            if(patTurn==userTurn){
                if((pos+30)>=(patternPoints.get(patternUserIndex)+30)-width && (pos+30)<=(patternPoints.get(patternUserIndex)+30)+width){
                    patternTime++;
                    if(patternTime>=10){
                        patternUserIndex++;
                        patternTime = 0;
                    }
                } else if (patternUserIndex==patternPoints.size()){
                    // round complete!
                    patTurn = postUserTurn;
                }
            }
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
                    if(poin!=poip){
                        for(int i=poin; i<=poip; i++){
                            _strip->leds[i%30] = CRGB(30,30,30);
                        }
                    }
                    break;
                case userTurn:
                    for(int i = patternUserIndex; i<patternPoints.size(); i++){
                        for(int j=patternPoints.get(i)-width; j<=patternPoints.get(i)+width; j++){
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
    patternIndex = 0;
    patternUserIndex= 0;
    score = 0;
    speed = 1;
    direction = 1;
    patTurn = cpuTurn;
    delay(1500);
}