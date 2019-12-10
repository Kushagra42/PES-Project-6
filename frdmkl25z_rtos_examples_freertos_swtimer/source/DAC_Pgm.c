
#include "DAC_Pgm.h"
#include "Lookup_Table.c"
#include "fsl_uart.h"
#include "fsl_debug_console.h"
#include "stdint.h"
#include "Logger.h"

#include "fsl_adc16.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
#include "Volt_Equations.h"
#include "LED_Blink.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_BASE ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U /*PTE20, ADC0_SE0 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
dma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done = false;
int8_t flag_full_ut=0;
int8_t COUNT=0;
//Buffer_Parameters* dx_cb;
volatile int8_t DMA_Int_Flag=0;
volatile int8_t Run_Num=0;
//Buffer_Parameters* dx_cb=NULL;

uint32_t k = 0;
dma_transfer_config_t transferConfig;

extern Buffer_Parameters* rx_cb;
extern Buffer_Parameters* dx_cb;

int8_t full_flag=0;
volatile uint8_t i;
adc16_channel_config_t g_adc16ChannelConfigStruct;
float voltRead;

/*******************************************************************************
 * Code
 ******************************************************************************/
void DAC_ADC_Init(void)
{
    adc16_config_t adc16ConfigStruct;
    dac_config_t dacConfigStruct;
    //adc16_channel_config_t g_adc16ChannelConfigStruct;


    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASEADDR, true); /* Enable output. */


    ADC16_GetDefaultConfig(&adc16ConfigStruct);
#if defined(BOARD_ADC_USE_ALT_VREF)
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(DEMO_ADC16_BASEADDR, &adc16ConfigStruct);

    /* Make sure the software trigger is used. */
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASEADDR, false);
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASEADDR))
    {
        PRINTF("\r\nADC16_DoAutoCalibration() Done.");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Prepare ADC channel setting */
    g_adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
    g_adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    g_adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_Adc16ConversionValue = 0;
volatile bool g_Adc16ConversionDoneFlag = false;


void DEMO_ADC16_IRQ_HANDLER_FUNC(void)
{
    g_Adc16ConversionDoneFlag = true;
    /* Read conversion result to clear the conversion completed flag. */
    g_Adc16ConversionValue = ADC16_GetChannelConversionValue(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP);
}


void sine_wave()
   {


				DAC_SetBufferValue(DEMO_DAC_BASEADDR, 0U, DAC_Buffer[i]);
   	   	        PRINTF("\r\n\r\nDAC Value: %d\r\n", DAC_Buffer[i]);
   	   	        Log_String(0,1,"DAC Value");
   	   	  		Log_Data(0,1,DAC_Buffer[i]);
	        	i++;
	        	DAC_Equations();
	        	 GREEN_LED_ON();
	        	 Delay_Time(500);
	        	 GREEN_LED_OFF();
	        	while(i>51)
	        	{
	        		i=0;

	        	}
   }


void DAC_Equations()


{
			float voltRead;

	        /* Convert ADC value to a voltage based on 3.3V VREFH on board */
	        voltRead = (float)(DAC_Buffer[i]) * (VREF_BRD / SE_12BIT);
	        PRINTF("\r\nADC Voltage: %0.3f Volts\r\n", voltRead);
	        Log_String(0,1,"ADC Voltage");
	         Log_Data(0,1,voltRead);
	        //Log_String(Time_Stamp,0,1,"ADC Voltage");
	        //Log_Data(Time_Stamp,0,1,voltRead);


}


void ADC_Calculation()
{
			PRINTF("INSIDE ADC CALCULATIONS");

			g_Adc16ConversionDoneFlag = false;
	        ADC16_SetChannelConfig(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChannelConfigStruct);

	        while (!g_Adc16ConversionDoneFlag)
	        {
	        }
	        PRINTF("\r\n\r\nADC Value: %d\r\n", g_Adc16ConversionValue);

	        /* Convert ADC value to a voltage based on 3.3V VREFH on board */
	        voltRead = (float)(g_Adc16ConversionValue * (VREF_BRD / SE_12BIT));
	        PRINTF("\r\nADC FUNCTION Voltage: %0.3f\r\n", voltRead);
	    	Add_Element_To_Buffer(rx_cb,g_Adc16ConversionValue);
	    	Check_Buffer(rx_cb, BUFFER_LENGTH);


}

void DSP_Initialize()
{

	dx_cb= pvPortMalloc(BUFFER_LENGTH*sizeof(Buffer_Parameters));
	Init_Buffer(dx_cb,BUFFER_LENGTH);
}

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
    		g_Transfer_Done = true;
}

void DMA_Pgm()
{

   PRINTF("INSIDE DMA PRGM");


	/* Print source buffer */
	PRINTF("DMA memory to memory transfer begin.\r\n\r\n");
	for (k = 0; k < BUFFER_LENGTH; k++)
	{
	    PRINTF("\r\nDestination Buffer:%d\t", dx_cb[k]);
	}

    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);
    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareTransfer(&transferConfig, rx_cb, sizeof(uint16_t), dx_cb, sizeof(uint16_t), sizeof(BUFFER_LENGTH*sizeof(uint16_t)),
                        kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    DMA_StartTransfer(&g_DMA_Handle);

    /* Wait for DMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
    PRINTF("\r\n\r\nDMA memory to memory transfer finish.\r\n\r\n");
    PRINTF("\r\nDestination Buffer:\r\n");
    /* Print destination buffer */
    PRINTF("\r\n\r\nDMA memory to memory transfer finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");

    for (k = 0; k < BUFFER_LENGTH; k++)
    {
        PRINTF("\r\nNEW BUFFER:%d\t", dx_cb[k]);
    }
    while (g_Transfer_Done==true)
    {
    	DMA_Int_Flag=1;
    	Run_Num++;

    }


}


void Add_ADC_Values_To_Buffer()
{
	Check_Buffer(rx_cb, BUFFER_LENGTH);

	 if(full_flag==1)
	 {

		 	BLUE_LED_ON();
			Delay_Time(100);
		    BLUE_LED_OFF();
			Delay_Time(100);


		    PRINTF("\r\nCIRCULAR BUFFER IS FULL");
		    BLUE_LED_ON();
		    Delay_Time(500);
		    BLUE_LED_OFF();

		 	DMA_Pgm();

	 }


}


void Voltage_Prameters()
{
	if(DMA_Int_Flag)
	{
	if(Run_Num<5)
	{
		 Max_Volt();
		 Min_Volt();
		 Avg_Volt();
		 Std_Dev();
	}
	else if(Run_Num>=5)
	{

		vTaskSuspendAll();
	}
	}




}

