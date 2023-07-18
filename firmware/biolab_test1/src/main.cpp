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
#include <manager.h>
#include <avr/interrupt.h>
#include <avr/io.h>

_device *main_ptr = new _device;

menu *menu_ptr;
oled *oled_ptr;
strip *strip_ptr;
manager *manager_ptr;

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
    menu_ptr = new menu();
    break;
  case oled_TYPE:
    oled_ptr = new oled(menu_ptr);
    break;
  case strip_TYPE:
    strip_ptr = new strip(menu_ptr);
    break;
  case grip_TYPE:
    break;
  case direct_TYPE:
    D_set[D_index] = new direct(D_index,main_ptr,menu_ptr,oled_ptr,strip_ptr);
    D_set[D_index]->current_affector = direct_affector;
    D_index++;
    break;
  case sense_TYPE:
    D_set[D_index] = new sense(D_index,main_ptr,menu_ptr,oled_ptr,strip_ptr);
    D_set[D_index]->current_affector = sense_affector;
    D_index++;
    break;
  case manager_TYPE:
    manager_ptr = new manager(main_ptr,menu_ptr,oled_ptr,strip_ptr);
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

  menu_ptr->cursor_prev = menu_ptr->cursor_current;

  if(!digitalRead(HOME_PIN)){

    menu_ptr->printed = false;
    menu_ptr->system_state = game;
    menu_ptr->demo_state = stopped;
    menu_ptr->home_state = true;

  } else if(menu_ptr->system_state==running){

  } else if(!digitalRead(DOWN_PIN)){

    menu_ptr->cursor_current++;
    menu_ptr->cursor_current%=(cursor_max+1);
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  } else if(!digitalRead(UP_PIN)){

    if(menu_ptr->cursor_current==0){

      menu_ptr->cursor_current = cursor_max;

    } else {
    menu_ptr->cursor_current--;
    }
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  }
  
  if(menu_ptr->system_state==running){
    
    manager_ptr->gameCount++;
    if(manager_ptr->gameCount==45){

      manager_ptr->gameCount = 0;
      manager_ptr->gameFlag = 1;

    }

  }

}

// DEVICE & SWITCH UPDATE

ISR (TIMER2_COMPA_vect)
{

    manager_ptr->refreshCount++;
    if(manager_ptr->refreshCount==25){

      PORTD ^= (1 << PD6);

      manager_ptr->switchCount++;
      manager_ptr->refreshFlag = 1;
      manager_ptr->refreshCount = 0;

    }
    if(manager_ptr->switchCount==25+(rand()%55)){
      manager_ptr->switchFlag = 1;
      manager_ptr->switchCount = 0;
    }

}

// PORT PIN CHANGE

ISR (PCINT0_vect)
{

  PCIFR ^= (1 << PCIF0);
  manager_ptr->crankFlag = 1;

}

ISR (PCINT1_vect)
{

  PCIFR ^= (1 << PCIF0);
  manager_ptr->crankFlag = 1;

}

ISR (PCINT2_vect)
{

  PCIFR ^= (1 << PCIF0);
  manager_ptr->crankFlag = 1;

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

  strip_ptr->setColor(0,0,0);
  strip_ptr->setIntensity(0);
  oled_ptr->clearAll();
  oled_ptr->bootingPrint();
  delay(300);
  oled_ptr->clearAll();
  strip_ptr->lubDub();
  delay(100);
  strip_ptr->sweepColor(111,0,0,10);
  oled_ptr->_screen->drawBitmap(10,10,images[1], 100, 100, WHITE);
  oled_ptr->_screen->display();
  delay(300);
  strip_ptr->setColor(0,0,0);
  oled_ptr->clearAll();
  oled_ptr->pleaseWaitPrint();
  delay(100);
  oled_ptr->clearAll();

  sei(); // ENABLE INTERRUPTS

}

int main(){

  init();
  setup();

  while(true){

    // MENU STATE MACHINE

    if(menu_ptr->system_state==game){
      
      if(menu_ptr->home_state){

        oled_ptr->clearAll();
        oled_ptr->clearAll();
        strip_ptr->inverseSweep(10);
        strip_ptr->setColor(100,0,0);
        strip_ptr->setIntensity(75);
        _delay_ms(1000);
        menu_ptr->home_state = false;
        menu_ptr->selected_demo = 0;
        menu_ptr->selected_device = 0;
        D_index = 0;
        
      }

      if(!(menu_ptr->printed)){

        oled_ptr->clearAll();
        strip_ptr->setColor(100,0,0);
        strip_ptr->setIntensity(75);
        menu_ptr->system_state = game;
        oled_ptr->printGameMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        cursor_max = 2;
        menu_ptr->cursor_current = 0;
        menu_ptr->cursor_prev = cursor_max;
        menu_ptr->printed = true;

      }
      
      if(!digitalRead(SELECT_PIN)){

        manager_ptr->game_selected = zone;
        menu_ptr->system_state = demo;
        menu_ptr->printed = false;
        oled_ptr->clearAll();
        oled_ptr->pleaseWaitPrint();
        oled_ptr->clearAll();
        strip_ptr->setColor(100,10,0);
        strip_ptr->setIntensity(75);
        cursor_max = 2;
        menu_ptr->cursor_current = 0;
        menu_ptr->cursor_prev = cursor_max;
        delay(50);

      }

    }

    if(menu_ptr->system_state==demo){

      if(!(menu_ptr->printed)){
        
        oled_ptr->clearAll();
        oled_ptr->printDemoMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        menu_ptr->printed = true;

      }
      
      if(!digitalRead(SELECT_PIN)){

        menu_ptr->selected_demo = menu_ptr->cursor_current;
        menu_ptr->system_state = device;
        menu_ptr->printed = false;
        oled_ptr->clearAll();
        oled_ptr->pleaseWaitPrint();
        oled_ptr->clearAll();
        strip_ptr->setColor(100,30,0);
        strip_ptr->setIntensity(75);
        cursor_max = 2;
        menu_ptr->cursor_current = 0;
        menu_ptr->cursor_prev = cursor_max;
        delay(50);

      }

    }

    if(menu_ptr->system_state==device){

      if(!(menu_ptr->printed)){
        
        oled_ptr->clearAll();
        oled_ptr->printDeviceMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        menu_ptr->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

          menu_ptr->selected_device = menu_ptr->cursor_current;
          menu_ptr->printed = false;
          createObject(menu_ptr->selected_demo, menu_ptr->selected_device);
          oled_ptr->clearAll();
          strip_ptr->setColor(100,100,100);
          strip_ptr->setIntensity(25);
          delay(50);
          oled_ptr->pleaseWaitPrint();
          menu_ptr->system_state = addition;
          cursor_max = 1;
          menu_ptr->cursor_current = 0;
          menu_ptr->cursor_prev = cursor_max;

      }

    }

    if(menu_ptr->system_state==addition){

      if(!(menu_ptr->printed)){

        oled_ptr->clearAll();
        oled_ptr->printAdditionMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        menu_ptr->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

        menu_ptr->printed = false;
        oled_ptr->clearAll();

        if((menu_ptr->cursor_current)){

            menu_ptr->system_state = demo;
            cursor_max = 2;
            menu_ptr->printed = false;
            oled_ptr->clearAll();
            oled_ptr->pleaseWaitPrint();
            delay(100);
            oled_ptr->clearAll();
            strip_ptr->setColor(0,0,0);
            strip_ptr->setIntensity(75);
            cursor_max = 1; // investigate this
            menu_ptr->cursor_current = 0;
            menu_ptr->cursor_prev = cursor_max;
            delay(50);

        } else {

          oled_ptr->_screen->drawBitmap(10,10, images[menu_ptr->selected_demo], 100, 100, WHITE);
          oled_ptr->_screen->display();
          menu_ptr->system_state = running;
          menu_ptr->demo_state = started;
          strip_ptr->setColor(20,20,20);
          strip_ptr->setIntensity(50);
          delay(50);

        }

      }

    }

    if(menu_ptr->system_state==running){

      if(manager_ptr->crankFlag){

        for(int i = 0; i<D_index; i++){

          if(D_set[i]->current_affector==direct_affector){

            D_set[i]->updateGame(1);
            manager_ptr->crankFlag = 0;

          }

        }

      }

      if(manager_ptr->refreshFlag){
        
        strip_ptr->setColor(0,0,0);

        manager_ptr->plotObjective();

        for(int i = 0; i<D_index; i++){

          D_set[i]->updateGame(0);
          D_set[i]->captureData();
          manager_ptr->plotAffector(D_set[i]->returnPos(), i);
          manager_ptr->checkInside(D_set[i]->returnPos());

        }

        strip_ptr->setIntensity(75);

        manager_ptr->refreshFlag = 0;

      }

      if(manager_ptr->switchFlag){

        manager_ptr->updateObjective();
        if(manager_ptr->scoreFlag){

          manager_ptr->score++;

        }
        manager_ptr->scoreFlag = 0;
        manager_ptr->switchFlag = 0;

      }

      if(manager_ptr->gameFlag){

        manager_ptr->gameFlag = 0;

        manager_ptr->endGame();

        menu_ptr->system_state = again;

      }

    }

    if(menu_ptr->system_state==again){

      if(!(menu_ptr->printed)){

        strip_ptr->setColor(100,0,0);
        strip_ptr->setIntensity(75);
        oled_ptr->clearAll();
        oled_ptr->printAgainMenu();
        cursor_max = 1;
        menu_ptr->cursor_current = 0;
        menu_ptr->cursor_prev = cursor_max;
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        menu_ptr->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

        menu_ptr->printed = false;
        oled_ptr->clearAll();

        if((menu_ptr->cursor_current)){

          menu_ptr->system_state = game;
          cursor_max = 2;
          menu_ptr->printed = false;
          oled_ptr->clearAll();
          oled_ptr->pleaseWaitPrint();
          delay(100);
          oled_ptr->clearAll();
          strip_ptr->inverseSweep(10);
          cursor_max = 1;
          menu_ptr->cursor_current = 0;
          menu_ptr->cursor_prev = cursor_max;
          delay(50);

        } else {

          oled_ptr->_screen->drawBitmap(10,10, images[menu_ptr->selected_demo], 100, 100, WHITE);
          oled_ptr->_screen->display();
          menu_ptr->system_state = running;
          menu_ptr->demo_state = started;
          strip_ptr->setColor(20,20,20);
          strip_ptr->setIntensity(50);
          delay(50);

        }

      }
    
    }
    
  }

  return 0;

}