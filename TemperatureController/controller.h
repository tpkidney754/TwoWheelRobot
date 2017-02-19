#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "includeall.h"


#define MAX_DISPLAY_VAL          99
#define CONVERT_C_TO_F( tc )     ( tc ) = ( ( tc ) * 9 / 5 ) + 32
#define CONVERT_F_TO_C( tf )     ( tf ) = ( ( tf ) - 32 ) * 5 / 9

#define RELAY        PORTC_PCR9
#define RELAY_PIN    0x00000200

#define RELAY_ON    SET_BIT_IN_REG( GPIOC_PSOR, RELAY_PIN )
#define RELAY_OFF   SET_BIT_IN_REG( GPIOC_PCOR, RELAY_PIN )

typedef enum
{
   noChange = 0,
   changeDesiredTemp,
   changeTempRange,
   printSettings,
} ControllerState_e;

void Controller_Init( );
void Controller_StateMachine( );
void Controller_ChangeState( );
void Controller_SetCurrentTemp( uint8_t newTemp );
void Controller_SetDesiredTemp( uint8_t newTemp );
void Controller_SetTempRange( uint8_t newRange );
void Controller_ChangeDisplay( uint8_t value );
void Controller_SendTempData( uint8_t dontcare );

#endif //__CONTROLLER__
