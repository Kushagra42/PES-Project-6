# PES-Project-6

# FreeRTOS, ADC, DAC, DMA, DSP

#Created by: Vaidehi Salway & Kushagra Pandey #Date: 10-Dec-2019

#Refrences: Following refrences were used to gain insghts for some of the #functions implemented in this code.

#Counting number of characters: 1. https://www.freertos.org/a00021.html
#				2. dac_adc sample code from MCUxpresso SDK
#				3. Hello world FreeRTOS example from MCUxpresso SDK

#Repo Content:

#Soure code - main.c in src foldre other files in board folder Two scope outputs for generated Sine wave #Readme

#Assignment Description:

#This program includes genertion of sine wave signal on KKL25z's DAC, capture the signal with ADC, transfer collected data buffers via DMA and perform basic DSP operation.
#This program uses lookup tables, buffers, ADC, DAC, DMA, math functions and basic FreeRTOS task management

# Project includes two programs:
# Program 1 : Generates the sine wave and stores the values into lookup table
# Program 2 : Performs reading, transferring and DSP analysis of that data

# Program run in two modes : 1. Debug mode- comments on program steps and prints values needed to verify proper operation of the program
#			     2. Nornal mode- much less verboe logging



#Project Execution Instructions
# Select program 1 or Program 2
# Select between Debug mode or Normal mode 


#Project Execution
#This project runs in two modes
#1. Program 1: This program generates the Sine wave and stores the values in the look up table.
#2. Program 2: This program captures the Look table values
#	       Transfers the DAC register values to ADC0 pin
#	       ADC register values are stores in a circular buffer of size sufficient for one peak to peak Sine wave duration
#	       Once the circular buffer  is full the values are stored in DSP bufffer through DMA
#              DSP buffer used in another circular buffer. Reason for  choosing circular buffer is to fast operation in rea time.
#              Math operations such as Minimum, Maximum, Average and Standard deviaton are performed on the voltage vlues received
#	       LEDs are toggled to indicate different run cycles of the program.


#Code Design: 
#1. Look up table
#2. Circular BBuffer tto store ADC register values
#2. Circular buffer used as DSP buffer

#Problems faced:
#1.DMA transfer
#2.logger time stamp using Systick Timer
 
#Tried resolving the difficulty by reading from resources online and writing multiple functions to test the outputs
