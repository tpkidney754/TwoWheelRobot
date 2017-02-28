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
   uint8_t commands[ 6 ][ 10 ];
   size_t length;
   size_t i = 0;
   uint8_t * currentCommand;

   currentCommand = strtok( buffer, "\n " );

   while( currentCommand != NULL )
   {
      strcpy( commands[ i++ ], currentCommand );
      currentCommand = strtok( NULL, "\n " );
   }
   i--;
   length = MyStrLen( commands[ i ] );
   commands[ i ][ length - 1 ] = '\0';

   i = 0;
#ifdef FRDM
   if( strstr( commands[ i ], "write" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint8_t buffer0[ 40 ];
         uint8_t data[ 2 ];
         uint8_t reg = MyAtoi( commands[ i ] );
         i++;
         uint8_t numBytes = MyAtoi( commands[ i ] );
         i++;
         for( uint8_t j = 0; j < numBytes; j++ )
         {
            numBytes = MyAtoi( commands[ i ] );
         }
         if( numBytes > 1 )
         {
            I2C_SendData( reg, numBytes, data, LSM9DS1_ACCELGYRO_ADDR );
         }
         else
         {
            I2C_SendByte( reg, data, LSM9DS1_ACCELGYRO_ADDR );
         }
         sprintf( buffer0, "Wrote to reg 0x%X\n", reg );
         LOG0( buffer0 );
      }
   }
   else if( strstr( commands[ i ], "read" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint8_t buffer0[ 40 ];
         uint8_t reg = MyAtoi( commands[ i ] );
         i++;
         uint8_t numBytes = MyAtoi( commands[ i ] );
         uint8_t returnedValue[ 20 ];

         if(  numBytes == 1 )
         {
            I2C_ReadByte( reg, returnedValue, LSM9DS1_ACCELGYRO_ADDR );
            sprintf( buffer0, "Returned value from register 0x%X is 0x%x\n", reg, returnedValue[ 0 ] );
            LOG0( buffer0 );
         }
         else
         {
            I2C_ReadData( reg, returnedValue, numBytes, LSM9DS1_ACCELGYRO_ADDR );
            for( uint8_t j = 0; j < numBytes; j++ )
            {
               sprintf( buffer0, "Returned value from register 0x%X is 0x%x\n", reg + j, returnedValue[ j ] );
               LOG0( buffer0 );
            }
         }
      }

   }
   else if( strstr( commands[ i ], "send" ) )
   {
      i++;
   }
   else if( strstr( commands[ i ], "write" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {

      }
   }
#endif
}
