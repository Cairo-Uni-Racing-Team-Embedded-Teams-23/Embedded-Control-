/***********************************************************
* File Name    : CURT_ADC_config.h
* Author       : Abdallah said & Shehab Aldeen                            
* Version      : V01                                      
* Date         : 10/11/2022                                
* DESCRIPTION  :  Header file for the ADC driver
***********************************************************/

#ifndef CURT_ADC_CONFIG_H_
#define CURT_ADC_CONFIG_H_

/*    Libraries     */

#include "STD_TYPES.h"
#include "CURT_ADC_private.h"
#include "CURT_DMA_private.h"

/* Defines */
#define TRUE					     1
#define FALSE					     0
#define RESET_VALUE                  0
#define MAX_NUM_OF_SEQ_IN_SQR3	     6
#define MAX_NUM_OF_SEQ_IN_SQR2	     6
#define MAX_NUM_OF_SEQ_IN_SQR1	     4
#define NUM_OF_BITS_EACH_SEQ_SQRX    5
#define MAX_NUM_OF_SEQ_IN_SMPR2      9
#define MAX_NUM_OF_SEQ_IN_SMPR1      17
#define NUM_OF_BITS_EACH_SEQ_SMPRX   3


ADC_ModeTypeDef					conversion_mode	        = SINGLE_CONVERSION ;

ADC_ChannelsModeTypeDef 		channel_mode 	        = SINGLE_CHANNEL ;

ADC_RegularNumberOfChannel 		number_of_channel       = One_Channel; 
 
ADC_ChannelSequence				sequence[]		        = {ch5};

ADC_TimeSamplingRate            Channel_Sampling_Rate[] = { _1_cycle }  ; 

DMA_PeripheralOrMemorySize		peripheral_size         = EIGHT_BITS;

DMA_PeripheralOrMemorySize		memory_size   	        = EIGHT_BITS;

ADC_ExternalEventSelect			external_selection      = TIM1_CC1_EVENT;

#endif /*CURT_ADC_CONFIG_H_*/