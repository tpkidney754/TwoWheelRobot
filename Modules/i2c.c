#include "i2c.h"

I2C_Error I2C_Init( uint8 I2C_Channel, uint8 I2C_DesiredSpeedkHz )
{
   // Enable port b
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTB_MASK );
   // B0 is SCK, B1 is SDA, both are , alt 2
   SET_BIT_IN_REG( PORTB_PCR0, PORT_PCR_MUX( ALTERNATIVE_2 ) );
   SET_BIT_IN_REG( PORTB_PCR1, PORT_PCR_MUX( ALTERNATIVE_2 ) );
   // Enable clock for i2c device
   SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_I2C0_MASK );

   I2C_DesiredSpeedkHz = LSM9DS1_I2C_FREQ_KHZ;
   // Max for this chip is 100 khz
   if( I2C_DesiredSpeedkHz > I2C_MAX_SPEED )
   {
      return I2C_ChoosenFreqTooHigh;
   }

   // baud rate = bus speed/ ( mul * SCL divider )
   // if baud rate == 100 khz and bus clock is 24 Mhz, then
   // the mul*SCL divider needs to be 240.
   // This means that the availabe ICR valueis
   // 0x1F: SCL = 240, SDA hold value = 33, SCL Hold start = 118, SCL hold stop = 121
   // SDA hold time = bus period * mul * sda hold value
   //               =  42 ns     *  1  * 33  = 1.386 us
   // SCL start hold time = bus period * mul * scl start hold value
   //                             42   *  1  *  118  = 4.956 us
   // SCL stop hold time = bus period * mul * scl stop hold value
   //                             42   *  1  *  121  = 5.082 us

   // Write Frequency Divider register to set the i2c baud rate
   SET_BIT_IN_REG( I2C0_F, I2C_F_MULT( 0 ) | I2C_F_ICR( ICR_FOR_100khz_24MhzBus ) );
   // Write control register 1 to enable the i2c module and interrupts
   // Initialize ram varaibles ( IICEN = 1 and IICIE = 1 ) for transmit data
   SET_BIT_IN_REG( I2C0_C1, I2C_C1_IICEN_MASK | I2C_C1_MST_MASK );
}

I2C_Error I2C_SendData( uint8_t * data, uint8_t numBytes, uint8_t address )
{
   // Start with blocking, then move to interrupt driven.
   // Write: control register 1 to enable TX
   // Write: Address with LSB = 0
   // Wait for transfer complete flag
   // Write to transfer complete flag to clear it.
   // Start loop to begin transmission of the data
   // Write to data register
   // Wait for compeltion flag
   // Write to completion flag
}

I2C_Error I2C_ReadData( uint8_t * data, uint8_t address )
{
   // Write address with LSb = 0
   // Wait for tranfer complete flag
   // Write to transfer complete flag to clear it.
   // Write address with LSb = 1
   // Write control register to switch to RX

}
