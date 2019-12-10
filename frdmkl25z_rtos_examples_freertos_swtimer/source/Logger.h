/*
 * @file Logger.h
 * author: kushagra Pandey & Vaidehi Salway
 * Date:10/18/2019
 *
 * This .h file contains the header files requred for Logger.c file
 * There are two modes of operating this file
 * 1. Logger Enable
 * 2. Logger Disable
 *
 * Enable or Disable the logger by un-commenting #define logging_init or #define logging_notinit respectively from Logger.h
 *
 *Defining the funcyions used in Logger.c file
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "string.h"

#include "Delay_Function.h"
#include "LED_Blink.h"
//#include "Table_State_Machine.h"


// Un-comment logging_init and comment logging_notinit to enable logging
#define logging_init
#define level 1

#define LENGTH2  30

// Comment logging_init and un-comment logging_notinit to enable logging
//#define logging_notinit

void Log_Enabled();
void Log_Disabled();
uint8_t Status();
void Log_Data(int x,int y,int8_t data);
void Log_String(int x,int y,char *statement);
void Log_Integer(int x,int y,int integer_value);


