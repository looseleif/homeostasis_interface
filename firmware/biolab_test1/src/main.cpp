#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <modules.h>
#include <menu.h>
#include <oled.h>
#include <strip.h>
#include <sense.h>

_device *main_ptr = new _device;

menu *menu_ptr;
oled *oled_ptr;
strip *strip_ptr;

_affector *D1_ptr;
_affector *D2_ptr;
_affector *D3_ptr;

int8_t D_index = 0;

_affector *D_set[3] = {D1_ptr,D2_ptr,D3_ptr};

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
    //strip_ptr = new strip(menu_ptr);
    break;
  case sense_TYPE:
    D_set[D_index] = new sense(D_index,main_ptr,menu_ptr,oled_ptr,strip_ptr);
    D_index++;
    break;
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

  if(!digitalRead(DOWN_PIN)){

    menu_ptr->cursor_current++;
    menu_ptr->cursor_current%=3;
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  } else if(!digitalRead(UP_PIN)){

    if(menu_ptr->cursor_current==0){

      menu_ptr->cursor_current = 2;

    } else {
    menu_ptr->cursor_current--;
    }
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  } else if(!digitalRead(HOME_PIN)){

    menu_ptr->printed = false;
    menu_ptr->system_state = welcome;
    menu_ptr->demo_state = stopped;
    menu_ptr->home_state = true;

  }

  // if(menu_ptr->selected_demo==sense_TYPE && menu_ptr->system_state==running){
    
  //   char dist_str[3];
  //   snprintf(dist_str, sizeof(dist_str), "%d", D_set[0]->returnVal());
  //   oled_ptr->clearAll();
  //   oled_ptr->sendString(dist_str);
        
  // }

}

ISR (TIMER2_COMPA_vect)
{

}

void setup()   {

  // PORT DATA DIRECTION
  
  // DDRA |= 0b00000000;
  // DDRB |= 0b00000000;
  // DDRC |= 0b00000000;
  // DDRD |= 0b00000000;

  // DDRD &= ~_BV(DDD7);
  // PORTD |= _BV(PORTD7);
  // DDRD &= ~_BV(DDD6);
  // PORTD |= _BV(PORTD6);

  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(14,HIGH);

  cli();

  // TIMER1 W/ INTERRUPT

  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 2500;// = (16*10^6) / (1*1024) - 1 (must be <65536)
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

  sei();

}

int main(){

  init();
  setup();

  int i;

  while(true){

    digitalWrite(13,LOW);
    digitalWrite(14,HIGH);
    delay(10);
    digitalWrite(13,HIGH);
    digitalWrite(14,LOW);
    delay(10);

    if(menu_ptr->system_state==welcome){
      if(!(menu_ptr->printed)){
        
        if(menu_ptr->home_state){

          oled_ptr->clearAll();
          strip_ptr->lubDub();
          menu_ptr->home_state = false;
          menu_ptr->selected_demo = 0;
          menu_ptr->selected_device = 0;
          menu_ptr->cursor_current = 0;
          menu_ptr->cursor_prev = 2;
          D_index = 0;
          
        }

        oled_ptr->clearAll();
        menu_ptr->system_state = demo;
        oled_ptr->printDemoMenu();
        oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);
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
        delay(100);
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
          oled_ptr->_screen->drawBitmap(10,10, images[menu_ptr->selected_demo], 100, 100, WHITE);
          oled_ptr->_screen->display();
          menu_ptr->demo_state = started;
          menu_ptr->system_state = running;

      }

    }
      
    if(menu_ptr->system_state==running){

      if(menu_ptr->selected_demo == sense_TYPE){
      
        for(i = 0; i<D_index; i++){

          D_set[i]->captureData();
          D_set[i]->updateGame();

        }
        


      }

    }

  }

  return 0;

}

