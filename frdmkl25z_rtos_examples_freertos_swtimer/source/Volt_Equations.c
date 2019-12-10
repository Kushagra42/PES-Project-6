
#include "Volt_Equations.h"
#include "DAC_Pgm.h"
#include "math.h"

Buffer_Parameters* dx_cb=0;
int l=0;

uint32_t Max_Volt()
{
uint32_t max=dx_cb;
for(int i=0;i<BUFFER_LENGTH;i++)
{

	if(dx_cb>max)
	{

		max=dx_cb;
	}
}
return max;

}

uint32_t Min_Volt()
{
	uint32_t min=dx_cb;
for(l=0;l<BUFFER_LENGTH;l++)
{

	if(dx_cb<min)
	{

		min=dx_cb;
	}
}
return min;
}

float Avg_Volt()
{

float vtg_arr[BUFFER_LENGTH];
for(l=0;l<=BUFFER_LENGTH;l++)
{
	vtg_arr[l]=(vtg_arr[l]+vtg_arr[l+1])/(BUFFER_LENGTH);

}
return vtg_arr[BUFFER_LENGTH];

}

float Std_Dev()
{
uint32_t sum=0.0;
uint32_t mean;
uint32_t SD=0;


for(l=0;l<=BUFFER_LENGTH;l++)
{
sum+=dx_cb;

}
mean =sum/BUFFER_LENGTH;
for(l=0;l<=BUFFER_LENGTH;l++)
{
	//SD+= pow((dx_cb - mean),2);
	return sqrt(SD/BUFFER_LENGTH);
}

}
