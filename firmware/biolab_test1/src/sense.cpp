#include <sense.h>

sense::sense(const uint8_t port, _device *mainptr, menu *menuptr, oled *oledptr, strip *stripptr){

  sense_main_ptr = mainptr;
  sense_menu_ptr = menuptr;
  sense_oled_ptr = oledptr;
  sense_strip_ptr = stripptr;
  portNum = port;

  // HARD CODED FOR NOW!!!

  trigPin = D2_A;
  echoPin = D2_B;

  sense_sensor = new NewPing(trigPin,echoPin,300);

}

void sense::calculateRate(int8_t mod){

  //distance = sense_sensor->ping_median(10)/1000000*343/2;
  //sense_oled_ptr->sendString(String(distance));
  sense_oled_ptr->pleaseWaitPrint();
  delay(500);
  sense_oled_ptr->printGrip();

}

// int8_t sense::returnDelta(void)
//     {
//       pinAVal = digitalRead(encoderPinA);
//       pinBVal = digitalRead(encoderPinB);
//       uint8_t lookupVal = (prevAVal << 3) | (prevBVal << 2) | (pinAVal << 1) | pinBVal;
//       prevAVal = pinAVal;
//       prevBVal = prevBVal;
//       return quadratureLookupTable[lookupVal];
//     }

//     //this is called (through a flag checked for in main)
//     //calculates a production rate and sends it to the strip. 
//     void calculateRate(int8_t modifier)
//     {
//       if(modifier == CRANKSUM_RATETYPE)
//       {
//         int8_t currentOut = returnDelta();
//         //make sure it's not an invalid state change
//         if(currentOut)
//         { 
//         crankSum += currentOut;
//         }
//       }
//       if(modifier == GENERAL_RATETYPE)
//       {
//         // calculates current moving average efficiently
//         movingAverage += (-movingAverage/movingAveragePeriod + crankSum*1.1);

//         //make it pointless to spin the crank too fast
//         if(movingAverage > 80) movingAverage = 80;
//         //prevent excessively small carryover
//         if(movingAverage < 1) movingAverage = 0;
//         overallRate = ((movingAverage/80. * maxProductionRate)*2.0 - consumptionRate) * 0.0001 * CRANKRATESCALAR;// * CRANKRATESCALAR;
//         //reset the sum because it has just been incorporated into a moving avg
//         crankSum = 0;
//         //send the rate to the strip so that it can update the position of this indicator
//         indicatorstrip_ptr->updatePosition(overallRate, portNum);
//       }
//       return;
//     }