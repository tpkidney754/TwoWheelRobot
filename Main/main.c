#include "includeall.h"

extern CircularBuffer_t * UART0_RXBuffer;
extern CircularBuffer_t * UART0_TXBuffer;

extern CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
extern CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

int main()
{
   UartSetup( 0, 57600, 0 );
#ifdef FRDM
   LEDSetup();
   I2C_Init( 0, 0 );
   // Will be using the ADC later on, just not now.
   //ADC_Init( ADC_CHANNEL );
#endif

#ifdef TESTING
   Testing();
#endif

   uint8_t buffer[ 100 ];
   uint32_t length = 0;
   uint8_t readTempData = 0;
   CommandMessage_t cmdmsg;
   TemperatureData tempData;

#ifdef FRDM
   while( 1 )
   {
      if( parseDiag )
      {
         length = UART0_RXBuffer->numItems;
         for( size_t i = 0; i < length; i++ )
         {
            CBufferRemove( UART0_RXBuffer, &buffer[ i ], DMACH_UART0TX );
         }

         ParseDiag( buffer );
         parseDiag = 0;
      }

   }
#endif
   return 0;
}
