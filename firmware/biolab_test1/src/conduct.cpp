#include <conduct.h>>

conduct::conduct(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){

  conduct_accel = new Adafruit_ADXL343(12345);
  conduct_accel->setRange(ADXL343_RANGE_2_G);
  conduct_accel->setDataRate(ADXL343_DATARATE_1600_HZ);

}

void conduct::captureData(void)
{
  return;
}

void conduct::updateGame(int x)
{
  return;
}

int8_t conduct::returnVal(void){
  return 0;
}

uint8_t conduct::returnPos(void){

  return 0;

}




