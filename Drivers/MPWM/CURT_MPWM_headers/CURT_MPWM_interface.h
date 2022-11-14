/***********************************************************
* File Name    : CURT_MPWM_interface.h
* Author       : Mina Sobhy & Clara Issa                       
* Version      : V01                                      
* Date         : 9/11/2022                                
* DESCRIPTION  :  Header file for the Timer PWM driver interface
***********************************************************/
#ifndef CURT_MPWM_INTERFACE_H_
#define CURT_MPWM_INTERFACE_H_

#include "CURT_MPWM_private.h"

typedef enum 
{
	CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4
}Channel_No;

typedef enum 
{
	/* PWM_mode1: output is HIGH till it reaches the compare value then becomes LOW
	   PWM_mode2: output is LOW till it reaches the compare value then becomes HIGH */
	PWM_MODE1, PWM_MODE2
}PWM_mode;


typedef enum 
{
	DISABLE_ARR, ENABLE_ARR
}Auto_Reload_Buffer;

typedef enum 
{
	UPCOUNTER, DOWNCOUNTER
}Direction_State;


typedef struct 
{
	TIM_TypeDef 		*TIMERx					;
	Channel_No 			Copy_xChannelNo			;
	PWM_mode 			Copy_xMode				;
	u16 				Copy_xPreScaler			;
	u16 				Copy_xPreloadValue		;
	Auto_Reload_Buffer 	Copy_xAutoReloadBuffer	;
	Direction_State 	Copy_xDirection_State	;
	u8 					Copy_xDutyCycle			;
}MPWM_ConfigType;

void MPWM_init(MPWM_ConfigType * MPWM_config);
void MPWM_setTopValue(TIM_TypeDef *TIMERx , u16 Copy_xPreloadValue);
void MPWM_setDutyCycle(TIM_TypeDef *TIMERx ,u8 Copy_xChannelNo, u8 Copy_xDutyCycle);
void MPWM_deInit(TIM_TypeDef *TIMERx ,u8 Copy_xChannelNo);


#endif /* CURT_MPWM_INTERFACE_H_ */
