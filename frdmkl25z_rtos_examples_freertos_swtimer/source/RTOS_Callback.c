#include "RTOS_Callback.h"
#include "DAC_Pgm.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"


static void Sine_Wave_Callback(TimerHandle_t xTimer)
{

	 PRINTF("\n IN SINE WAVE CALL BACK FUNC");
	 Log_String(0,1,"IN SINE WAVE CALL BACK FUNC");
     sine_wave();


}


void DAC_Create_Start_Timer()
{

	TimerHandle_t SwTimerHandle = NULL;
    /* Create the software timer. */
    SwTimerHandle = xTimerCreate("SwTimer",          /* Text name. */
                                 SW_TIMER_PERIOD_MS, /* Timer period. */
                                 pdTRUE,             /* Enable auto reload. */
                                 0,                  /* ID is not used. */
								 Sine_Wave_Callback);   /* The callback function. */
    /* Start timer. */
    xTimerStart(SwTimerHandle, 0);
    /* Start scheduling. */


}




