#include <direct.h>>

direct::direct(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  direct_main_ptr = mainptr;
  direct_menu_ptr = menuptr;
  direct_oled_ptr = oledptr;
  direct_strip_ptr = stripptr;
  portNum = port;

  direct_pin1 = D2_A;
  direct_pin2 = D2_B;

}

void direct::captureData(void)
{

  direct_strip_ptr->setColor(100,100,0);
  direct_strip_ptr->setIntensity(25);

}

void direct::updateGame(void)
{

  digitalWrite(13,LOW);
  digitalWrite(14,LOW);
  delay(100);
  

}

int direct::returnVal(void){



}