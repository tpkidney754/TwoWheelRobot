#ifndef __MESSAGING__
#define __MESSAGING__

#include "includeall.h"

#define MAX_LENGTH         128

#define ENABLE_MESSAGING   1

typedef enum
{
   noError = 0,
   txBufferFull,
   rxBufferFull,
} MessagingErrors_e;

#define NUM_COMMANDS       7

typedef enum
{
   changeColor = 0,
   changePWM,
   setTemp,
   setDisplay,
   setDesired,
   setRange,
   readTempData,
   NOPcommand = 0xFF
} Commands_e;

#define COMMAND_MSG_BYTES  3
struct CommandMessage
{
   uint8_t cmd;
   uint8_t data;
   uint8_t checksum;
} __attribute__((__packed__));

typedef struct CommandMessage CommandMessage_t;

#define TEMP_MSG_BYTES     7
struct TemperatureMessage
{
   uint8_t currentTemp;
   uint8_t currentDesired;
   uint8_t currentRange;
   uint8_t powerOn;
   uint8_t checksum;
   uint8_t cr;
   uint8_t lf;
} __attribute__((__packed__));

typedef struct TemperatureMessage TemperatureMessage_t;

typedef union
{
   uint8_t data[ TEMP_MSG_BYTES ];
   TemperatureMessage_t msg;
} TemperatureData;


MessagingErrors_e BuildCommandMessage( Commands_e cmd, uint8_t data );
MessagingErrors_e CalculateCommandChecksum( CommandMessage_t * msg );
MessagingErrors_e CalculateTemperatureChecksum( TemperatureMessage_t * msg );
#ifdef FRDM
MessagingErrors_e SendMessage( TemperatureMessage_t * msg );
#endif
#ifdef BBB
MessagingErrors_e SendMessage( CommandMessage_t * msg );
#endif
MessagingErrors_e DecodeCommandMessage( CommandMessage_t * msg );

#endif // __MESSAGING__
