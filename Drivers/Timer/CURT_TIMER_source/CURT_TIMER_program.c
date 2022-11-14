

/* Libraries*/

#include "std_types.h"
#include "common_macros.h"



/* Own Driver Files*/
#include "CURT_TIMER_interface.h"
#include "CURT_TIMER_private.h"
#include "CURT_TIMER_config.h"

static volatile void (*TIMER2_CallBack)(void) = NULL_PTR;
static volatile void (*TIMER3_CallBack)(void) = NULL_PTR;
static volatile void (*TIMER4_CallBack)(void) = NULL_PTR;
static volatile void (*TIMER5_CallBack)(void) = NULL_PTR;

void TIMER_init(TIMER_ConfigType *  TIMER_config, void (*Copy_vpFuncPtr)(void))
{		
	/* Enable or disable Auto-Reload */
	TIMER_config -> TIMERx -> CR1 . ARPE = TIMER_config -> Copy_xAutoReloadBuffer;

	TIMER_config -> TIMERx -> CR1 . DIR = TIMER_config -> Copy_xDirection_State;

	switch (TIMER_config -> Copy_xMode)
	{
	case OUTPUT_COMPARE:
		TIMER_OutputCompareMode(TIMER_config->TIMERx, TIMER_config -> Copy_xChannelNo,TIMER_config -> Copy_xCompareValue);
		break;

	case ONE_PULSE:
		TIMER_OnePulseMode(TIMER_config->TIMERx, TIMER_config -> Copy_xChannelNo, TIMER_config -> Copy_xCompareValue);
		break;
	}

	if (TIMER_config->TIMERx == TIMER_TIM2)
		TIMER2_CallBack = Copy_vpFuncPtr;
	else if (TIMER_config->TIMERx == TIMER_TIM3)
		TIMER3_CallBack = Copy_vpFuncPtr;
	else if (TIMER_config->TIMERx == TIMER_TIM4)
		TIMER4_CallBack = Copy_vpFuncPtr;
	else if (TIMER_config->TIMERx == TIMER_TIM5)
		TIMER5_CallBack = Copy_vpFuncPtr;

	TIMER_config -> TIMERx -> ARR . ARR = TIMER_config -> Copy_xPreloadValue;

	TIMER_config -> TIMERx -> PSC . PSC= TIMER_config -> Copy_xPreScaler;

	TIMER_config -> TIMERx -> CR1 . CEN = LOGIC_HIGH;

}

void TIMER_OnePulseMode(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue)
{
	TIMERx -> CR1 . OPM = LOGIC_HIGH ;
	TIMERx -> DIER . UIE = LOGIC_HIGH;
	switch (Copy_xChannelNo)
	{
	case CHANNEL_1:
		TIMERx -> CCR1 . CCR1 = Copy_xCompareValue;
		break;

	case CHANNEL_2:
		TIMERx -> CCR2 . CCR2 = Copy_xCompareValue;
		break;

	case CHANNEL_3:
		TIMERx -> CCR3 . CCR3 = Copy_xCompareValue;
		break;

	case CHANNEL_4:
		TIMERx -> CCR4 . CCR4 = Copy_xCompareValue;
		break;
	}

}

void TIMER_OutputCompareMode(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue)
{
	//TIMERx_config -> TIMERx -> DIER . UIE = LOGIC_HIGH;
	switch (Copy_xChannelNo)
	{
	case CHANNEL_1:
		TIMERx -> DIER . CC1IE =  LOGIC_HIGH;
		TIMERx -> CCMR1 . CC1S = 0;
		TIMERx -> CCMR1 . OC1M = 0;
		/* if we want to generate output OC1
		 * TIMERx -> CCER . CC1E = LOGIC_HIGH; */
		TIMERx -> CCER . CC1E = 0;
		TIMERx -> CCR1 . CCR1 = Copy_xCompareValue;
		break;

	case CHANNEL_2:
		TIMERx -> DIER . CC2IE =  LOGIC_HIGH;
		TIMERx -> CCMR1 . CC2S = 0;
		TIMERx -> CCMR1 . OC2M = 0;
		/* if we want to generate output OC2
		 * TIMERx -> CCER . CC2E = LOGIC_HIGH; */
		TIMERx -> CCER . CC2E = 0;
		TIMERx -> CCR2 . CCR2 = Copy_xCompareValue;
		break;

	case CHANNEL_3:
		TIMERx -> DIER . CC3IE =  LOGIC_HIGH;
		TIMERx -> CCMR2 . CC3S = 0;
		TIMERx -> CCMR2 . OC3M = 0;
		/* if we want to generate output OC3
		 * TIMERx -> CCER . CC3E = LOGIC_HIGH; */
		TIMERx -> CCER . CC3E = 0;
		TIMERx -> CCR3 . CCR3 = Copy_xCompareValue;
		break;

	case CHANNEL_4:
		TIMERx -> DIER . CC4IE =  LOGIC_HIGH;
		TIMERx -> CCMR2 . CC4S = 0;
		TIMERx -> CCMR2 . OC4M = 0;
		/* if we want to generate output OC4
		 * TIMERx -> CCER . CC4E = LOGIC_HIGH; */
		TIMERx -> CCER . CC4E = 0;
		TIMERx -> CCR4 . CCR4 = Copy_xCompareValue;
		break;
	}
}

void TIMER_setTopValue(TIM_TypeDef *TIMERx , u16 Copy_xPreloadValue)
{
	TIMERx -> ARR . ARR= Copy_xPreloadValue;
}

void TIMER_setCompareValue(TIM_TypeDef * TIMERx, u8 Copy_xChannelNo, u16 Copy_xCompareValue)
{
	switch(Copy_xChannelNo)
	{
	case CHANNEL_1:
		TIMERx -> CCR1 . CCR1 = Copy_xCompareValue;
		break;
	case CHANNEL_2:
		TIMERx -> CCR2 . CCR2 = Copy_xCompareValue;
		break;
	case CHANNEL_3:
		TIMERx -> CCR3 . CCR3 = Copy_xCompareValue;
		break;
	case CHANNEL_4:
		TIMERx -> CCR4 . CCR4 = Copy_xCompareValue;
		break;
	}
}

void TIM2_IRQHandler(void)
{
	TIMER2_CallBack();
	TIMER_TIM2 -> SR . UIF = 0;
	TIMER_TIM2 -> SR . CC1IF = 0;
	TIMER_TIM2 -> SR . CC2IF = 0;
	TIMER_TIM2 -> SR . CC3IF = 0;
	TIMER_TIM2 -> SR . CC4IF = 0;
}

void TIM3_IRQHandler(void)
{
	TIMER3_CallBack();
	TIMER_TIM3 -> SR . UIF = 0;
	TIMER_TIM3 -> SR . CC1IF = 0;
	TIMER_TIM3 -> SR . CC2IF = 0;
	TIMER_TIM3 -> SR . CC3IF = 0;
	TIMER_TIM3 -> SR . CC4IF = 0;

}

void TIM4_IRQHandler(void)
{
	TIMER4_CallBack();
	TIMER_TIM4 -> SR . UIF = 0;
	TIMER_TIM4 -> SR . CC1IF = 0;
	TIMER_TIM4 -> SR . CC2IF = 0;
	TIMER_TIM4 -> SR . CC3IF = 0;
	TIMER_TIM4 -> SR . CC4IF = 0;

}

void TIM5_IRQHandler(void)
{
	TIMER5_CallBack();
	TIMER_TIM5 -> SR . UIF = 0;
	TIMER_TIM5 -> SR . CC1IF = 0;
	TIMER_TIM5 -> SR . CC2IF = 0;
	TIMER_TIM5 -> SR . CC3IF = 0;
	TIMER_TIM5 -> SR . CC4IF = 0;

}

void TIMER_deInit(TIM_TypeDef *TIMERx ,u8 Copy_xChannelNo)
{
	TIMERx -> CR1 	. ARPE	= 0 ;
	TIMERx -> CR1 	. DIR	= 0 ;
	TIMERx -> CCMR1	. OC1M	= 0 ;
	TIMERx -> CCMR2	. OC4M	= 0 ;
	TIMERx -> PSC 	. PSC	= 0 ;
	TIMERx -> ARR 	. ARR	= 0 ;
	TIMERx -> CCR1 	. CCR1	= 0 ;
	TIMERx -> CCR2 	. CCR2	= 0 ;
	TIMERx -> CCR3 	. CCR3	= 0 ;
	TIMERx -> CCR4 	. CCR4	= 0 ;
}
