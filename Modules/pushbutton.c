#include "pushbutton.h"

///*************************************************************************
/// Function:  Button_Init                                                 *
///                                                                        *
/// Description: Initializes the GPIO settings for a pushbutton.           *
///                                                                        *
/// Parameters: uint8_t buttonNum: Not currently being used but is         *
///             a placeholder if more than one pushbutton will be used in  *
///             the future.                                                *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void Button_Init( uint8_t buttonNum )
{
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   SET_BIT_IN_REG( BUTTON0, PORT_PCR_IRQC( IRQRising ) |
                            PORT_PCR_MUX( PIN_GPIO ) );
   CLEAR_BITS_IN_REG( GPIOC_PDOR, BUTTON0_PIN );
   CLEAR_BITS_IN_REG( GPIOC_PDDR, BUTTON0_PIN );
   NVIC_ClearPendingIRQ( PORTA_IRQn );
   NVIC_EnableIRQ( PORTA_IRQn );
   NVIC_SetPriority( PORTA_IRQn, 2 );
}

void PORTA_IRQHandler( )
{
   NVIC_DisableIRQ( PORTA_IRQn );
   //Software delay to debounce pushbutton.
   for( uint32_t i = 0; i < 1000000; i++ );
   if( BUTTON0 & PORT_PCR_ISF_MASK )
   {
      SET_BIT_IN_REG( BUTTON0, PORT_PCR_ISF_MASK );
      Controller_ChangeState( );
   }
   NVIC_EnableIRQ( PORTA_IRQn );
}
