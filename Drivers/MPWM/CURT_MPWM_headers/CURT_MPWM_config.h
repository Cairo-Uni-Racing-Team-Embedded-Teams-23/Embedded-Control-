/***********************************************************
* File Name    : CURT_MPWM_config.h
* Author       : Mina Sobhy & Clara Issa                       
* Version      : V01                                      
* Date         : 9/11/2022                                
* DESCRIPTION  : Header file for the Timer PWM driver interface
***********************************************************/

#ifndef CURT_MPWM_CONFIG_H_
#define CURT_MPWM_CONFIG_H_

#include "CURT_MPWM_private.h"
#include "CURT_MPWM_interface.h"


MPWM_ConfigType	MPWM_config = {
	MPWM_TIM2,
	
	CHANNEL_1,
	
	PWM_MODE1,
	
	0,
	
	5000,
	
	ENABLE_ARR,
	
	UPCOUNTER,
	
	50,
};










#endif /* CURT_MPWM_config_H_ */
