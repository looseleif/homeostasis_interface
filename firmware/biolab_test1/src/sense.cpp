#include <sense.h>

sense::sense(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  sense_main_ptr = mainptr;
  sense_menu_ptr = menuptr;
  sense_oled_ptr = oledptr;
  sense_strip_ptr = stripptr;
  portNum = port;

  pos = 0;

  if(sense_menu_ptr->selected_device==0){
      
      trigPin = D1_A;
      echoPin = D1_B;
      portNum = 0;

  } else if(sense_menu_ptr->selected_device==1){
      
      trigPin = D2_A;
      echoPin = D2_B;
      portNum = 1;

  } else if(sense_menu_ptr->selected_device==2){

      trigPin = D3_A;
      echoPin = D3_B;
      portNum = 2;

  }

  sense_ultra = new UltraSonicDistanceSensor(trigPin,echoPin);

}

void sense::captureData(void){

    pos = static_cast<uint8_t>(sense_ultra->measureDistanceCm());

}

void sense::updateGame(int x){
  
}

int8_t sense::returnVal(void){

  return 0;

}

uint8_t sense::returnPos(void){

  return pos%30;

}