#include <strip.h>

strip::strip(menu *ptr) {

    _strip_menu_ptr = ptr;
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void strip::setIntensity(int val){

    FastLED.setBrightness(val);
    FastLED.show();
    return;

}

void strip::setColor(int r, int g, int b){

  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(r,g,b);

  }

}

void strip::sweepColor(int r, int g, int b, int rate){

  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(100+(50),0,0);
    FastLED.show();
    delay(rate);

  }

}

void strip::lubDub(void){

  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(100+(50*i),0,0);
    delay(15);

  }

  FastLED.setBrightness(0);
  FastLED.show();
  delay(50);

  FastLED.setBrightness(25);
  FastLED.show();
  delay(200);

  FastLED.setBrightness(0);
  FastLED.show();
  delay(50);

  FastLED.setBrightness(50);
  FastLED.show();
  delay(200);

  FastLED.setBrightness(0);
  FastLED.show();
  delay(250);

  FastLED.setBrightness(75);
  FastLED.show();
  delay(200);

  FastLED.setBrightness(0);
  FastLED.show();
  delay(50);

  FastLED.setBrightness(100);
  FastLED.show();
  delay(200);

  FastLED.setBrightness(0);
  FastLED.show();
  delay(50);

  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(0,0,0);
    delay(15);

  }

  FastLED.setBrightness(100);

  return;

}