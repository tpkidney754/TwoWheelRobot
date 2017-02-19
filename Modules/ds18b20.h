#ifndef __DS18B20__
#define __DS18B20__

#include "includeall.h"

#define ROM_BYTES                8
#define SERIAL_NUM_BYTES         6
#define SCRATCPAD_BYTES          9

#define WAIT_TIME_LONG           200
#define WAIT_TIME_SHORT          20

typedef union
{
   uint8_t romBytes[ ROM_BYTES ];
   struct __attribute__((__packed__))
   {
      uint8_t familyCode;
      uint8_t serialNum[ SERIAL_NUM_BYTES ];
      uint8_t crc;
   } ;
} DS8B20_ROMCode;

typedef union
{
   uint8_t scratchpadBytes[ SCRATCPAD_BYTES ];
   struct __attribute__((__packed__))
   {
      uint8_t temperatureRawLSB;
      uint8_t temperatureRawMSB;
      uint8_t thRegister;
      uint8_t tlRegister;
      uint8_t configurationRegister;
      uint8_t reserved0;
      uint8_t reserved1;
      uint8_t reserved2;
      uint8_t crc;
   };
} DS8B20_Scratchpad;

// ROM COMMANDS
#define SEARCH_ROM               0xF0
#define READ_ROM                 0x33
#define MATCH_ROM                0x55
#define SKIP_ROM                 0xCC
#define ALARM_SEARCH             0xEC
// FUNCTION COMMANDS
#define CONVERT_T                0x44
#define WRITE_SCRATCHPAD         0x4E
#define READ_SCRATCHPAD          0xBE
#define COPY_SCRATCHPAD          0x48
#define RECALL_E2                0xB8
#define READ_POWER_SUPPLY        0xB4

uint8_t TransactionStepOne( );
void TransactionStepTwo( );
float ReadTemp( );
float ConvertRawTemperatureData( uint16_t rawTemperatureData );


#endif // __DS18B20__
