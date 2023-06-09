#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define OLED_MOSI     D11
#define OLED_CLK      D13
#define OLED_DC       D6
#define OLED_CS       D10
#define OLED_RST      D7

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

// Create the OLED display
Adafruit_SH1107 display = Adafruit_SH1107(128, 128,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);


#include <modules.h>

#include <menu.h>
#include <oled.h>
#include <strip.h>

#include <sense.h>

_device *main_ptr = new _device;

menu *menu_ptr;
oled *oled_ptr;
strip *strip_ptr;

_device *D1_ptr;
_device *D2_ptr;
_device *D3_ptr;
_device *A1_ptr;
_device *A2_ptr;
_device *A3_ptr;

int8_t D_index = 0;
int8_t A_index = 0;

_device *D_set[3] = {D1_ptr,D2_ptr,D3_ptr};
_device *A_set[3] = {A1_ptr,A2_ptr,A3_ptr};

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
  case speak_TYPE:
    //strip_ptr = new strip(menu_ptr);
    break;
  case hold_TYPE:
    //strip_ptr = new strip(menu_ptr);
    break;
  case debug_TYPE:
    //strip_ptr = new strip(menu_ptr);
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

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
  
  menu_ptr->cursor_prev = menu_ptr->cursor_current;

  if(!digitalRead(DOWN_PIN)){

    menu_ptr->cursor_current++;
    menu_ptr->cursor_current%=6;
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  } else if(!digitalRead(UP_PIN)){

    if(menu_ptr->cursor_current==0){

      menu_ptr->cursor_current = 5;

    } else {
    menu_ptr->cursor_current--;
    }
    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, false);

  } else if(!digitalRead(HOME_PIN)){

    oled_ptr->printSelector(menu_ptr->cursor_prev,menu_ptr->cursor_current, true);

    menu_ptr->printed = false;
    menu_ptr->system_state = welcome;
    menu_ptr->demo_state = stopped;
    menu_ptr->home_state = true;

  }

	TCNT1 = 65500;   // build period of ~1ms

}

// START-UP

void setup()   {

  // PORT DATA DIRECTION
  
  // DDRA |= 0b00000000;
  // DDRB |= 0b00000000;
  // DDRC |= 0b00000000;
  // DDRD |= 0b00000000;

  DDRD &= ~_BV(DDD7);
  PORTD |= _BV(PORTD7);

  DDRD &= ~_BV(DDD6);
  PORTD |= _BV(PORTD6);

  // TIMER0 ISR EVERY ~2 MILLISECOND

  TCNT1 = (65500);   // for 1 sec at 16 MHz	 
  TCCR1A = 0x00;
	TCCR1B = (1 << CS10) | (1 << CS12); // Timer mode with 8 prescler
	TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();  // Enable global interrupts by setting global interrupt enable bit in SREG
	
  // CREATE OBJECTS

  createObject(menu_TYPE,0);
  createObject(oled_TYPE,0);
  createObject(strip_TYPE,0);

  // INTRO BOOT SEQUENCE

  strip_ptr->setColor(0,0,0);
  strip_ptr->setIntensity(0);
  oled_ptr->clearAll();
  oled_ptr->bootingPrint();
  delay(100);
  oled_ptr->clearAll();
  strip_ptr->lubDub();
  delay(100);
  strip_ptr->sweepColor(255,0,0,10);
  oled_ptr->_screen->drawBitmap(-20,0, heart_bmp, 100, 100, WHITE);
  oled_ptr->_screen->display();
  delay(100);
  strip_ptr->setColor(0,0,0);
  oled_ptr->clearAll();
  oled_ptr->pleaseWaitPrint();
  delay(100);
  oled_ptr->clearAll();

}

void testdrawline() {
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, SH110X_WHITE);
    display.display();
    delay(1);
  }
  delay(250);
}

void testdrawrect(void) {
    display.drawRect(0, 0, 50, 25, SH110X_WHITE);
    display.display();
    delay(50);
}

int main(){

  //pinMode(D8, OUTPUT);
  pinMode(9, OUTPUT);

  //digitalWrite(D8,LOW);
  //digitalWrite(D9,LOW);

  init();
  //setup();

  // Start OLED
  display.begin(0, true); // we dont use the i2c address but we will reset!
  

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw many lines


  int i=0;

  while(true){

    delay(1000);
    //digitalWrite(D8,LOW);
    digitalWrite(9,HIGH);
    delay(1000);
    //digitalWrite(D8,HIGH);
    digitalWrite(9,LOW);
    i++;
    display.setRotation(i%4);

      

    // miniature bitmap display
    display.clearDisplay();
    testdrawrect();
    display.display();
    delay(1);


/*

    if(menu_ptr->system_state==welcome){
      if(!(menu_ptr->printed)){
        
        oled_ptr->clearAll();
        menu_ptr->system_state = demo;
        oled_ptr->printDemoMenu();
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
        strip_ptr->setColor(100,0,0);
        strip_ptr->setIntensity(50);
        delay(50);

      }

    }

    if(menu_ptr->system_state==device){

      if(!(menu_ptr->printed)){
        
        oled_ptr->clearAll();
        oled_ptr->printDeviceMenu();
        menu_ptr->printed = true;

      }

      if(!digitalRead(SELECT_PIN)){

          menu_ptr->selected_device = menu_ptr->cursor_current;
          menu_ptr->demo_state = started;
          menu_ptr->system_state = running;
          menu_ptr->printed = false;
          createObject(menu_ptr->selected_demo, menu_ptr->selected_device);
          // oled_ptr->clearAll();
          // strip_ptr->setColor(100,0,0);
          // strip_ptr->setIntensity(50);
          // delay(50);

      }

    }
      
    if(menu_ptr->system_state==running){

        
      D1_ptr->calculateRate(0);


    }

    */

  }
    


  return 0;

}