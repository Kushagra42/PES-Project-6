
/* Standard includes. */
#include <assert.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"


/* The software timer period. */
#define SW_TIMER_PERIOD_MS (100 / portTICK_PERIOD_MS)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* The callback function. */
 static void Sine_Wave_Callback(TimerHandle_t xTimer);
 static void ADC_Read_Store_Callback(TimerHandle_t xTimer);

 void DAC_Create_Start_Timer();
 void ADC_Create_Start_Timer();
