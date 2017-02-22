#ifndef __I2C__
#define __I2C__

#include "includeall.h"

typedef enum
{
   I2C_NoError = 0,
   I2C_ChoosenFreqTooHigh,
   I2C_GeneralError,
} I2C_Error;

typedef enum
{
   I2C_mul1 = 0,
   I2C_mul2,
   I2C_mul4,
} I2C_Multiplier;

#define I2C_MAX_SPEED   100

#define MULT_FOR_100khz_24MhzBus 0
#define ICR_FOR_100khz_24MhzBus  0x1F

I2C_Error I2C_Init( );
I2C_Error I2C_SendData( uint8_t * data );
I2C_Error I2C_ReadData( uint8_t * data );

#endif //__I2C__
