#include "diags.h"

///*************************************************************************
/// Function:  ParseDiag                                                   *
///                                                                        *
/// Description: Receives a string signifying a diag command from          *
///              the serial port.                                          *
///                                                                        *
/// Parameters: uint8_t * buffer: pointer to a string buffer.              *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void ParseDiag( uint8_t * buffer )
{
   // Support up to four commands with 10 characters each.
   uint8_t commands[ 4 ][ 10 ];
   size_t length;
   size_t i = 0;
   uint8_t * currentCommand;

   currentCommand = strtok( buffer, "\n " );

   while( currentCommand != NULL )
   {
      strcpy( commands[ i++ ], currentCommand );
      currentCommand = strtok( NULL, "\n " );
   }

   length = MyStrLen( commands[ i - 1 ] );
   commands[ i - 1 ][ length ] = '\0';

   i = 0;

   if( strstr( commands[ i ], "set" ) )
   {
      i++;
      if( strstr( commands[ i ], "color" ) )
      {
         i++;
         Color_t color = NONE;
         if( strstr( commands[ i ], "red" ) )
         {
            color = RED;
         }
         else if( strstr( commands[ i ], "green" ) )
         {
            color = GREEN;
         }
         else if( strstr( commands[ i ], "blue" ) )
         {
            color = BLUE;
         }
         else if( strstr( commands[ i ], "purple" ) )
         {
            color = PURPLE;
         }
         else if( strstr( commands[ i ], "yellow" ) )
         {
            color = YELLOW;
         }
         else if( strstr( commands[ i ], "cyan") )
         {
            color = CYAN;
         }
         else if( strstr( commands[ i ], "white" ) )
         {
            color = WHITE;
         }
         else if( strstr( commands[ i ], "off" ) )
         {
            color = OFF;
         }
         else
         {
            LOG0( "Invalid color given\n" );
         }

      #if ENABLE_MESSAGING
         BuildCommandMessage( changeColor, ( uint8_t ) color );
      #else
         SwitchLEDs( ( uint8_t ) color );
      #endif
      }
      else if ( strstr( commands[ i ], "power" ) )
      {
         i++;
         uint32_t pulseWidth;
         pulseWidth = MyAtoi( commands[ i ] );
      #if ENABLE_MESSAGING
         BuildCommandMessage( changePWM, ( uint8_t ) pulseWidth );
      #else
         ChangeLEDPW( ( uint8_t ) pulseWidth );
      #endif
      }
      else if( strstr( commands[ i ], "display" ) )
      {
         i++;
         if( strstr( commands[ i ], "cycle" ) )
         {
            for( uint8_t i = 0; i < 100; i++ )
            {
            #if ENABLE_MESSAGING
               BuildCommandMessage( setDisplay, ( uint8_t ) i );
            #else
               UpdateDisplay( 0, ( uint8_t ) ( i / 10 ) );
               UpdateDisplay( 1, ( uint8_t ) ( i % 10 ) );
            #endif
               for( uint32_t j = 0; j < 100000000; j++ );
            }
         }
         else
         {
            uint32_t value = MyAtoi( commands[ i ] );
         #if ENABLE_MESSAGING
            BuildCommandMessage( setDisplay, ( uint8_t ) value );
         #else
            UpdateDisplay( 0, ( uint8_t ) ( value / 10 ) );
            UpdateDisplay( 1, ( uint8_t ) ( value % 10 ) );
         #endif
         }
      }
      else if( strstr( commands[ i ], "temp" ) )
      {
         i++;
         uint32_t newTemp;
         newTemp = MyAtoi( commands[ i ] );
      #if ENABLE_MESSAGING
         BuildCommandMessage( setTemp, ( uint8_t ) newTemp );
      #else
         Controller_SetCurrentTemp( newTemp );
      #endif
      }
      else if( strstr( commands[ i ], "desired" ) )
      {
         i++;
         uint32_t newDesTemp = MyAtoi( commands[ i ] );
      #if ENABLE_MESSAGING
         BuildCommandMessage( setDesired, ( uint8_t ) newDesTemp );
      #else
         Controller_SetDesiredTemp( ( uint8_t ) newDesTemp );
      #endif
      }
      else if( strstr( commands[ i ], "range" ) )
      {
         i++;
         uint32_t newRange = MyAtoi( commands[ i ] );
      #if ENABLE_MESSAGING
         BuildCommandMessage( setRange, ( uint8_t ) newRange );
      #else
         Controller_SetTempRange( ( uint8_t ) newRange );
      #endif
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
   else if( strstr( commands[ i ], "read" ) )
   {
      i++;
   #ifdef FRDM
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint32_t reg = MyAtoi( commands[ i ] );
         nRF24L01_ReadReg( 0, reg );
      }
      else if( strstr( commands[ i ], "temp" ) )
   #else
      if( strstr( commands[ i ], "temp" ) )
   #endif
      {
         BuildCommandMessage( readTempData, 0 );
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
#ifdef FRDM
   else if( strstr( commands[ i ], "send" ) )
   {
      i++;
      if( strstr( commands[ i ], "nop" ) )
      {
         nRF24L01_SendNOP( 0 );
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
   else if( strstr( commands[ i ], "write" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint32_t reg = MyAtoi( commands[ i++ ] );
         uint32_t value = MyAtoi( commands[ i ] );
         nRF24L01_WriteReg( 0, reg, value );

      }
   }
#endif
}
