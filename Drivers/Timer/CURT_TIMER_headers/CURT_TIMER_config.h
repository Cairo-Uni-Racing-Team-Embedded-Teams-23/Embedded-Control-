/***********************************************************
* File Name    : CURT_TIMER_config.h
* Author       : Mina Sobhy & Clara Issa                       
* Version      : V01                                      
* Date         : 9/11/2022                                
* DESCRIPTION  : Header file for the Timer PWM driver interface
***********************************************************/

#ifndef CURT_TIMER_CONFIG_H_
#define CURT_TIMER_CONFIG_H_

#include "CURT_TIMER_private.h"
#include "CURT_TIMER_interface.h"


TIMER_ConfigType	TIMER_config =
{
	TIMER_TIM2,
	
	CHANNEL_1,
	
	OUTPUT_COMPARE,
	
	0,
	
	5000,
	
	ENABLE_ARR,
	
	UPCOUNTER,
	
	50,
};










#endif /* CURT_TIMER_config_H_ */
