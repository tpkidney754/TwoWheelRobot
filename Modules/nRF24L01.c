#include "nRF24L01.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];
uint8_t readRegComplete;

///*************************************************************************
/// Function:  nRF24L01_Activate                                           *
///                                                                        *
/// Description: Sets up a msg that will be sent to the nRF24L01 module    *
///              that will activate the device. The command sets the       *
///              R_RX_PL_WID, W_ACK_PAYLOAD, and W_TX_PAYLOAD_NOACK        *
///              features. Also this will set up the CE and IRQ pins.      *
///                                                                        *
/// Parameters: uint8_t SPI_ch: The spi channel being used.                *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_Activate( uint8_t SPI_ch )
{
#ifdef FRDM
   if( SPI_ch == 0 )
   {
      SET_BIT_IN_REG( nRF24L01_0_CE, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( nRF24L01_0_IRQ, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( GPIOC_PDDR, nRF24L01_0_CE_PIN );
   }
   else
   {
      SET_BIT_IN_REG( nRF24L01_1_CE, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( nRF24L01_1_IRQ, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( GPIOE_PDDR, nRF24L01_1_CE_PIN );
   }
#endif
   nRF24L01_SPIMessage_t msg;
   msg.command = ACTIVATE;
   msg.spiCh = SPI_ch;
   msg.data[ 0 ] = ACTIVATE_KEY;
   msg.bytesToSend = 1;

   nRF24L01_SendData( &msg );
}

///*************************************************************************
/// Function:  nRF24L01_ReadReg                                            *
///                                                                        *
/// Description: Sets up a msg that will be sent to the nRF24L01 module    *
///              that will read a register on the device.                  *
///                                                                        *
/// Parameters: uint8_t SPI_ch: The spi channel being used.                *
///             nRF24L01_Registers_e reg: Register to be read.             *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_ReadReg( uint8_t SPI_ch, nRF24L01_Registers_e reg )
{
   nRF24L01_SPIMessage_t msg;

   msg.spiCh = SPI_ch;
   msg.command = READ_REG( reg );

   switch( reg )
   {
      // These three addresses are 5 bytes wide,
      // so 1 byte is sent to read register, then
      // 5 nops are sent to read back register. All other
      // registers are a single byte.
      case RX_ADDR_P0:
      case RX_ADDR_P1:
      case TX_ADDR:
         msg.bytesToSend = 5;
         for( int8_t i = 0; i < msg.bytesToSend - 1; i++ )
         {
            msg.data[ i ] = msg.command;
         }
         break;
      default:
         msg.bytesToSend = 1;
         msg.data[ 0 ] = NOP;
   }

   nRF24L01_SendData( &msg );
}

///*************************************************************************
/// Function:  nRF24L01_WriteReg                                           *
///                                                                        *
/// Description: Sets up a msg that will be sent to the nRF24L01 module    *
///              that will write a value to a register on the device.      *
///                                                                        *
/// Parameters: uint8_t SPI_ch: The spi channel being used.                *
///             nRF24L01_Registers_e reg: Register to be written to.       *
///             uint8_t dataToWrite: value to be written to register       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite )
{
   nRF24L01_SPIMessage_t msg;

   msg.spiCh = SPI_ch;
   msg.command = WRITE_REG( reg );
   msg.bytesToSend = 1;
   msg.data[ 0 ] = dataToWrite;

   nRF24L01_SendData( &msg );
}

///*************************************************************************
/// Function:  nRF24L01_SendData                                           *
///                                                                        *
/// Description: Receives a msg structure and then adds that msg to the    *
///              circular buffer used for SPI transmissions.               *
///                                                                        *
/// Parameters: nRF24L01_SPIMessage_t * msg: pointer to the message struct *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_SendData( nRF24L01_SPIMessage_t * msg )
{
   uint8_t data;

   data = msg->command;
   CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data, NO_DMA );

   for( int8_t i = 0; i < msg->bytesToSend; i++ )
   {
      data = msg->data[ i ];
      CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data, NO_DMA );
   }

   SPI_TransmitData( msg->spiCh, msg->bytesToSend + 1 );
}

///*************************************************************************
/// Function:  nRF24L01_SetTXMode                                          *
///                                                                        *
/// Description: Sets up the nRF24L01 in TX mode                           *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_SetTXMode( uint8_t SPI_ch )
{
   nRF24L01_WriteReg( SPI_ch, CONFIG, PWR_UP_MASK );
   // Sets CE pin high
#if FRDM
   SPI_ch == 0 ? SET_BIT_IN_REG( GPIOC_PSOR, nRF24L01_0_CE_PIN ) :
                 SET_BIT_IN_REG( GPIOE_PSOR, nRF24L01_1_CE_PIN );
#endif
}

///*************************************************************************
/// Function:  nRF24L01_SetRXMode                                          *
///                                                                        *
/// Description: Sets up the nRF24L01 in RX mode                           *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_SetRXMode( uint8_t SPI_ch )
{
   nRF24L01_WriteReg( SPI_ch, CONFIG, ( PWR_UP_MASK | PRIM_RX_MASK ) );
   // Sets CE pin high
#if FRDM
   SPI_ch == 0 ? SET_BIT_IN_REG( GPIOC_PSOR, nRF24L01_0_CE_PIN ) :
                 SET_BIT_IN_REG( GPIOE_PSOR, nRF24L01_1_CE_PIN );
#endif
}

///*************************************************************************
/// Function:  nRF24L01_StandbyMode                                        *
///                                                                        *
/// Description: Sets up the nRF24L01 in RX mode                           *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_StandbyMode( uint8_t SPI_ch )
{
   nRF24L01_WriteReg( SPI_ch, CONFIG, PWR_UP_MASK );
   // Sets CE pin high
#if FRDM
   SPI_ch == 0 ? SET_BIT_IN_REG( GPIOC_PCOR, nRF24L01_0_CE_PIN ) :
                 SET_BIT_IN_REG( GPIOE_PCOR, nRF24L01_1_CE_PIN );
#endif
}

///*************************************************************************
/// Function:  nRF24L01_PowerDown                                          *
///                                                                        *
/// Description: Sets up the nRF24L01 in RX mode                           *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_PowerDown( uint8_t SPI_ch )
{
   nRF24L01_WriteReg( SPI_ch, CONFIG, 0 );
   // Sets CE pin high
#if FRDM
   SPI_ch == 0 ? SET_BIT_IN_REG( GPIOC_PCOR, nRF24L01_0_CE_PIN ) :
                 SET_BIT_IN_REG( GPIOE_PCOR, nRF24L01_1_CE_PIN );
#endif
}

///*************************************************************************
/// Function:  nRF24L01_SetupChannel                                       *
///                                                                        *
/// Description: Sets up the nRF24L01 transmission channel.                *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_SetupChannel( uint8_t SPI_ch )
{
   nRF24L01_WriteReg( SPI_ch, RF_CH, nRF24L01_CHANNEL_FREQ );
   nRF24L01_WriteReg( SPI_ch, RF_SETUP, ( nRF24L01_DATA_RATE | nRF24L01_PA_CONTROL ) );
}

///*************************************************************************
/// Function:  nRF24L01_SendNOP                                            *
///                                                                        *
/// Description: Sends a NOP command to the nRF24L01 device                *
///                                                                        *
/// Parameters: uint8_t SPI_ch: SPI channel being used.                    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void nRF24L01_SendNOP( uint8_t SPI_ch )
{
   nRF24L01_SPIMessage_t msg;
   msg.command = NOP;
   msg.bytesToSend = 0;
   msg.spiCh = SPI_ch;

   nRF24L01_SendData( &msg );
}
