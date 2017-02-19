#ifdef TESTING
#include "testing.h"

static uint8_t fillerChar[ 3 ] = { '*', '@', '~' };

///*************************************************************************
/// Function:  Testing                                                     *
///                                                                        *
/// Description: Main function that calls all individual test suite.       *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void Testing()
{
#ifdef FRDM
   InitDMA( TESTING_DMA_CH );
#endif
   DataTesting();
   MemoryTesting();
   CircularBufferTesting();
   PerformanceTesting();
}

///*************************************************************************
/// Function:  PrintHeader                                                 *
///                                                                        *
/// Description: A string is passed in and a header type. The type will    *
///              dictate the filler characters surrounding the header      *
///              sting.                                                    *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void PrintHeader( uint8_t * header, HeaderType_t headerType )
{
   if( headerType == pass_e )
   {
      strcat( header, " Passed Successfully!" );
   }
   else if( headerType == fail_e )
   {
      strcat( header, " Failed!" );
   }

   uint8_t fillerLength = HEADER_LENGTH - MyStrLen( header ) - 2;
   fillerLength /= 2;
   uint8_t * filler = malloc( sizeof( uint8_t ) * fillerLength + 1 );
   MyMemSet( filler, 0, fillerLength + 1, TESTING_DMA_CH );

   for( uint32_t i = 0; i < fillerLength; i++ )
   {
      filler[i] = fillerChar[ headerType ];
   }

   sprintf( testPrintBuffer, "\n%s %s %s\n", filler, header, filler );
   LOG0( testPrintBuffer );
   free( filler );
}

#endif
