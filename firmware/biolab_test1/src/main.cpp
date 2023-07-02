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

uint8_t refreshFlag = 0;
uint8_t refreshCount = 0;
uint8_t crankFlag = 0;
uint8_t mod = 0;

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
    //strip_ptr = new strip(menu_ptr);
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
  }

}

void deleteObject(int objtype, int portnum)
{

  // implement destruction

}

// INTERRUPT SERVICE ROUTINES
  
//Interrupt service routine for a timer that exectures every millisecond. DO NOT call functions/methods from within
//an ISR. Set flags that are checked for within the main loop. You want to spend as little time inside of an ISR as
//possible to prevent undefined program behavior. 

// TODO use flags instead of heavy ISR lease

ISR (TIMER1_COMPA_vect)
{

  menu_ptr->cursor_prev = menu_ptr->cursor_current;

  if(!digitalRead(HOME_PIN)){

    menu_ptr->printed = false;
    menu_ptr->system_state = welcome;
    menu_ptr->demo_state = stopped;
    menu_ptr->home_state = true;

  } else if(menu_ptr->system_state==running || menu_ptr->system_state==welcome){

  
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

}

ISR (TIMER2_COMPA_vect)
{
    refreshCount++;
    if(refreshCount==15){

      refreshFlag = 1;
      refreshCount = 0;

    }
}

ISR (PCINT0_vect)
{

  PCIFR ^= (1 << PCIF0);
  crankFlag = 1;

}

ISR (PCINT1_vect)
{

  PCIFR ^= (1 << PCIF0);
  crankFlag = 1;

}

ISR (PCINT2_vect)
{

  PCIFR ^= (1 << PCIF0);
  crankFlag = 1;

}

// ISR (PCINT3_vect)
// {

//   PCIFR ^= (1 << PCIF0);
//   digitalWrite(13,HIGH);
//   digitalWrite(14,HIGH);

// }

// ISR(PCINT7_vect){

//   PORTD ^= (1 << PD5);
//   PORTD ^= (1 << PD6);

// }

void setup()   {

  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(14,LOW);

  cli();

  // TIMER1 W/ INTERRUPT

  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  OCR1A = 2500;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // TIMER2 W/ INTERRUPT

  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
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

  // strip_ptr->setColor(0,0,0);
  // strip_ptr->setIntensity(0);
  // oled_ptr->clearAll();
  // oled_ptr->bootingPrint();
  // delay(300);
  // oled_ptr->clearAll();
  // strip_ptr->lubDub();
  // delay(100);
  // strip_ptr->sweepColor(111,0,0,10);
  // oled_ptr->_screen->drawBitmap(10,10,images[1], 100, 100, WHITE);
  // oled_ptr->_screen->display();
  // delay(300);
  // strip_ptr->setColor(0,0,0);
  // oled_ptr->clearAll();
  // oled_ptr->pleaseWaitPrint();
  // delay(100);
  oled_ptr->clearAll();

  sei();

}

int main(){

  init();
  setup();

  int i;

  while(true){

    if(menu_ptr->system_state==welcome){
      if(!(menu_ptr->printed)){
        
        if(menu_ptr->home_state){

          oled_ptr->clearAll();
          strip_ptr->lubDub();
          strip_ptr->setColor(100,0,0);
          strip_ptr->setIntensity(50);
          menu_ptr->home_state = false;
          menu_ptr->selected_demo = 0;
          menu_ptr->selected_device = 0;
          menu_ptr->cursor_current = 0;
          menu_ptr->cursor_prev = cursor_max;
          D_index = 0;
          
        }

        oled_ptr->clearAll();
        menu_ptr->system_state = demo;
        oled_ptr->printDemoMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
        cursor_max = 2;
        menu_ptr->cursor_current = 0;
        menu_ptr->cursor_prev = cursor_max;
        menu_ptr->printed = true;

      }

    }

    if(menu_ptr->system_state==demo){

      if(!digitalRead(SELECT_PIN)){

        menu_ptr->selected_demo = menu_ptr->cursor_current;
        menu_ptr->system_state = device;
        menu_ptr->printed = false;
        oled_ptr->clearAll();
        oled_ptr->pleaseWaitPrint();
        oled_ptr->clearAll();
        strip_ptr->setColor(0,0,100);
        strip_ptr->setIntensity(50);
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
          createObject(int(menu_ptr->selected_demo), int(menu_ptr->selected_device));
          oled_ptr->clearAll();
          strip_ptr->setColor(50,0,50);
          strip_ptr->setIntensity(50);
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

          if(!(menu_ptr->cursor_current)){

              menu_ptr->system_state = welcome;
              cursor_max = 2;
              menu_ptr->printed = false;
              oled_ptr->clearAll();
              oled_ptr->pleaseWaitPrint();
              delay(100);
              oled_ptr->clearAll();
              strip_ptr->setColor(0,0,100);
              strip_ptr->setIntensity(50);
              delay(50);

          } else if(menu_ptr->cursor_current){

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

      if(crankFlag){

        for(i = 0; i<D_index; i++){

          if(D_set[i]->current_affector==direct_affector){

            D_set[i]->updateGame(1);
            crankFlag = 0;

          }

        }

      }

      if(refreshFlag){

        strip_ptr->setColor(0,0,0);

        for(i = 0; i<D_index; i++){

          D_set[i]->updateGame(0);
          D_set[i]->captureData();
          manager_ptr->plotAffector(D_set[i]->returnPos(), i);

        }

        refreshFlag = 0;
        strip_ptr->setIntensity(50);

      }

    }

  }

  return 0;

}

