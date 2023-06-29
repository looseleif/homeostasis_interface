#include <direct.h>>

int8_t quadratureLookupTable[16] = {0,/*-1*/0,1,0,1,0,0,/*-1*/0,/*-1*/0,0,0,1,0,1,/*-1*/0,0};


direct::direct(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  direct_main_ptr = mainptr;
  direct_menu_ptr = menuptr;
  direct_oled_ptr = oledptr;
  direct_strip_ptr = stripptr;
  portNum = port;

  if(direct_menu_ptr->selected_device==0){
      
      direct_pin1 = D1_A;
      direct_pin2 = D1_B;
      portNum = 0;

  } else if(direct_menu_ptr->selected_device==1){
      
      pinMode(D2_B,INPUT_PULLUP);

      cli();
    
      // Configure PD2 as an input using the Data Direction Register D (DDRD)
      DDRA &= ~_BV(DDA6);

      // Enable the pull-up resistor on PD2 using the Port D Data Register (PORTD)
      PORTA |= _BV(PORTA6);

      // Enable pin change interrupt on the PCINT18 pin using Pin Change Mask Register 2 (PCMSK2)
      PCMSK0 |= _BV(PCINT6);

      // Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
      PCICR |= _BV(PCIE0);

      // // Configure PB5 as an output using the Port B Data Direction Register (DDRB)
      // DDRB |= _BV(DDB5);

      sei();

      direct_pin1 = D2_A;
      direct_pin2 = D2_B;
      portNum = 1;

  } else if(direct_menu_ptr->selected_device==2){

      direct_pin1 = D3_A;
      direct_pin2 = D3_B;
      portNum = 2;

  }

}

void direct::captureData(void)
{

}

void direct::updateGame(void)
{

  // int8_t modifier = 0;

  // // if(modifier == CRANKSUM_RATETYPE){

  // //   int8_t currentOut = returnVal();
  // //   //make sure it's not an invalid state change
  // //   if(currentOut)
  // //   { 
  // //   crankSum += currentOut;
  // //   }
  // // }

  // if(modifier == GENERAL_RATETYPE){

  //   // calculates current moving average efficiently
  //   movingAverage += (-movingAverage/movingAveragePeriod + crankSum*1.1);

  //   //make it pointless to spin the crank too fast
  //   if(movingAverage > 80) movingAverage = 80;
  //   //prevent excessively small carryover
  //   if(movingAverage < 1) movingAverage = 0;
  //   overallRate = ((movingAverage/80. * maxProductionRate)*2.0 - consumptionRate) * 0.0001 * CRANKRATESCALAR;// * CRANKRATESCALAR;
  //   //reset the sum because it has just been incorporated into a moving avg
  //   crankSum = 0;
  //   //send the rate to the strip so that it can update the position of this indicator
  //   // direct_strip_ptr->leds[]
  // }
  // return;

}

int direct::returnVal(void){

  // pinAVal = digitalRead(direct_pin1);
  // pinBVal = digitalRead(direct_pin2);
  // uint8_t lookupVal = (prevAVal << 3) | (prevBVal << 2) | (pinAVal << 1) | pinBVal;
  // prevAVal = pinAVal;
  // prevBVal = prevBVal;
  // return quadratureLookupTable[lookupVal];

}




