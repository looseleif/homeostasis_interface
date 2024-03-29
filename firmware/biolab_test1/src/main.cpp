#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <modules.h>
#include <menu.h>
#include <oled.h>
#include <strip.h>
#include <sense.h>
#include <direct.h>
#include <fixate.h>
#include <manager.h>
#include <avr/interrupt.h>
#include <avr/io.h>

menu *_menu;
manager *_manager;
oled *_oled;
strip *_strip;

_affector *D1_ptr = NULL;
_affector *D2_ptr = NULL;
_affector *D3_ptr = NULL;
int8_t D_index = 0;
_affector *D_set[3] = {D1_ptr,D2_ptr,D3_ptr};

void createObject(int objtype)
{

  switch (objtype) {

    case menu_TYPE:
      _menu = new menu();
      break;
    case oled_TYPE:
      _oled = new oled(_menu);
      break;
    case strip_TYPE:
      _strip = new strip(_menu);
      break;
    // case sense_TYPE:
    //   D_set[D_index] = new sense(D_index,_menu,_oled,_strip);
    //   D_set[D_index]->current_affector = sense_affector;
    //   D_index++;
    //   break;
    case direct_TYPE:
      D_set[D_index] = new direct(D_index,_menu,_oled,_strip);
      D_set[D_index]->current_affector = direct_affector;
      D_index++;
      break;
    case fixate_TYPE:
      D_set[D_index] = new fixate(D_index,_menu,_oled,_strip);
      D_set[D_index]->current_affector = fixate_affector;
      D_index++;
      break;
    case manager_TYPE:
      _manager = new manager(_menu,_oled,_strip);
      break;
      
  }

}

void deleteObject(int objtype)
{

  for(int i = 0; i<D_index; i++){
    delete D_set[i];
  }

  D1_ptr = NULL;
  D2_ptr = NULL;
  D3_ptr = NULL;

}

// MENU & GAME UPDATE
ISR (TIMER1_COMPA_vect)
{

  PORTD ^= (1 << PD5);
  PORTD ^= (1 << PD6);

  //_menu->cursor_prev = _menu->cursor_current;
  
  if(!digitalRead(HOME_PIN)){
    _menu->printed = false;
    _menu->system_state = game;
    _menu->demo_state = stopped;
    _menu->home_state = true;

  } else if(_menu->system_state==running){
  } else if(!digitalRead(UP_PIN)){

    _menu->selection = 1;

  } else if(!digitalRead(LEFT_PIN)){

    _menu->selection = 2;

  }else if(!digitalRead(RIGHT_PIN)){

    _menu->selection = 3;

  } else if(!digitalRead(DOWN_PIN)){

    _menu->selection = 4;

  }
  if(_menu->system_state==running){

    _manager->gameCount++;

    if(_manager->gameCount==_manager->gameTimeTotal){

      _manager->gameCount = 0;
      _manager->gameFlag = 1;

    }

  }

}

// DEVICE & SWITCH UPDATE
ISR (TIMER2_COMPA_vect)
{

  _manager->refreshCount++;

  if(_manager->refreshCount==25){

    _manager->switchCount++;
    _manager->patternCount++;
    _manager->refreshFlag = 1;
    _manager->refreshCount = 0;

  }

  if(_manager->switchCount==25+(rand()%55)){

    _manager->switchFlag = 1;
    _manager->switchCount = 0;

  }

  if(_manager->patternCount==50&&_manager->game_selected==memory){

    _manager->patternFlag = 1;
    _manager->patternCount = 0;

  }

}

// port pin change for direct affector
ISR (PCINT0_vect)
{

  PCIFR ^= (1 << PCIF0);
  _manager->crankFlag = 1;

}

ISR (PCINT1_vect)
{

  PCIFR ^= (1 << PCIF0);
  _manager->crankFlag = 1;

}

ISR (PCINT2_vect)
{

  PCIFR ^= (1 << PCIF0);
  _manager->crankFlag = 1;

}

void bootSequence(void){

  _strip->setColor(0,0,0);
  _strip->setIntensity(0);
  _oled->clear();
  _oled->bootingPrint();
  _delay_ms(300);
  _oled->clear();
  _strip->lubDub();
  _delay_ms(100);
  _strip->sweepColor(111,0,0,10);
  _strip->setColor(0,0,0);
  _oled->clear();
  _oled->pleaseWaitPrint();
  _delay_ms(500);
  _oled->clear();

}

// SETUP TIMERS + INTERRUPTS + OBJECTS
void setup()   {

  // DEBUG LEDS
  DDRD |= (1 << PD5);
  PORTD ^= (1 << PD5);
  PORTD ^= (1 << PD5);
  DDRD |= (1 << PD6);
  PORTD ^= (1 << PD6); 

  cli();

  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
  OCR1A = 2500; // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set CS10 and CS12 bits for prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0; // initialize counter value to 0
  OCR2A = 255; // must be < 256
  TCCR2A |= (1 << WGM21); // turn on CTC mode
  TCCR2B |= (1 << CS22);  // set prescaler
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt

  randomSeed(analogRead(0));

  createObject(menu_TYPE);
  createObject(oled_TYPE);
  createObject(strip_TYPE);
  createObject(manager_TYPE);

  bootSequence();

  sei();

}

int main(){
  
  init();
  setup();

  while(true){
    
    // MENU STATE MACHINE
    
    if(_menu->system_state==game){
      
      deleteObject(0);

      D_index = 0;

      if(_menu->home_state){

        cli();
        TCNT1  = 2250;
        sei();
        _oled->clear();
        _strip->inverseSweep(10);
        _oled->goingHomePrint();
        _delay_ms(500);
        _oled->clear();
        _strip->sweepColor(100,0,0,10);
        _delay_ms(50);
        _strip->setColor(100,0,0);
        _strip->setIntensity(50);
        _menu->home_state = false;
        _menu->selected_demo = 0;
        _menu->selected_port = 0;
        _menu->selection = 0;
        _manager->gameTimeTotal = 45;
        _manager->direction = 1;
        _manager->refreshFlag = 0;
        _manager->refreshCount = 0;
        _manager->crankFlag = 0;
        _manager->switchFlag = 0;
        _manager->switchCount = 0;
        _manager->patternFlag = 0;
        _manager->patternCount = 0;
        _manager->gameFlag = 0;
        _manager->gameCount = 0;
        _manager->scoreFlag = 0;
        _manager->score = 0;
        _manager->width = 1;
        _manager->speed = 1;
        _manager->mod = 0;

      }

      if(!(_menu->printed)){

        _oled->clear();
        _strip->setColor(100,0,0);
        _strip->setIntensity(50);
        _menu->system_state = game;
        _oled->printGameMenu();
        _menu->selection = 0;
        _menu->printed = true;

      }

      // ZONE || MEMORY || CHASE || N/A
      if(_menu->selection == 1 || _menu->selection == 2 || _menu->selection == 3){

        _manager->game_selected = _menu->selection;
        _menu->system_state = affector;
        _menu->printed = false;
        _oled->clear();
        _oled->pleaseWaitPrint();
        _delay_ms(250);
        _oled->clear();
        _delay_ms(500);
        _strip->setColor(100,10,0);
        _strip->setIntensity(50);
        _menu->selection = 0;
        _delay_ms(500);

      }

    }

    if(_menu->system_state==affector){

      if(!(_menu->printed)){

        _oled->clear();
        _oled->printAffectorMenu();
        _menu->printed = true;

      }

      // N/A || DIRECT || FIXATE || N/A
      if(_menu->selection == 2 || _menu->selection == 3){

        _menu->selected_demo = _menu->selection;
        _menu->system_state = port;
        _menu->printed = false;
        _oled->clear();
        _oled->pleaseWaitPrint();
        _delay_ms(500);
        _oled->clear();
        _strip->setColor(100,30,0);
        _strip->setIntensity(50);
        _delay_ms(500);
        _menu->selection = 0;

      }

    }

    if(_menu->system_state==port){

      if(!(_menu->printed)){

        _oled->clear();
        _oled->printPortMenu();
        _menu->printed = true;

      }

      // MID || LEFT || RIGHT || N/A
      if(_menu->selection == 1 || _menu->selection == 2 || _menu->selection == 3){

        _menu->selected_port = _menu->selection;
        _menu->printed = false;
        createObject(_menu->selected_demo);
        _oled->clear();
        _strip->setColor(50,50,50);
        _strip->setIntensity(50);
        _delay_ms(50);
        _oled->pleaseWaitPrint();
        _menu->system_state = addition;
        _menu->selection = 0;

      }

    }

    if(_menu->system_state==addition){

      if(!(_menu->printed)){

        _oled->clear();
        _oled->printAdditionMenu();
        _menu->printed = true;

      }

      if(_menu->selection){
        
        _oled->clear();
        _menu->printed = false;
        
        //LEFT BUTTON (YES)
        if(_menu->selection == 2){

          _menu->system_state = affector;
          _menu->printed = false;
          _oled->clear();
          _oled->pleaseWaitPrint();
          _delay_ms(100);
          _oled->clear();
          _strip->setColor(100,30,0);
          _strip->setIntensity(50);
          _menu->selection = 0;
          _delay_ms(50);

        // RIGHT BUTTON (NO)
        } else if(_menu->selection == 3) {

          _menu->system_state = running;
          _menu->demo_state = started;
          _strip->setColor(50,50,50);
          _strip->setIntensity(50);
          _delay_ms(100);

          _oled->clear();

          _oled->playingInfo(_manager->game_selected);
          _delay_ms(1000);
          _oled->clear();
          _strip->inverseSweep(10);

          switch (_manager->game_selected){

            case (zone):
              OCR2A = 255;
              break;
            case (memory):
              OCR2A = 255;
              break;
            case (chase):
              OCR2A = 25;
              break;        
            default:
              break;

          }

        }

      }

    }

    if(_menu->system_state==running){

      if(_manager->crankFlag){

        for(int i = 0; i<D_index; i++){

          if(D_set[i]->current_affector==direct_affector){
            D_set[i]->updateGame(1);
            _manager->crankFlag = 0;
          }

        }

      }

      if(_manager->refreshFlag){

        _strip->setColor(0,0,0);
        _manager->plotObjective();

        for(int i = 0; i<D_index; i++){

          D_set[i]->updateGame(0);
          D_set[i]->captureData();
          _manager->plotAffector(D_set[i]->returnPos(), i);
          _manager->checkInside(D_set[i]->returnPos());

        }

        _strip->setIntensity(50);
        _manager->refreshFlag = 0;

      }

      if(_manager->switchFlag){

        _manager->updateObjective();

        if(_manager->scoreFlag){
          
          _manager->score++;

          if(_manager->game_selected==chase){

            if(_manager->score%10==0){

              _manager->direction*=-1;
              _manager->speed++;

            }

            if(_manager->score%35==0){
              _manager->width=1;
            } else if(_manager->score%50==0){
              _manager->width=0;
            }

          }

        }

        _manager->scoreFlag = 0;
        _manager->switchFlag = 0;

      }

      if(_manager->gameFlag){

        _manager->gameFlag = 0;
        _manager->endGame();
        _menu->system_state = again;
        _strip->sweepColor(100,0,0,10);

      }

    }

    if(_menu->system_state==again){

      if(!(_menu->printed)){

        _strip->setColor(100,0,0);
        _strip->setIntensity(50);
        _oled->clear();
        _oled->printAgainMenu();
        _menu->selection = 0;
        _menu->printed = true;

      }

      if(_menu->selection){

        _menu->printed = false;
        _oled->clear();

        // RIGHT BUTTON (NO)
        if((_menu->selection == 3)){

          _oled->clear();
          _strip->inverseSweep(10);
          _oled->resetPrint();
          delay(250);
          _oled->clear();
          _menu->system_state = game;
          _menu->selection = 0;
          _menu->printed = false;
          _delay_ms(500);
          _strip->sweepColor(100,0,0,10);

        // LEFT BUTTON (YES)
        } else if(_menu->selection == 2) {

          _oled->clear();

          cli();

          switch (_manager->game_selected){

            case (zone):
              OCR2A = 255;
              break;
            case (memory):
              OCR2A = 255;
              break;
            case (chase):
              OCR2A = 25;
              break;        
            default:
              break;

          }

          sei();

          _menu->system_state = running;
          _menu->demo_state = started;
          _strip->setColor(20,20,20);
          _strip->setIntensity(50);
          _delay_ms(50);

        }

      }

    }  

  }

  return 0;

}