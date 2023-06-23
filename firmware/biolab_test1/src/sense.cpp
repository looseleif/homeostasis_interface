#include <sense.h>

sense::sense(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  sense_main_ptr = mainptr;
  sense_menu_ptr = menuptr;
  sense_oled_ptr = oledptr;
  sense_strip_ptr = stripptr;
  portNum = port;

  // HARD CODED FOR NOW!!!

  trigPin = D2_A;
  echoPin = D2_B;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ;
  distance = 0;

  sense_ultra = new UltraSonicDistanceSensor(trigPin,echoPin);

}

void sense::captureData(void)
{
    distance = static_cast<int>(sense_ultra->measureDistanceCm());
}

void sense::updateGame(void)
{

  for(int i = 0; i<distance%NUM_LEDS; i++){

    sense_strip_ptr->leds[i] = CRGB(100,0,0);

  }

  for(int i = distance%NUM_LEDS; i<NUM_LEDS; i++){

    sense_strip_ptr->leds[i] = CRGB(0,0,0);

  }

  FastLED.show();
  
}

int sense::returnVal(void){

  return abs(distance);

}