#include <sense.h>

sense::sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr){
  // COM1 only
  sense_soft = new SlowSoftI2CMaster(D1_A, D1_B, true);
  sense_soft->i2c_init();
  // check ID
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAX1<<8|ADXL3XX_REG_DATAX0&0x10000 ? 8 : 0))) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DEVID&0xFF)) return;
  if(sense_soft->i2c_read(true)!=0xE5) return;
  sense_soft->i2c_stop();
  // set data rate
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1 | I2C_WRITE)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_BW_RATE))            return;
  if (!sense_soft->i2c_write(ADXL3XX_DATARATE_100_HZ))        return;
  sense_soft->i2c_stop();
  // set range
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1 | I2C_WRITE)) return;
  if (!sense_soft->i2c_write(ADXL343_MG2G_MULTIPLIER))        return;
  if (!sense_soft->i2c_write(ADXL343_RANGE_4_G))              return;
  sense_soft->i2c_stop();
  // disable interrupt
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1 | I2C_WRITE)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_INT_ENABLE))         return;
  if (!sense_soft->i2c_write(0))                              return;
  sense_soft->i2c_stop();
  // disable interrupt
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1 | I2C_WRITE)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_THRESH_TAP))         return;
  if (!sense_soft->i2c_write(20))                             return;
  sense_soft->i2c_stop();
  // enable measurements
  if (!sense_soft->i2c_start(ADXL343_ADDRESS<<1 | I2C_WRITE)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_POWER_CTL))          return;
  if (!sense_soft->i2c_write(0x08))                           return;
  sense_soft->i2c_stop();
  delay(6);

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
  // read X
  _X = 0x0000;
  _X &= (sense_soft->i2c_read(true))<<8;
  _X &= (sense_soft->i2c_read(true));
  delay(6);
  if (!sense_soft->i2c_rep_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAY1<<8|ADXL3XX_REG_DATAY0&0x10000 ? 8 : 0))) return;
  // send the address
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAY1&0xFF)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAY0&0xFF)) return;
  // read Y
  _Y = 0x0000;
  _Y &= (sense_soft->i2c_read(true))<<8;
  _Y &= (sense_soft->i2c_read(true));
  delay(6);
  if (!sense_soft->i2c_rep_start(ADXL343_ADDRESS<<1| I2C_READ | (ADXL3XX_REG_DATAZ1<<8|ADXL3XX_REG_DATAZ0&0x10000 ? 8 : 0))) return;
  // send the address
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAZ1&0xFF)) return;
  if (!sense_soft->i2c_write(ADXL3XX_REG_DATAZ0&0xFF)) return;
  // read Z
  _Z = 0x0000;
  _Z &= (sense_soft->i2c_read(true))<<8;
  _Z &= (sense_soft->i2c_read(true));
  delay(6);
  sense_soft->i2c_stop();
  return;
}

int8_t sense::returnVal(void){
  return 0;
}

uint8_t sense::returnPos(void){
  return 0;
}




