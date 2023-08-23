#include <fixate.h>

fixate::fixate(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){
  _menu = menuptr;
  _oled = oledptr;
  _strip = stripptr;
  portNum = port;
  pos = 0;
  if(_menu->selected_device==0){
      trigPin = D1_A;
      echoPin = D1_B;
      portNum = 0;
  } else if(_menu->selected_device==1){
      trigPin = D2_A;
      echoPin = D2_B;
      portNum = 1;
  } else if(_menu->selected_device==2){
      trigPin = D3_A;
      echoPin = D3_B;
      portNum = 2;
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
  return pos%NUM_LEDS;
}