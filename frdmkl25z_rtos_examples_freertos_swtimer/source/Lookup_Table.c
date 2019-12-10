//#define PROGRAM1

#ifdef PROGRAM1
#include "fsl_debug_console.h"
#include "math.h"



void Sine_get();

int index=0;

static int buffer[LENGTH];
static int DAC_Buffer[LENGTH];

void Sine_get()
{

	for(index = 0; index<LENGTH ;index++)
	 {
	  buffer[index] = ( ( ( sin(index * (6.28/50)))+2)*4096/3.3 );
	  PRINTF("SINE = %d\n\r",buffer[index]);
	  DAC_Buffer[index]=buffer[index];
	 }


}
#endif

#define LENGTH 64
static const int DAC_Buffer[LENGTH] = {
        2631,
        2780,
        2929,
        3077,
        3202,
        3326,
        3437,
        3524,
        3599,
        3661,
        3710,
        3712,
        3713,
        3710,
        3661,
        3599,
        3524,
        3437,
        3326,
        3202,
        3077,
        2929,
        2780,
        2631,
        2482,
        2321,
        2172,
        2023,
        1874,
        1750,
        1626,
        1526,
        1427,
        1353,
        1291,
        1253,
        1241,
        1240,
        1241,
        1253,
        1291,
        1353,
        1427,
        1526,
        1626,
        1750,
        1874,
        2023,
        2172,
        2321,
        2482
};














