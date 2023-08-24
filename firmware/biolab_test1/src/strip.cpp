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
    
    this->leds[i] = CRGB(r,g,b);
    FastLED.show();
    _delay_ms(rate);

  }

}

void strip::inverseSweep(int rate){
  
  for(int i = NUM_LEDS-1; i>=0; i--){
    
    this->leds[i] = CRGB(0,0,0);
    FastLED.show();
    _delay_ms(rate);

  }

}

void strip::lubDub(void){
  
  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(111,0,0);
    _delay_ms(15);
    
  }

  FastLED.setBrightness(0);
  FastLED.show();
  _delay_ms(50);

  FastLED.setBrightness(50);
  FastLED.show();
  _delay_ms(200);

  FastLED.setBrightness(0);
  FastLED.show();
  _delay_ms(50);

  FastLED.setBrightness(50);
  FastLED.show();
  _delay_ms(200);

  FastLED.setBrightness(0);
  FastLED.show();
  _delay_ms(250);

  FastLED.setBrightness(50);
  FastLED.show();
  _delay_ms(200);

  FastLED.setBrightness(0);
  FastLED.show();
  _delay_ms(50);

  FastLED.setBrightness(50);
  FastLED.show();
  _delay_ms(200);

  FastLED.setBrightness(0);
  FastLED.show();
  _delay_ms(50);

  for(int i = 0; i<NUM_LEDS; i++){

    this->leds[i] = CRGB(0,0,0);
    _delay_ms(15);

  }

  FastLED.setBrightness(50);

  return;

}