#include <manager.h>

manager::manager(menu *menuptr, oled *oledptr, strip *stripptr){

    _menu = menuptr;
    _oled = oledptr;
    _strip = stripptr;

    gameTimeTotal = 45;

    direction = 1;

    refreshFlag = 0;
    refreshCount = 0;

    crankFlag = 0;
    
    switchFlag = 0;
    switchCount = 0;

    patternFlag = 0;
    patternCount = 0;

    gameFlag = 0;
    gameCount = 0;
    
    scoreFlag = 0;
    score = 0;

    width = 1;
    speed = 1;
    mod = 0;

    patternPoints.add(rand()%NUM_LEDS);

}

void manager::updateObjective(void){
    
    switch(game_selected){

        case(zone):
            poi = NUM_LEDS+(rand()%NUM_LEDS);
            poin = (poi-width);
            poip = (poi+width);
            exists = 1;
            entered = 0;
            break;
        case(memory):
            if(patternFlag){
                if(patTurn==cpuTurn&&patternPoints.size()==1){
                    _oled->clearAll();
                    _oled->_screen->drawBitmap(10,10, cpu, 100, 100, WHITE);
                    _oled->_screen->display();
                }
                if(patTurn==cpuTurn&&((int)patternIndex==patternPoints.size())){
                    patTurn = preUserTurn;
                } else if(patTurn==preUserTurn){
                    patTurn = userTurn;
                } else if(patTurn==userTurn&&((int)patternIndex==patternPoints.size())){
                    patTurn = postUserTurn;
                }

                switch (patTurn){
                    
                    case cpuTurn:
                        poi = NUM_LEDS+patternPoints.get(patternIndex);
                        poin = (poi-width);
                        poip = (poi+width);
                        patternIndex++;
                        break;
                    case preUserTurn:
                        poin = 0;
                        poip = 0;
                        patternIndex = 0;
                        _strip->setColor(0,0,0);
                        _oled->clearAll();
                        _oled->_screen->drawBitmap(10,10, user, 100, 100, WHITE);
                        _oled->_screen->display();
                        patTurn = userTurn;
                        break;
                    case userTurn:
                        break;
                    case postUserTurn:
                        _oled->clearAll();
                        _oled->_screen->drawBitmap(10,10, nice, 100, 100, WHITE);
                        _oled->_screen->display();
                        _delay_ms(100);
                        _oled->clearAll();
                        gameCount = 0;
                        gameTimeTotal+= 3;
                        patternPoints.add(rand()%NUM_LEDS);
                        patternIndex = 0;
                        patternUserIndex = 0;
                        patTurn = cpuTurn;
                        _oled->clearAll();
                        _oled->_screen->drawBitmap(10,10, cpu, 100, 100, WHITE);
                        _oled->_screen->display();
                        break;

                }

            }

            break;
        case(chase):
            poi = NUM_LEDS+(((poi+(direction*speed))%NUM_LEDS));
            poin = (poi-width);
            poip = (poi+width);
            break;

    }

}

void manager::checkInside(uint8_t pos){

    switch(game_selected){

        case(zone):
            if(((pos+NUM_LEDS>=poin && pos+NUM_LEDS<=poip)||(poi%NUM_LEDS==0 && pos>=NUM_LEDS-width)||(poi%NUM_LEDS==(NUM_LEDS-1) && pos<=width)) && entered){
                scoreFlag = 1;
                entered = 0;
                exists = 0;
            }
            
            if(((pos+NUM_LEDS>=poin && pos+NUM_LEDS<=poip)||(poi%NUM_LEDS==0 && pos>=NUM_LEDS-width)||(poi%NUM_LEDS==(NUM_LEDS-1) && pos<=width)) && !entered){
                entered = 1;
            }

            break;
        case(memory):
            pointOfInterest = patternPoints.get(patternUserIndex);
            
            if(patTurn==userTurn){
                if(pointOfInterest==0 && pos>=NUM_LEDS-width){
                    patternTime++;
                } else if(pointOfInterest==29 && pos<=width){
                    patternTime++;
                } else if((pos+NUM_LEDS)>=(patternPoints.get(patternUserIndex)+NUM_LEDS)-width && (pos+NUM_LEDS)<=(patternPoints.get(patternUserIndex)+NUM_LEDS)+width){
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
            if((pos+NUM_LEDS>=poin && pos+NUM_LEDS<=poip)||(poi%NUM_LEDS==0 && pos>=NUM_LEDS-width)||(poi%NUM_LEDS==29 && pos<=width)){
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
                        _strip->leds[i%NUM_LEDS] = CRGB(100,100,100);
                    }
                } else {
                    for(int i=poin; i<=poip; i++){
                        _strip->leds[i%NUM_LEDS] = CRGB(100,0,0);
                    }
                }

            }
            break;
        case(memory):
            
            switch (patTurn){
                
                case cpuTurn:
                    if(poin!=poip){
                        
                        for(int i=poin; i<=poip; i++){
                            _strip->leds[i%NUM_LEDS] = CRGB(30,30,30);
                        }

                    }
                    break;
                case userTurn:
                    for(int i = patternUserIndex; i<patternPoints.size(); i++){
                        
                        for(int j=(patternPoints.get(i)+NUM_LEDS)-width; j<=(patternPoints.get(i)+NUM_LEDS)+width; j++){
                            _strip->leds[j%NUM_LEDS] = CRGB(30,30,30);
                        }

                    }
                    break;
                default:
                    break;
                }
            break;
        case(chase):
            for(int i=poin; i<=poip; i++){
                _strip->leds[i%NUM_LEDS] = CRGB(100,0,0);
            }
            break;
    }

}

void manager::plotAffector(uint8_t pos, int dev){
    
    if(patTurn!=cpuTurn || game_selected!=memory){
        
        switch(dev){
            
            case 0: _strip->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;
            case 1: _strip->leds[pos%NUM_LEDS] = CRGB(50,50,0); break;
            case 2: _strip->leds[pos%NUM_LEDS] = CRGB(0,50,50); break;

        }

    }

}

void manager::endGame(void){
    
    _oled->clearAll();

    cli();

    OCR2A = 255;

    sei();

    if(score>17 && game_selected!=chase)
        score=17;

    switch (game_selected){

        case (zone):
            _oled->printNumber(score);
            _delay_ms(500);
            _oled->clearAll();

            if(score>5)
                _oled->printWin();

            break;
        case (memory):
            _oled->printNumber(score);
            _delay_ms(500);
            _oled->clearAll();

            if(score>5)
                _oled->printWin();

            break;
        case (chase):
            _oled->printNumber(score/10);
            _delay_ms(500);
            _oled->clearAll();
            
            if(score>30)
                _oled->printWin();

            break;        
        default:
            break; 
    }

    patternPoints.clear();
    patternIndex = 0;
    patternUserIndex= 0;

    score = 0;
    speed = 1;
    direction = 1;
    width = 1;

    patTurn = cpuTurn;
    patternPoints.add(rand()%NUM_LEDS);

    _delay_ms(500);

}