#include "adc.h"

static uint8_t ADC_value;

///*************************************************************************
/// Function:  ADC_Init                                                    *
///                                                                        *
/// Description: Initializes the adc wihh the corresponding adc channel    *
///                                                                        *
/// Parameters: ADC_InputChannel ADC_ch: The analog channel to being       *
///             initialized.                                               *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void ADC_Init( ADC_InputChannel ADC_ch )
{
   SET_BIT_IN_REG( SIM_SCGC5, ADC_PORT );
   SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_ADC0_MASK );
   SET_BIT_IN_REG( ADC_CH_PIN, PORT_PCR_MUX( MUX_PIN_ANALOG ) );
   SET_BIT_IN_REG( ADC0_CFG1, ADC_CFG1_ADLSMP_MASK );
   SET_BIT_IN_REG( ADC0_SC3, ADC_SC3_AVGE_MASK | ADC_SC3_AVGS( avg16Samples ) );
   ADC_value = 0;
}

///*************************************************************************
/// Function:  ADC_StartConversion                                         *
///                                                                        *
/// Description: Starts an analog to digital conversion and enables an     *
///              interrupt when the conversion is complete.                *
///                                                                        *
/// Parameters: ADC_InputChannel ADC_ch: The analog channel starting       *
///             conversion                                                 *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void ADC_StartConversion( ADC_InputChannel ADC_ch )
{
   NVIC_ClearPendingIRQ( ADC0_IRQn );
   NVIC_EnableIRQ( ADC0_IRQn );
   NVIC_SetPriority( ADC0_IRQn, 2 );
   SET_REG_VALUE( ADC0_SC1A, ADC_SC1_ADCH_MASK,
                             ADC_SC1_AIEN_MASK | ( ADC_ch & ADC_SC1_ADCH_MASK ) );
}

///*************************************************************************
/// Function:  ADC_GetCurrentValue                                         *
///                                                                        *
/// Description: Returns a floating point percentage the current value     *
///              from the last conversion value divided by the max value   *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
float ADC_GetCurrentValue( )
{
   return ( ADC_value / MAX_VALUE );
}

void ADC0_IRQHandler( )
{
   NVIC_DisableIRQ( ADC0_IRQn );

   if( ADC0_SC1A & ADC_SC1_COCO_MASK )
   {
      ADC_value = ( uint8_t ) ADC0_RA;
      return;
   }

   if( ADC0_SC1B & ADC_SC1_COCO_MASK )
   {
      ADC_value = ( uint8_t ) ADC0_RB;
      return;
   }

   NVIC_EnableIRQ( ADC0_IRQn );
}
