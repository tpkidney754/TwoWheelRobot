#ifndef __I2C__
#define __I2C__

#include "includeall.h"

typedef enum
{
   I2C_NoError = 0,
   I2C_Error,
} I2C_Error;

typedef enum
{
   I2C_mul1 = 0,
   I2C_mul2,
   I2C_mul4,
} I2C_Multiplier;

#define ICR_VALUE    48
#define SLAVE_ADDR

I2C_Error I2C_Init( );
I2C_Error I2C_SendData( uint8_t * data );
I2C_Error I2C_ReadData( uint8_t * data );

#endif //__I2C__
