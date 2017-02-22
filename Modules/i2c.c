#include "i2c.h"

I2C_Error I2C_Init( uint8 I2C_Channel, uint8 I2C_DesiredSpeedkHz )
{
   // Force DesiredSpeed first
   I2C_DesiredSpeedkHz = LSM9DS1_I2C_FREQ_KHZ;
   // Max for this chip is 100 khz
   if( I2C_DesiredSpeedkHz > I2C_MAX_SPEED )
   {
      return I2C_ChoosenFreqTooHigh;
   }

   // baud rate = bus speed/ ( mul * SCL divider )
   // if baud rate == 100 khz and bus clock is 24 Mhz, then
   // the mul*SCL divider needs to be 240.
   // This means that the availabe ICR values are as follows:
   // 0x1F: SCL = 240, SDA hold value = 33, SCL Hold start = 118, SCL hold stop = 121
   // SDA hold time = bus period * mul * sda hold value
   //               =  42 ns     *  1  * 33  = 1.386 us
   // SCL start hold time = bus period * mul * scl start hold value
   //                             42   *  1  *  118  = 4.956 us
   // SCL stop hold time = bus period * mul * scl stop hold value
   //                             42   *  1  *  121  = 5.082 us

   SET_BIT_IN_REG( I2C0_F, I2C_F_MULT( 0 ) | I2C_F_ICR( ICR_FOR_100khz_24MhzBus ) );
   SET_BIT_IN_REG( I2C0_C1, I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK | I2C_C1_MST_MASK );

}

I2C_Error I2C_SendData( uint8_t * data )
{

}

I2C_Error I2C_ReadData( uint8_t * data )
{

}
