#include <sense.h>

sense::sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){

  sense_soft = new SlowSoftI2CMaster(A4, A5, true);

  // write your own god damn driver chase!
  // after swimming that is, gotta clear the mind

  sense_accel = new Adafruit_ADXL343(12345);
  sense_accel->setRange(ADXL343_RANGE_2_G);
  sense_accel->setDataRate(ADXL343_DATARATE_1600_HZ);

}

void sense::captureData(void)
{
  return;
}

void sense::updateGame(int x)
{
  return;
}

int8_t sense::returnVal(void){
  return 0;
}

uint8_t sense::returnPos(void){

  return 0;

}




