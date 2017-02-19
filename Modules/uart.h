#ifndef __UART__
#define __UART__

#include "includeall.h"

#define OSR                16
#define CR                 13
#define LF                 10

#define RXBUFFER_SIZE      128
#define TXBUFFER_SIZE      128
#define DMA_RXBUFFER_SIZE  _128Bytes
#define DMA_TXBUFFER_SIZE  _1kBytes

#ifdef FRDM
#define DMACH_UART0RX      NO_DMA
#define DMACH_UART0TX      NO_DMA
#define DMACH_UART1RX      NO_DMA
#define DMACH_UART1TX      NO_DMA
#define DMA_TRANSFER_SIZE  _8bit
#else
#define DMACH_UART0RX      NO_DMA
#define DMACH_UART0TX      NO_DMA
#define MODEMDEVICE        "/dev/ttyO1" // Beaglebone Black serial port
#define BONEPATH           "/sys/devices/bone_capemgr.9/slots"
#define POSIX_SOURCE       1
#define BAUDRATE           B115200
#endif

extern uint8_t parseDiag;

void UartSetup( uint8_t channel, uint32_t buadRate, uint8_t parity );
void UartTX( uint8_t * buffer, uint32_t length );
int8_t UartRX( uint8_t * data );
void PutChar( uint8_t data );

#endif //__UART__
