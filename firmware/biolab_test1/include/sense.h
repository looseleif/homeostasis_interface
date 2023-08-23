#ifndef CONDUCT_H
#define CONDUCT_H

#include <string.h>

#include <modules.h>
#include <menu.h>
#include <strip.h>
#include <oled.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include <SlowSoftI2CMaster.h>
#include <avr/io.h>

#define ADDRLEN 1

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define ADXL343_ADDRESS (0x53) /**< Assumes ALT address pin low */
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
#define ADXL3XX_REG_DEVID (0x00)        /**< Device ID */
#define ADXL3XX_REG_THRESH_TAP (0x1D)   /**< Tap threshold */
#define ADXL3XX_REG_OFSX (0x1E)         /**< X-axis offset */
#define ADXL3XX_REG_OFSY (0x1F)         /**< Y-axis offset */
#define ADXL3XX_REG_OFSZ (0x20)         /**< Z-axis offset */
#define ADXL3XX_REG_DUR (0x21)          /**< Tap duration */
#define ADXL3XX_REG_LATENT (0x22)       /**< Tap latency */
#define ADXL3XX_REG_WINDOW (0x23)       /**< Tap window */
#define ADXL3XX_REG_THRESH_ACT (0x24)   /**< Activity threshold */
#define ADXL3XX_REG_THRESH_INACT (0x25) /**< Inactivity threshold */
#define ADXL3XX_REG_TIME_INACT (0x26)   /**< Inactivity time */
#define ADXL3XX_REG_ACT_INACT_CTL                                              \
  (0x27) /**< Axis enable control for activity and inactivity detection */
#define ADXL3XX_REG_THRESH_FF (0x28) /**< Free-fall threshold */
#define ADXL3XX_REG_TIME_FF (0x29)   /**< Free-fall time */
#define ADXL3XX_REG_TAP_AXES (0x2A)  /**< Axis control for single/double tap */
#define ADXL3XX_REG_ACT_TAP_STATUS (0x2B) /**< Source for single/double tap */
#define ADXL3XX_REG_BW_RATE (0x2C)     /**< Data rate and power mode control */
#define ADXL3XX_REG_POWER_CTL (0x2D)   /**< Power-saving features control */
#define ADXL3XX_REG_INT_ENABLE (0x2E)  /**< Interrupt enable control */
#define ADXL3XX_REG_INT_MAP (0x2F)     /**< Interrupt mapping control */
#define ADXL3XX_REG_INT_SOURCE (0x30)  /**< Source of interrupts */
#define ADXL3XX_REG_DATA_FORMAT (0x31) /**< Data format control */
#define ADXL3XX_REG_DATAX0 (0x32)      /**< X-axis data 0 */
#define ADXL3XX_REG_DATAX1 (0x33)      /**< X-axis data 1 */
#define ADXL3XX_REG_DATAY0 (0x34)      /**< Y-axis data 0 */
#define ADXL3XX_REG_DATAY1 (0x35)      /**< Y-axis data 1 */
#define ADXL3XX_REG_DATAZ0 (0x36)      /**< Z-axis data 0 */
#define ADXL3XX_REG_DATAZ1 (0x37)      /**< Z-axis data 1 */
#define ADXL3XX_REG_FIFO_CTL (0x38)    /**< FIFO control */
#define ADXL3XX_REG_FIFO_STATUS (0x39) /**< FIFO status */

class sense: public _affector
{

    private:

        SlowSoftI2CMaster *sense_soft;

    public:

        sense(const uint8_t port, menu *menuptr, oled *oledptr, strip *stripptr);
        void sense::captureData(void) override;
        void sense::updateGame(int x) override;
        int8_t sense::returnVal(void) override;
        uint8_t sense::returnPos(void) override;
        unsigned long _X;
        unsigned long _Y;
        unsigned long _Z;
        int xval, yval, zval;
        strip *_strip;
        oled *_oled;
        menu *_menu;

};

#endif

