#include "messaging.h"

CircularBuffer_t * UART1_TXBuffer;

#ifdef FRDM
static void (*commands[ NUM_COMMANDS ] )( uint8_t input ) =
             { SwitchLEDs,
               ChangeLEDPW,
               Controller_SetCurrentTemp,
               Controller_ChangeDisplay,
               Controller_SetDesiredTemp,
               Controller_SetTempRange,
               Controller_SendTempData };
#endif

///*************************************************************************
/// Function:  BuildCommandMesage                                          *
///                                                                        *
/// Description: Takes a command number and the input value and creates    *
///              the message to be sent to the FRDM board.                 *
///                                                                        *
/// Parameters: Commands_e cmd: Command to be sent in the message.         *
///             uint8_t data: Input value of the command.                  *
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e BuildCommandMessage( Commands_e cmd, uint8_t data )
{
   CommandMessage_t msg;
   msg.cmd = cmd;
   msg.data = data;

   CalculateCommandChecksum( &msg );
#ifdef BBB
   return SendMessage( &msg );
#else
   return noError;
#endif
}

///*************************************************************************
/// Function:  CalculateCommandChecksum                                    *
///                                                                        *
/// Description: Creates the checksum for the command message.             *
///                                                                        *
/// Parameters: CommandMessage_t * msg: Pointer to a command message struct*
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e CalculateCommandChecksum( CommandMessage_t * msg )
{
   // The checksum is all the values of the struct XORed with eachother

   uint8_t checksum = 0;
   checksum = msg->cmd;
   checksum ^= msg->data;

   msg->checksum = checksum;

   return noError;
}

///*************************************************************************
/// Function:  CalculateTemperatureChecksum                                *
///                                                                        *
/// Description: Creates the checksum for the temperature data message.    *
///                                                                        *
/// Parameters: CommandMessage_t * msg: Pointer to a temperature data      *
///                                     message struct.                    *
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e CalculateTemperatureChecksum( TemperatureMessage_t * msg )
{
   uint8_t checksum = 0;
   checksum ^= msg->currentTemp;
   checksum ^= msg->currentDesired;
   checksum ^= msg->currentRange;
   checksum ^= msg->powerOn;

   msg->checksum = checksum;

   return noError;
}

#ifdef FRDM
///*************************************************************************
/// Function:  SendMessage                                                 *
///                                                                        *
/// Description: Adds the temperature data message to the UART circular    *
///              buffer.                                                   *
///                                                                        *
/// Parameters: TemperatureMessage_t * msg: Pointer to a temperature data  *
///                        message struct.                                 *
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e SendMessage( TemperatureMessage_t * msg )
{
   //UartTX( ( uint8_t * ) msg, TEMP_MSG_BYTES );
   if( CBufferAdd( UART1_TXBuffer, &(msg->currentTemp) , DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->currentDesired) , DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->currentRange), DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->powerOn), DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->checksum), DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->cr), DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( UART1_TXBuffer, &(msg->lf), DMACH_UART1TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   SET_BIT_IN_REG( UART1_C2, UART_C2_TIE_MASK );

}
#endif

#ifdef BBB
///*************************************************************************
/// Function:  SendMessage                                                 *
///                                                                        *
/// Description: Sends the command message through UART                    *
///                                                                        *
/// Parameters: CommandMessage_t * msg: Pointer to a temperature data      *
///                                     message struct.                    *
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e SendMessage( CommandMessage_t * msg )
{
   UartTX( ( uint8_t * ) msg, 3 );
}
#endif

///*************************************************************************
/// Function:  DecodeCommandMessage                                        *
///                                                                        *
/// Description: Parses the command message on the FRDM side and calls     *
///              the appropriate function from the commands function       *
///              pointer array.                                            *
///                                                                        *
/// Parameters: CommandMessage_t * msg: Received command message.          *
///             uint8_t data: Input value of the command.                  *
///                                                                        *
/// Return Value: MessagingErrors_e: Enumeration of messaging errors.      *
///                                                                        *
///*************************************************************************
MessagingErrors_e DecodeCommandMessage( CommandMessage_t * msg )
{
   // This is an excellent oppurtunity for implementing function pointers
   // when I get the time.
#ifdef FRDM
   if( msg->cmd < NUM_COMMANDS )
   {
      commands[ msg->cmd ]( msg->data );
   }
#endif
   return noError;
}
