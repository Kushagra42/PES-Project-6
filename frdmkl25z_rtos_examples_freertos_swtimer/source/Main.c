



#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


//custom files
#include "DAC_Pgm.h"
#include "RTOS_Callback.h"
#include "Lookup_Table.c"

#include "event_groups.h"
#include "LED_Blink.h"
#include "Delay_Function.h"


/* Task priorities. */
#define DAC_task_PRIORITY 				(configMAX_PRIORITIES - 1)
#define ADC_task_PRIORITY 				(configMAX_PRIORITIES - 2)
#define ADC_Buffer_task_PRIORITY 		(configMAX_PRIORITIES - 3)
#define VTG_Parameters_task_PRIORITY	(configMAX_PRIORITIES - 4)

static void DAC_task(void *pvParameters);
static void ADC_task(void *pvParameters);
static void ADC_Buffer_task(void *pvParameters);
static void VTG_Parameters_task(void *pvParameters);
Buffer_Parameters* rx_cb;

int main(void)
{
	GREEN_LED_ON();
	Delay_Time(500);
	GREEN_LED_OFF();

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_BootClockRUN();

    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    SystemCoreClockUpdate();

    //enabling IRQ for ADC
    EnableIRQ(DEMO_ADC16_IRQn);
    //Enabling DAC ADC
    DAC_ADC_Init();

    RED_LED_INIT();
    BLUE_LED_INIT();
    GREEN_LED_INIT();

    //initializing the circular buffer
	rx_cb= pvPortMalloc(BUFFER_LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(rx_cb,BUFFER_LENGTH);


    DSP_Initialize();


    xTaskCreate(DAC_task, "DAC_Create_Start_Timer", configMINIMAL_STACK_SIZE + 38, NULL, DAC_task_PRIORITY, NULL);

    xTaskCreate(ADC_task, "ADC_Create_Start_Task", configMINIMAL_STACK_SIZE + 38, NULL, ADC_task_PRIORITY, NULL);

    xTaskCreate(ADC_Buffer_task, "ADC_Buffer_Task", configMINIMAL_STACK_SIZE + 38, NULL, ADC_Buffer_task_PRIORITY, NULL);

    xTaskCreate(VTG_Parameters_task, "VTG_Parameters_task", configMINIMAL_STACK_SIZE + 38, NULL, VTG_Parameters_task_PRIORITY, NULL);


    /* Start scheduling. */
    vTaskStartScheduler();
    for (;;)
        ;

    return 0 ;
}


static void DAC_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("IN DAC TASK.\r\n");
        DAC_Create_Start_Timer();
        vTaskSuspend(NULL);
    }
}


static void ADC_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("IN ADC TASK.\r\n");
        ADC_Calculation();
        vTaskDelay(100);

    }
}

static void ADC_Buffer_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("IN ADC TASK.\r\n");
        Add_ADC_Values_To_Buffer();
        vTaskDelay(100);

    }
}


static void VTG_Parameters_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("IN ADC TASK.\r\n");
        Voltage_Prameters();
        vTaskDelay(100);

    }
}





