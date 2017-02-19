#ifndef __SPI__
#define __SPI__

#include "includeall.h"

#define SPI_RXBUFFER_SIZE 128
#define SPI_TXBUFFER_SIZE 128

#define SPI_CHANNELS 2

typedef enum
{
   prescaler1 = 0,
   prescaler2,
   prescaler3,
   prescaler4,
   prescaler5,
   prescaler6,
   prescaler7,
   prescaler8,
} SPI_BRPrescaler;

typedef enum
{
   divisor2 = 0,
   divisor4,
   divisor8,
   divisor16,
   divisor32,
   divisor64,
   divisor128,
   divisor256,
   divisor512,
} SPI_BRDivisor;
// These prescalers and BRDs are based on a
// bus clock of 24 MHz
#define SPI_1Mbps_PRESCALER      prescaler3 // 24/3 = 8
#define SPI_1Mbps_BRD            divisor8 // 8/8 = 1Mbps
#define SPI_2Mbps_PRESCALER      prescaler3
#define SPI_2Mbps_BRD            divisor4
#define SPI_0_5Mbps_PRESCALER    prescaler6
#define SPI_0_5Mbps_BRD          divisor8

#define SPI0_MOSI       PORTC_PCR6
#define SPI0_SCK        PORTC_PCR5
#define SPI0_MISO       PORTC_PCR7
#define SPI0_CS         PORTC_PCR4
#define SPI0_CS_PIN     0x0010

#define SPI1_MOSI       PORTE_PCR1
#define SPI1_SCK        PORTE_PCR2
#define SPI1_MISO       PORTE_PCR3
#define SPI1_CS         PORTE_PCR4
#define SPI1_CS_PIN     0x0010

// Beaglebone Black SPI macros
#define DEVICE_LOC      "/dev/spidev1.0"
#define MODE            1
#define BPW             8
#define BBB_SPI_SPEED   500000
#define ARRAY_SIZE(a) (sizeof( a ) / sizeof( ( a )[0] ) )

void SPI_Init( uint8_t SPI_ch, uint8_t master );
void SPI_TransmitData( uint8_t SPI_ch, size_t numBytes );

#ifdef BBB
void SPI_Test( uint8_t SPI_ch );
#endif // BBB
#endif // __SPI__
