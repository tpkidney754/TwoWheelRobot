#include "project1.h"

void Project1Report( void )
{
   uint8_t array[ ARRAY_SIZE ];
   uint8_t * pArray1 = &array[ 0 ];
   uint8_t * pArray2 = pArray2 = &array[ 8 ];
   uint8_t * pArray3 = pArray3 = &array[ 16 ];

   uint8_t temp = 31;
   for( uint32_t i = 0; i < 16; i++ )
   {
      *( pArray1 + i ) = temp++;
   }

   DumpMemory( array, ARRAY_SIZE );

   MyMemSet( pArray3, 0, ARRAY_SIZE-16);

   DumpMemory( array, ARRAY_SIZE );

   MyMemMove( pArray1, pArray3, 8 );
   DumpMemory( array, ARRAY_SIZE );
   MyMemMove( pArray2, pArray1, 16 );
   DumpMemory( array, ARRAY_SIZE );
   MyReverse( array, ARRAY_SIZE );

   DumpMemory( array, ARRAY_SIZE );
}
