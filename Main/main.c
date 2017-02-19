#include "includeall.h"

extern CircularBuffer_t * UART0_RXBuffer;
extern CircularBuffer_t * UART0_TXBuffer;
extern CircularBuffer_t * UART1_RXBuffer;
extern CircularBuffer_t * UART1_TXBuffer;
extern CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
extern CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

int main()
{
   UartSetup( 0, 57600, 0 );
#ifdef FRDM
   UartSetup( 1, 115200, 0 );
   LEDSetup();
   InitDisplay( 0 );
   InitDisplay( 1 );
   ADC_Init( ADC_CHANNEL );
   Button_Init( 0 );
   Controller_Init( );
   InitWaitTimer( );
   SWC_Init( );
   float temperature = 0;
   temperature = ReadTemp( );
   Controller_SetCurrentTemp( temperature );
#endif

#ifdef TESTING
   //Testing();
#endif

   uint8_t buffer[ 100 ];
   uint32_t length = 0;
   uint8_t readTempData = 0;
   CommandMessage_t cmdmsg;
   TemperatureData tempData;

#ifdef FRDM
while( 1 )
{
#ifndef TESTING
   Controller_StateMachine( );
   Controller_SetCurrentTemp( ReadTemp( ) );
#endif //TESTING
   if( UART1_RXBuffer->numItems == COMMAND_MSG_BYTES )
   {
      CBufferRemove( UART1_RXBuffer, &cmdmsg.cmd, DMACH_UART1RX  );
      CBufferRemove( UART1_RXBuffer, &cmdmsg.data, DMACH_UART1RX );
      CBufferRemove( UART1_RXBuffer, &cmdmsg.checksum, DMACH_UART1RX );

      DecodeCommandMessage( &cmdmsg );

      parseDiag = 0;
   }

#else
#ifdef TESTING
while( 1 )
{
   printf( "Enter command: " );
#else
{
#endif
   fgets( buffer, 100, stdin );
   length = MyStrLen( buffer );
   if( strstr( buffer, "read temp" ) )
   {
      readTempData = 1;
   }

   ParseDiag( buffer );

   if( readTempData )
   {
      for( int32_t i = 0; i < 100000; i++ );
      while( UartRX( ( uint8_t * ) &tempData.data ) <= 0 );

      printf( "%d,%d,%d,%s",
               tempData.msg.currentTemp,
               tempData.msg.currentDesired,
               tempData.msg.currentRange,
               tempData.msg.powerOn ? "ON" : "OFF" );

      readTempData = 0;
   }
#endif
}

return 0;
}
