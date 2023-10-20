#include <fixate.h>

fixate::fixate(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){
  
  // class specific support pointers
  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;

  // current position of fixate affector
  pos = 0;

  if(_menu->selected_port==2){ // LEFT "USB" PORT

      trigPin = D1_A;
      echoPin = D1_B;

  } else if(_menu->selected_port==1){ // MIDDLE "USB" PORT

      trigPin = D2_A;
      echoPin = D2_B;

  } else if(_menu->selected_port==3){ // RIGHT "USB" PORT

      trigPin = D3_A;
      echoPin = D3_B;

  }

  fixate_ultra = new UltraSonicDistanceSensor(trigPin,echoPin);

}

void fixate::captureData(void){

  pos = static_cast<uint8_t>(fixate_ultra->measureDistanceCm());

}

void fixate::updateGame(int x){}

int8_t fixate::returnVal(void){

  return 0;

}

uint8_t fixate::returnPos(void){

  return ((pos+15)%NUM_LEDS);

}