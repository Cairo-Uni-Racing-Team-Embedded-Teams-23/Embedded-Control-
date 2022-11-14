/***********************************************************
 * File Name    : CURT_TIMER_interface.h
 * Author       : Mina Sobhy & Clara Issa
 * Version      : V01
 * Date         : 9/11/2022
 * DESCRIPTION  :  Header file for the Timer PWM driver
 ***********************************************************/
#ifndef CURT_TIMER_INTERFACE_H_
#define CURT_TIMER_INTERFACE_H_

#include "CURT_TIMER_private.h"

typedef enum 
{
	CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4
}Channel_No;

typedef enum 
{
	/* PWM_mode1: output is HIGH till it reaches the compare value then becomes LOW
	   PWM_mode2: output is LOW till it reaches the compare value then becomes HIGH */
	OUTPUT_COMPARE, ONE_PULSE
}TIMER_mode;


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
	TIM_TypeDef *TIMERx		;
	Channel_No Copy_xChannelNo	;
	TIMER_mode Copy_xMode	;
	u16 Copy_xPreScaler	;
	u16 Copy_xPreloadValue	;
	u16 Copy_xCompareValue;
	Auto_Reload_Buffer Copy_xAutoReloadBuffer; 
	Direction_State Copy_xDirection_State;
}TIMER_ConfigType;

void TIMER_init(TIMER_ConfigType *  TIMER_config, void (*Copy_vpFuncPtr)(void));
void TIMER_voidSetTopValue(TIM_TypeDef *TIMERx , u16 Copy_u16TopValue);
void TIMER_OnePulseMode(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue);
void TIMER_OutputCompareMode(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue);
void TIMER_setCompareValue(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue);
void TIMER_voidDeInit(TIM_TypeDef *TIMERx ,u8 Copy_u8ChannelNo);


#endif /* CURT_TIMER_INTERFACE_H_ */
