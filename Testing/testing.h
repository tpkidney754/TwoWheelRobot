#ifdef TESTING
#ifndef __TESTING__
#define __TESTING__

#include "includeall.h"

#define PASS            0
#define HEADER_LENGTH   100

void Testing();

uint8_t testPrintBuffer[ 256 ];
uint8_t headerBuffer[ HEADER_LENGTH ];

typedef enum HeaderType
{
   pass_e = 0,
   fail_e,
   main_e,
} HeaderType_t, headerType_t;

void PrintHeader( uint8_t * header, HeaderType_t headerType );

#endif // __TESTING__
#endif
