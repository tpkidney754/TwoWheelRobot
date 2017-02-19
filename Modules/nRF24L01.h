#ifndef __NRF24L01__
#define __NRF24L01__

#include "includeall.h"

// SPI Commands to nRF24L01
#define READ_REG( reg )       ( uint8_t ) ( ( reg ) & 0x1F )
#define WRITE_REG( reg )      ( uint8_t ) ( 0x20 | ( reg ) & 0x1F )
#define R_RX_PAYLOAD            0x61
#define W_TX_PAYLOAD            0xA0
#define FLUSH_TX                0xE1
#define FLUSH_RX                0xE2
#define REUSE_TX_PL             0xE3
#define ACTIVATE                0x50
#define ACTIVATE_KEY            0x73
#define R_RX_PL_WID             0x60
#define W_ACK_PAYLOAD( ppp )  ( 0xA8 | ( ( ppp ) & 0x7 ) )
#define W_TX_PAYLOAD_NO_ACK     0xB0
#define NOP                     0xFF

// The CE and IRQ pins to/from the nRF24L01
#define nRF24L01_0_CE         PORTC_PCR0
#define nRF24L01_0_CE_PIN     0x0001
#define nRF24L01_0_IRQ        PORTC_PCR3
#define nRF24L01_0_IRQ_PIN    0x0008

#define nRF24L01_1_CE         PORTE_PCR0
#define nRF24L01_1_CE_PIN     0x0001
#define nRF24L01_1_IRQ        PORTE_PCR5
#define nRF24L01_1_IRQ_PIN    0x0020

typedef enum
{
   ADR_1Mbps = 0,
   ADR_2Mbps,
} ADR_e;

typedef enum
{
   PWR_neg18dBm = 0,
   PWR_neg12dBm,
   PWR_neg6dBm,
   PWR_0dBm,
} PWR_e;

// Using 10 channels set up at 2.400 GHz, 2.410 GHz, 2.420 GHz and so on.
typedef enum
{
   CHANNEL_0 = 0,
   CHANNEL_1 = 10,
   CHANNEL_2 = 20,
   CHANNEL_3 = 30,
   CHANNEL_4 = 40,
   CHANNEL_5 = 50,
   CHANNEL_6 = 60,
   CHANNEL_7 = 70,
   CHANNEL_8 = 80,
   CHANNEL_9 = 90,
} CHANNEL_e;

#define nRF24L01_DATA_RATE        ( ADR_1Mbps << 3 )
#define nRF24L01_PA_CONTROL       ( PWR_neg18dBm << 1 )
#define nRF24L01_CHANNEL_FREQ     CHANNEL_0
#define nRF24L01_LNA_GAIN         0

typedef struct
{
   uint8_t spiCh;
   uint8_t command;
   uint8_t data[ 6 ];
   uint8_t bytesToSend;
} nRF24L01_SPIMessage_t;

// Registers
typedef enum
{
   CONFIG = 0x0,
   EN_AA,
   EN_RXADDR,
   SETUP_AW,
   SETUP_RETR,
   RF_CH,
   RF_SETUP,
   STATUS,
   OBSERVE_TX,
   CD,
   RX_ADDR_P0,
   RX_ADDR_P1,
   RX_ADDR_P2,
   RX_ADDR_P3,
   RX_ADDR_P4,
   RX_ADDR_P5,
   TX_ADDR,
   RX_PW_P0,
   RX_PW_P1,
   RX_PW_P2,
   RX_PW_P3,
   RX_PW_P4,
   RX_PW_P5,
   FIFO_STATUS,
   DYNPD = 0x1C,
   FEATURE,
} nRF24L01_Registers_e;

typedef union
{
   struct
   {
      uint8_t primRx    :1;
      uint8_t pwrUp     :1;
      uint8_t crco      :1;
      uint8_t enCRC     :1;
      uint8_t maskMaxRt :1;
      uint8_t maskTxDs  :1;
      uint8_t maskRxDr  :1;
      uint8_t reserved  :1;
   } b;
   uint8_t B;
} nRF24L01_CONFIG_t;

#define PRIM_RX_MASK      0x01
#define PWR_UP_MASK       0x02
#define CRCO_MASK         0x04
#define EN_CRC_MASK       0x08
#define MASK_MAX_RT_MASK  0x10
#define MASK_TX_DS_MASK   0x20
#define MASK_RX_DR_MASK   0x40

typedef union
{
   struct
   {
      uint8_t enaaP0    :1;
      uint8_t enaaP1    :1;
      uint8_t enaaP2    :1;
      uint8_t enaaP3    :1;
      uint8_t enaaP4    :1;
      uint8_t enaaP5    :1;
      uint8_t reserved :2;
   } b;
   uint8_t B;
} nRF24L01_ENAA_t;

typedef union
{
   struct
   {
      uint8_t erxP0    :1;
      uint8_t erxP1    :1;
      uint8_t erxP2    :1;
      uint8_t erxP3    :1;
      uint8_t erxP4    :1;
      uint8_t erxP5    :1;
      uint8_t reserved :2;
   } b;
   uint8_t B;
} nRF24L01_EN_RXADDR_t;

typedef union
{
   struct
   {
      uint8_t aw       :2;
      uint8_t reserved :6;
   } b;
   uint8_t B;
} nRF24L01_SETUP_AW_t;

typedef union
{
   struct
   {
      uint8_t arc      :4;
      uint8_t ard      :4;
   } b;
   uint8_t B;
} nRF24L01_SETUP_RETR_t;

typedef union
{
   struct
   {
      uint8_t rfch     :7;
      uint8_t reserved :1;
   } b;
   uint8_t B;
} nRF24L01_RF_CH_t;

typedef union
{
   struct
   {
      uint8_t lnaHCURR    :1;
      uint8_t rfPWR       :2;
      uint8_t rfDR        :1;
      uint8_t pllLock     :1;
      uint8_t reserved    :3;
   } b;
   uint8_t B;
} nRF24L01_RF_SETUP_t;

typedef union
{
   struct
   {
      uint8_t txFull         :1;
      uint8_t rxPno          :3;
      uint8_t maxRT          :1;
      uint8_t txDS           :1;
      uint8_t rxDR           :1;
      uint8_t reserved       :1;
   } b;
   uint8_t B;
} nRF24L01_STATUS_t;

typedef union
{
   struct
   {
      uint8_t arcCNT  :4;
      uint8_t plosCNT :4;
   } b;
   uint8_t B;
} nRF24L01_OBSERVE_TX_t;

typedef union
{
   struct
   {
      uint8_t rxPwP0    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P0_t;

typedef union
{
   struct
   {
      uint8_t rxPwP1    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P1_t;

typedef union
{
   struct
   {
      uint8_t rxPwP2    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P2_t;

typedef union
{
   struct
   {
      uint8_t rxPwP3    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P3_t;

typedef union
{
   struct
   {
      uint8_t rxPwP4    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P4_t;

typedef union
{
   struct
   {
      uint8_t rxPwP5    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P5_t;

typedef union
{
   struct
   {
      uint8_t rxEmpty   :1;
      uint8_t rxFull    :1;
      uint8_t reserved0 :2;
      uint8_t txEmpty   :1;
      uint8_t txFull    :1;
      uint8_t txReuse   :1;
      uint8_t reserved1 :1;
   }b;
   uint8_t B;
} nRF24L01_FIFO_STATUS_t;

typedef union
{
   struct
   {
      uint8_t dplP0       :1;
      uint8_t dplP1       :1;
      uint8_t dplP2       :1;
      uint8_t dplP3       :1;
      uint8_t dplP4       :1;
      uint8_t dplP5       :1;
      uint8_t reserved    :1;
   }b;
   uint8_t B;
} nRF24L01_DYNPD_t;

typedef union
{
   struct
   {
      uint8_t enDynAck          :1;
      uint8_t enAckPay          :1;
      uint8_t enDpl             :1;
      uint8_t reserved          :5;
   }b;
   uint8_t B;
} nRF24L01_FEATURE_t;

void nRF24L01_Activate( uint8_t SPI_ch );
void nRF24L01_ReadReg( uint8_t SPI_ch, nRF24L01_Registers_e reg );
void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite );
void nRF24L01_SendData( nRF24L01_SPIMessage_t * msg );
void nRF24L01_SetTXMode( uint8_t SPI_ch );
void nRF24L01_SetRXMode( uint8_t SPI_ch );
void nRF24L01_StandbyMode( uint8_t SPI_ch );
void nRF24L01_PowerDown( uint8_t SPI_ch );
void nRF24L01_SetupChannel( uint8_t SPI_ch );
void nRF24L01_SendNOP( uint8_t SPI_ch );

#endif // __NRF24L01__
