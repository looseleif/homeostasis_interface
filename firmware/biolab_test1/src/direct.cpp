#include <direct.h>>

direct::direct(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){
  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;
  portNum = port;
  if(_menu->selected_device==0){
    cli();
    // Configure input using the Data Direction Register
    DDRB &= ~_BV(DDB1);
    DDRB &= ~_BV(DDB0);
    // Enable the pull-up resistor
    PORTB |= _BV(PORTB1);
    PORTB |= _BV(PORTB0);
    // Enable pin change interruptusing Pin Change Mask Register
    PCMSK1 |= _BV(PCINT9);
    // PCMSK1 |= _BV(PCINT8);
    // Enable pin change interrupt using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= _BV(PCIE1);
    sei();
    direct_pin1 = D1_A;
    direct_pin2 = D1_B;
    portNum = 0;
  } else if(_menu->selected_device==1){
    cli();
    // Configure input using the Data Direction Register
    DDRA &= ~_BV(DDA7);
    DDRA &= ~_BV(DDA6);
    // Enable the pull-up resistor
    PORTA |= _BV(PORTA7);
    PORTA |= _BV(PORTA6);
    // Enable pin change interruptusing Pin Change Mask Register
    PCMSK0 |= _BV(PCINT7);
    //PCMSK0 |= _BV(PCINT6);
    // Enable pin change interrupt using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= _BV(PCIE0);
    sei();
    direct_pin1 = D2_A; //PCINT7
    direct_pin2 = D2_B; //PCINT6
    portNum = 1;
  } else if(_menu->selected_device==2){
    cli();
    // Configure input using the Data Direction Register
    DDRC &= ~_BV(DDC2);
    DDRC &= ~_BV(DDC3);
    // Enable the pull-up resistor
    PORTC |= _BV(PORTC2);
    PORTC |= _BV(PORTC3);
    // Enable pin change interruptusing Pin Change Mask Register
    PCMSK2 |= _BV(PCINT18);
    // PCMSK2 |= _BV(PCINT19);
    // Enable pin change interrupt using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= _BV(PCIE2);
    sei();
    direct_pin1 = D3_A;
    direct_pin2 = D3_B;
    portNum = 2;
  }
}

void direct::captureData(void){}

void direct::updateGame(int x)
{
  if(x == CRANKSUM_RATETYPE){
    crankSum = returnVal();
  }
  if(x == GENERAL_RATETYPE){
    if(crankSum>0){
      direction = 1;
    } else if(crankSum<0){
      direction = -1;
    } else {
      direction = 0;
    }
    if(pos>60){
      pos = NUM_LEDS + pos%NUM_LEDS;
    } else if (pos-1 < NUM_LEDS && direction==-1){
      pos = (2*NUM_LEDS) - 1;
    } else {
      pos += direction;
    }
    crankSum = 0;
  }
  return;
}

int8_t direct::returnVal(void){
  pinAVal = digitalRead(direct_pin2) & 0b1111;
  pinBVal = digitalRead(direct_pin1) & 0b1111;
  int8_t lookupVal = (prevAVal << 3) | (prevBVal << 2) | (pinAVal << 1) | pinBVal;
  prevAVal = pinAVal;
  prevBVal = pinBVal;
  return quadratureLookupTable[lookupVal & 0b1111];
}

uint8_t direct::returnPos(void){
  return pos%NUM_LEDS;
}




