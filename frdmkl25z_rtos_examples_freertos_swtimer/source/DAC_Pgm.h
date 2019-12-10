

#include "fsl_adc16.h"
#include "fsl_dac.h"
#include "CIRCULAR_BUFFER.H"



#include "fsl_dma.h"
#include "fsl_dmamux.h"


#define DEMO_ADC16_BASEADDR ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U /* PTE20, ADC0_SE0 */
#define DEMO_DAC_BASEADDR DAC0

#define DEMO_ADC16_IRQn ADC0_IRQn
#define DEMO_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler
#define DAC_1_0_VOLTS 1241U
#define DAC_1_5_VOLTS 1862U
#define DAC_2_0_VOLTS 2482U
#define DAC_2_5_VOLTS 3103U
#define DAC_3_0_VOLTS 3724U

#define VREF_BRD 3.300
#define SE_12BIT 4096.0


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DMA_CHANNEL 0
#define DMA_SOURCE 63
void DMA_Callback(dma_handle_t *handle, void *param);
void DSP_Initialize();
void DMA_Pgm();


/* Initialize ADC16 & DAC */
void DAC_ADC_Init(void);
void sine_wave();

void DAC_Equations();
void ADC_Calculation();
void Add_ADC_Values_To_Buffer();
void Voltage_Prameters();
