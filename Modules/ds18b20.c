#include "ds18b20.h"

/*  All transactions must follow these steps
 *  1. Initialization/reset
 *  2. ROM Command followed by any required data exchange
 *  3. Function Command followed by any required data exchange
 */

///*************************************************************************
/// Function:  TransactionStepOne                                          *
///                                                                        *
/// Description: Simply calls the first step of the ds18b20 tranaction     *
///              which is the Single Wire Comms Reset and precence pusle   *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: uint8: Boolean to indicate if a presence pulse was       *
///                      received.                                         *
///                                                                        *
///*************************************************************************
uint8_t TransactionStepOne( )
{
   return SWC_ResetAndPresencePulses( );
}

///*************************************************************************
/// Function:  TransactionStepTwo                                          *
///                                                                        *
/// Description: The second part of every ds18b20 transaction is a ROM     *
///              command and then reading the data coming from the device. *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void TransactionStepTwo( )
{
   DS8B20_ROMCode romCode;
   SWC_SendByte( READ_ROM );
   WaitInUs( WAIT_TIME_LONG );
   SWC_ReadData( ROM_BYTES, ( uint8_t * ) &romCode );
}

///*************************************************************************
/// Function:  ReadTemp                                                    *
///                                                                        *
/// Description: Completes two different transactions to the ds18b20.      *
///              The first transaction is starting a temperature conversion*
///              which then places the result in the scratchpad. The second*
///              transaction is to read the scratchpad data to retrieve the*
///              result of the temperate reading.                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: float: The floating point value of the temperature result*
///                                                                        *
///*************************************************************************
float ReadTemp( )
{
   DS8B20_Scratchpad scratchpadData;
   uint8_t devicePresent = TransactionStepOne( );
   uint16_t rawTemperatureData;

   if( devicePresent == 0 )
   {
      return 0x0;
   }
   WaitInUs( WAIT_TIME_SHORT );
   TransactionStepTwo ( );
   // Send the CONVERT_T command byte
   SWC_SendByte( CONVERT_T );
   // The DS18B20 will transmit a 0 while the conversion
   // is in progress and a 1 when the conversion is complete.
   // The master can issue a read time slot to read the status
   // of the conversion.
   //SWC_ReadStatusAndWait( );
   WaitInUs( WAIT_TIME_LONG );
   TransactionStepOne( );
   WaitInUs( WAIT_TIME_SHORT );
   TransactionStepTwo( );
   WaitInUs( WAIT_TIME_SHORT );
   SWC_SendByte( READ_SCRATCHPAD );
   WaitInUs( WAIT_TIME_LONG );
   SWC_ReadData( SCRATCPAD_BYTES, ( uint8_t * ) &scratchpadData );

   rawTemperatureData = scratchpadData.temperatureRawLSB;
   rawTemperatureData |= scratchpadData.temperatureRawMSB << 8;

   return ConvertRawTemperatureData( rawTemperatureData );
}

///*************************************************************************
/// Function:  ConvertRawTemperatureData                                   *
///                                                                        *
/// Description: The raw temperature data needs to be converted to a value *
///              that can be understood by the processor. The lowest nibble*
///              is the fractional part of the temperature. The next byte  *
///              is the whole part but with the most signficant bit is sign*
///              extended to the MSB of the half word.                     *
///                                                                        *
/// Parameters: uint16_t rawTemperatureData: The raw temperature data that *
///             needs to be converted to a floating point value.           *
///                                                                        *
/// Return Value: float: The floating point value of the temperature result*
///                                                                        *
///*************************************************************************
float ConvertRawTemperatureData( uint16_t rawTemperatureData )
{
   float temperature;

   temperature = ( rawTemperatureData & 0x07F0 ) >> 4;

   if( ( rawTemperatureData & 0x000F ) >> 3 )
   {
      temperature += 0.5;
   }

   if( ( rawTemperatureData & 0xF000 ) >> 15 )
   {
      temperature *= -1;
   }

   return temperature;
}
