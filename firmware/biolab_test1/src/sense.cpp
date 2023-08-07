#include <sense.h>

sense::sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){

  // connecting I2C to LEFT PORT
  sense_soft = new SlowSoftI2CMaster(D1_A, D1_B, true);

  sense_soft->i2c_init();

  // write your own god damn driver chase!
  // after swimming that, gotta clear the mind

  // _sensorID = sensorID;
  // _wire = &Wire;
  // _addr = addr;
  // _wire = theWire;
  // _begun = false;

  // sense_accel = new Adafruit_ADXL343(12345);
  // sense_accel->setRange(ADXL343_RANGE_2_G);
  // sense_accel->setDataRate(ADXL343_DATARATE_1600_HZ);

  // writeRegister(ADXL3XX_REG_INT_ENABLE, 0);  // Disable interrupts to start
  // writeRegister(ADXL3XX_REG_THRESH_TAP, 20); // 62.5 mg/LSB (so 0xFF = 16 g)
  // writeRegister(ADXL3XX_REG_DUR, 50);        // Max tap duration, 625 µs/LSB
  // writeRegister(ADXL3XX_REG_LATENT,
  //               0); // Tap latency, 1.25 ms/LSB, 0=no double tap
  // writeRegister(ADXL3XX_REG_WINDOW,
  //               0); // Waiting period,  1.25 ms/LSB, 0=no double tap
  // writeRegister(ADXL3XX_REG_TAP_AXES, 0x7); // Enable the XYZ axis for tap

  // // Enable measurements
  // writeRegister(ADXL3XX_REG_POWER_CTL, 0x08);

}

void sense::captureData(void)
{
  return;
}

void sense::updateGame(int x)
{
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAX1<<8|ADXL3XX_REG_DATAX0&0x10000 ? 8 : 0))) return;

  // send the address
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAX1&0xFF)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAX0&0xFF)) return;


  // read
  _X = 0x0000;
  _X &= (sense_soft->i2c_read(true))<<8;
  _X &= (sense_soft->i2c_read(true));

  if (!sense_soft->i2c_rep_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAY1<<8|ADXL3XX_REG_DATAY0&0x10000 ? 8 : 0))) return;

  // send the address
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAY1&0xFF)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAY0&0xFF)) return;


  // read
  _Y = 0x0000;
  _Y &= (sense_soft->i2c_read(true))<<8;
  _Y &= (sense_soft->i2c_read(true));

    if (!sense_soft->i2c_rep_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAZ1<<8|ADXL3XX_REG_DATAZ0&0x10000 ? 8 : 0))) return;

  // send the address
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAZ1&0xFF)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAZ0&0xFF)) return;


  // read
  _Z = 0x0000;
  _Z &= (sense_soft->i2c_read(true))<<8;
  _Z &= (sense_soft->i2c_read(true));

  delay(6);

  return;
}

int8_t sense::returnVal(void){
  return 0;
}

uint8_t sense::returnPos(void){

  return 0;

}




