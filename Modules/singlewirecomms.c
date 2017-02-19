#include "singlewirecomms.h"

///*************************************************************************
/// Function:  SWC_Init                                                    *
///                                                                        *
/// Description: Initializes the GPIO for SWC                              *
///                                                                        *
/// Parameters: NONE
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void SWC_Init( )
{
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   SET_BIT_IN_REG( PORTA_PCR5, PORT_PCR_MUX( PIN_GPIO ) );
}

///*************************************************************************
/// Function:  SWC_ResetAndPresencePulses                                  *
///                                                                        *
/// Description: Pulls the comms line low for 480 us to reset the bus. Then*
///              all slaves on the bus will pull line low after the master *
///              releases the line.                                        *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: uint8_t: Boolean indicating if a slave is present on the *
///                        bus.                                            *
///                                                                        *
///*************************************************************************
uint8_t SWC_ResetAndPresencePulses( )
{
   SWITCH_TO_TX;
   PULL_LOW;
   //Wait 480 us
   WaitInUs( 480 );
   RELEASE_LINE;
   SWITCH_TO_RX;
   // Once the slave detects the rising edge from the bus release,
   // it will wait 15-60 us and then pull the bus low itself.
   //Wait 60 us
   WaitInUs( 60 );
   // The bus will then pull the bus low for 60-240 us.
   for( uint8_t i = 0; i < 18; i++ )
   {
      if( READ_LINE == 0 )
      {
         while( READ_LINE == 0 );
         return 1;
      }
      else
      {
         WaitInUs( 10 );
      }
   }

   return 0;
   // If the bus is low then slave present.

}

///*************************************************************************
/// Function:  SWC_SendByte                                                *
///                                                                        *
/// Description: Bit bangs out a byte of data on the SWC bus.              *
///                                                                        *
/// Parameters: uint8_t data: Byte to be sent on the bus.                  *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void SWC_SendByte( uint8_t data )
{
   SWITCH_TO_TX;

   for( uint8_t i = 0; i < 8; i++ )
   {
      // To send a 1 to the device, the line is pulled low for 15 us, and then
      // released and left high for 45 us.
      if( data & 0x1 )
      {
         PULL_LOW;
         // Wait15us, changed to 13 because there is some delay.
         WaitInUs( 13 );
         RELEASE_LINE;
         // Wait45us, chagned to 41 for same reasons.
         WaitInUs( 41 );
      }
      // to send a 0, the line pulled low for the full 60 us window.
      else
      {
         PULL_LOW;
         // Wait60us
         WaitInUs( 57 );
         RELEASE_LINE;
      }
      // After each bit, a one us recovery time is required.
      // wait 1us
      data >>= 1;
      WaitInUs( 1 );
   }
}

///*************************************************************************
/// Function:  SWC_ReadData                                                *
///                                                                        *
/// Description: Reads data on the bus. Each read window is initiated by   *
///              the master by pulling the line low for 1 us and then      *
///              released. Wait 15 us and then sample when the data from   *
///              the slave will be valid. If the bit is 1, then the slave  *
///              will release the line high, and keep it low if the bit is *
///              a zero.                                                   *
///                                                                        *
/// Parameters: uint8_t bytesToRead: Number of bytes that will be read     *
///             uint8_t * data: Pointer to a data buffer where the read    *
///                             data is to be placed.                      *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void SWC_ReadData( uint8_t bytesToRead, uint8_t * data )
{
   uint8_t tempData;

   for( uint8_t i = 0; i < bytesToRead; i++ )
   {
      for( uint8_t j = 0; j < 8; j++ )
      {
         SWITCH_TO_TX;
         PULL_LOW;
         // wait 1us
         WaitInUs( 1 );
         RELEASE_LINE;
         SWITCH_TO_RX;
         // Wait 15us
         WaitInUs( 13 );

         if( READ_LINE )
         {
            tempData |= ( 1 << j );
         }

         //wait 45us
         WaitInUs( 41 );
      }
      data[ i ] = tempData;
      tempData = 0;
   }
}

///*************************************************************************
/// Function:  SWC_ReadStatusAndWait                                       *
///                                                                        *
/// Description: Sometimes the slave will keep the line low while it       *
///              working a certain task.                                   *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void SWC_ReadStatusAndWait( )
{
   SWITCH_TO_TX;
   PULL_LOW;
   // Wait 1us
   WaitInUs( 1 );
   RELEASE_LINE;
   SWITCH_TO_RX;
   // wait 15us
   WaitInUs( 15 );
   while( READ_LINE == 0 );
}
