################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/CIRCULAR_BUFFER.c \
../source/DAC_Pgm.c \
../source/Delay_Function.c \
../source/LED_Blink.c \
../source/Logger.c \
../source/Lookup_Table.c \
../source/Main.c \
../source/RTOS_Callback.c \
../source/Volt_Equations.c \
../source/freertos_swtimer.c \
../source/semihost_hardfault.c 

OBJS += \
./source/CIRCULAR_BUFFER.o \
./source/DAC_Pgm.o \
./source/Delay_Function.o \
./source/LED_Blink.o \
./source/Logger.o \
./source/Lookup_Table.o \
./source/Main.o \
./source/RTOS_Callback.o \
./source/Volt_Equations.o \
./source/freertos_swtimer.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/CIRCULAR_BUFFER.d \
./source/DAC_Pgm.d \
./source/Delay_Function.d \
./source/LED_Blink.d \
./source/Logger.d \
./source/Lookup_Table.d \
./source/Main.d \
./source/RTOS_Callback.d \
./source/Volt_Equations.d \
./source/freertos_swtimer.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=1 -DDEBUG -DCPU_MKL25Z128VLK4 -DFSL_RTOS_FREE_RTOS -DFRDM_KL25Z -DFREEDOM -DCPU_MKL25Z128VLK4_cm0plus -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DSDK_DEBUGCONSOLE=1 -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../freertos -I../startup -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


