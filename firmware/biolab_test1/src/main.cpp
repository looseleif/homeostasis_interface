#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <modules.h>
#include <menu.h>
#include <oled.h>
#include <strip.h>
#include <conduct.h>
#include <direct.h>
#include <sense.h>
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

int8_t cursor_max = 0;

void createObject(int objtype, int portnum)
{

  switch (objtype)
  {
  case menu_TYPE:
    _menu = new menu();
    break;
  case oled_TYPE:
    _oled = new oled(_menu);
    break;
  case strip_TYPE:
    _strip = new strip(_menu);
    break;
  case conduct_TYPE:
    D_set[D_index] = new conduct(D_index,_menu,_oled,_strip);
    D_set[D_index]->current_affector = direct_affector;
    D_index++;
    break;
  case direct_TYPE:
    D_set[D_index] = new direct(D_index,_menu,_oled,_strip);
    D_set[D_index]->current_affector = direct_affector;
    D_index++;
    break;
  case sense_TYPE:
    D_set[D_index] = new sense(D_index,_menu,_oled,_strip);
    D_set[D_index]->current_affector = sense_affector;
    D_index++;
    break;
  case manager_TYPE:
    _manager = new manager(_menu,_oled,_strip);
    break;
  }

}

void deleteObject(int objtype, int portnum)
{

  // implement destruction

}

// INTERRUPT SERVICE ROUTINES

// MENU & GAME UPDATE

ISR (TIMER1_COMPA_vect)
{

  PORTD ^= (1 << PD5);

  _menu->cursor_prev = _menu->cursor_current;

  if(!digitalRead(HOME_PIN)){

    _menu->printed = false;
    _menu->system_state = game;
    _menu->demo_state = stopped;
    _menu->home_state = true;

  } else if(_menu->system_state==running){

  } else if(!digitalRead(DOWN_PIN)){

    _menu->cursor_current++;
    _menu->cursor_current%=(cursor_max+1);
    _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);

  } else if(!digitalRead(UP_PIN)){

    if(_menu->cursor_current==0){

      _menu->cursor_current = cursor_max;

    } else {
    _menu->cursor_current--;
    }
    _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);

  }
  
  if(_menu->system_state==running){
    
    _manager->gameCount++;
    if(_manager->gameCount==45){

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

      PORTD ^= (1 << PD6);

      _manager->switchCount++;
      _manager->refreshFlag = 1;
      _manager->refreshCount = 0;

    }
    if(_manager->switchCount==25+(rand()%55)){
      _manager->switchFlag = 1;
      _manager->switchCount = 0;
    }

}

// PORT PIN CHANGE

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

// SETUP TIMERS + INTERRUPTS + OBJECTS

void setup()   {

  // DEBUG LEDS

  DDRD |= (1 << PD5);
  PORTD ^= (1 << PD5);
  DDRD |= (1 << PD6);
  PORTD ^= (1 << PD6); 

  cli(); // DISABLE INTERRUPTS

  // TIMER1 W/ INTERRUPT

  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
  OCR1A = 2500;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // TIMER2 W/ INTERRUPT

  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
  TCNT2  = 0; //initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 255;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS22 bit for 64 prescaler
  TCCR2B |= (1 << CS22);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
	
  // INITIALIZE INTERFACE DEVICES

  createObject(menu_TYPE,0);
  createObject(oled_TYPE,0);
  createObject(strip_TYPE,0);
  createObject(manager_TYPE,0);

  // INTRO BOOT SEQUENCE

  _strip->setColor(0,0,0);
  _strip->setIntensity(0);
  _oled->clearAll();
  _oled->bootingPrint();
  delay(300);
  _oled->clearAll();
  _strip->lubDub();
  delay(100);
  _strip->sweepColor(111,0,0,10);
  _oled->_screen->drawBitmap(10,10,images[1], 100, 100, WHITE);
  _oled->_screen->display();
  delay(300);
  _strip->setColor(0,0,0);
  _oled->clearAll();
  _oled->pleaseWaitPrint();
  delay(100);
  _oled->clearAll();

  sei(); // ENABLE INTERRUPTS

}

int main(){

  init();
  setup();

  while(true){

    // MENU STATE MACHINE

    if(_menu->system_state==game){
      
      if(_menu->home_state){

        _oled->clearAll();
        _oled->clearAll();
        _strip->inverseSweep(10);
        _strip->setColor(100,0,0);
        _strip->setIntensity(75);
        _delay_ms(1000);
        _menu->home_state = false;
        _menu->selected_demo = 0;
        _menu->selected_device = 0;
        D_index = 0;
        
      }

      if(!(_menu->printed)){

        _oled->clearAll();
        _strip->setColor(100,0,0);
        _strip->setIntensity(75);
        _menu->system_state = game;
        _oled->printGameMenu();
        _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);
        cursor_max = 2;
        _menu->cursor_current = 0;
        _menu->cursor_prev = cursor_max;
        _menu->printed = true;

      }
      
      if(!digitalRead(SELECT_PIN)){

        _manager->game_selected = zone;
        _menu->system_state = demo;
        _menu->printed = false;
        _oled->clearAll();
        _oled->pleaseWaitPrint();
        _oled->clearAll();
        _strip->setColor(100,10,0);
        _strip->setIntensity(75);
        cursor_max = 2;
        _menu->cursor_current = 0;
        _menu->cursor_prev = cursor_max;
        delay(50);

      }

    }

    if(_menu->system_state==demo){

      if(!(_menu->printed)){
        
        _oled->clearAll();
        _oled->printDemoMenu();
        _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);
        _menu->printed = true;

      }
      
      if(!digitalRead(SELECT_PIN)){

        _menu->selected_demo = _menu->cursor_current;
        _menu->system_state = device;
        _menu->printed = false;
        _oled->clearAll();
        _oled->pleaseWaitPrint();
        _oled->clearAll();
        _strip->setColor(100,30,0);
        _strip->setIntensity(75);
        cursor_max = 2;
        _menu->cursor_current = 0;
        _menu->cursor_prev = cursor_max;
        delay(50);

      }

    }

    if(_menu->system_state==device){

      if(!(_menu->printed)){
        
        _oled->clearAll();
        _oled->printDeviceMenu();
        _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);
        _menu->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

          _menu->selected_device = _menu->cursor_current;
          _menu->printed = false;
          createObject(_menu->selected_demo, _menu->selected_device);
          _oled->clearAll();
          _strip->setColor(100,100,100);
          _strip->setIntensity(25);
          delay(50);
          _oled->pleaseWaitPrint();
          _menu->system_state = addition;
          cursor_max = 1;
          _menu->cursor_current = 0;
          _menu->cursor_prev = cursor_max;

      }

    }

    if(_menu->system_state==addition){

      if(!(_menu->printed)){

        _oled->clearAll();
        _oled->printAdditionMenu();
        _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);
        _menu->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

        _menu->printed = false;
        _oled->clearAll();

        if((_menu->cursor_current)){

            _menu->system_state = demo;
            cursor_max = 2;
            _menu->printed = false;
            _oled->clearAll();
            _oled->pleaseWaitPrint();
            delay(100);
            _oled->clearAll();
            _strip->setColor(0,0,0);
            _strip->setIntensity(75);
            cursor_max = 1; // investigate this
            _menu->cursor_current = 0;
            _menu->cursor_prev = cursor_max;
            delay(50);

        } else {

          _oled->_screen->drawBitmap(10,10, images[_menu->selected_demo], 100, 100, WHITE);
          _oled->_screen->display();
          _menu->system_state = running;
          _menu->demo_state = started;
          _strip->setColor(20,20,20);
          _strip->setIntensity(50);
          delay(50);

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

        _strip->setIntensity(75);

        _manager->refreshFlag = 0;

      }

      if(_manager->switchFlag){

        _manager->updateObjective();
        if(_manager->scoreFlag){

          _manager->score++;

        }
        _manager->scoreFlag = 0;
        _manager->switchFlag = 0;

      }

      if(_manager->gameFlag){

        _manager->gameFlag = 0;

        _manager->endGame();

        _menu->system_state = again;

      }

    }

    if(_menu->system_state==again){

      if(!(_menu->printed)){

        _strip->setColor(100,0,0);
        _strip->setIntensity(75);
        _oled->clearAll();
        _oled->printAgainMenu();
        cursor_max = 1;
        _menu->cursor_current = 0;
        _menu->cursor_prev = cursor_max;
        _oled->printSelector(_menu->cursor_prev,_menu->cursor_current, false);
        _menu->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

        _menu->printed = false;
        _oled->clearAll();

        if((_menu->cursor_current)){

          _menu->system_state = game;
          cursor_max = 2;
          _menu->printed = false;
          _oled->clearAll();
          _oled->pleaseWaitPrint();
          delay(100);
          _oled->clearAll();
          _strip->inverseSweep(10);
          cursor_max = 1;
          _menu->cursor_current = 0;
          _menu->cursor_prev = cursor_max;
          delay(50);

        } else {

          _oled->_screen->drawBitmap(10,10, images[_menu->selected_demo], 100, 100, WHITE);
          _oled->_screen->display();
          _menu->system_state = running;
          _menu->demo_state = started;
          _strip->setColor(20,20,20);
          _strip->setIntensity(50);
          delay(50);

        }

      }
    
    }
    
  }

  return 0;

}