

/* Libraries*/

#include "std_types.h"
#include "common_macros.h"



/* Own Driver Files*/
#include "CURT_MPWM_interface.h"
#include "CURT_MPWM_private.h"
#include "CURT_MPWM_config.h"


void MPWM_init(MPWM_ConfigType *  MPWM_config)
{		
	/* Enable or disable Auto-Reload */
	MPWM_config -> TIMERx -> CR1 . ARPE = MPWM_config -> Copy_xAutoReloadBuffer;
	
	MPWM_config -> TIMERx -> CR1 . DIR = MPWM_config -> Copy_xDirection_State;
	
	/* Set the count mode (up/down) */
	switch ( MPWM_config -> Copy_xChannelNo)
	{
		case CHANNEL_1:
			MPWM_config -> TIMERx -> CCMR1 . OC1M = MPWM_config -> Copy_xMode? 7 : 6;
			MPWM_config -> TIMERx -> CCMR1 . OC1PE = LOGIC_HIGH;
		break;
		
		case CHANNEL_2:
			MPWM_config -> TIMERx -> CCMR1 . OC2M = MPWM_config -> Copy_xMode? 7 : 6;
			MPWM_config -> TIMERx -> CCMR1 . OC2PE = LOGIC_HIGH;
		break;
		
		case CHANNEL_3:
			MPWM_config -> TIMERx -> CCMR2 . OC3M = MPWM_config -> Copy_xMode? 7 : 6;
			MPWM_config -> TIMERx -> CCMR2 . OC3PE = LOGIC_HIGH;
		break;
		
		case CHANNEL_4:
			MPWM_config -> TIMERx -> CCMR2 . OC4M = MPWM_config -> Copy_xMode? 7 : 6;
			MPWM_config -> TIMERx -> CCMR2 . OC4PE = LOGIC_HIGH ;
		break;
		
	}
	
	MPWM_config -> TIMERx -> ARR . ARR = MPWM_config -> Copy_xPreloadValue;
	
	MPWM_config -> TIMERx -> PSC . PSC= MPWM_config -> Copy_xPreScaler;

	MPWM_setDutyCycle(MPWM_config -> TIMERx, MPWM_config -> Copy_xChannelNo, MPWM_config -> Copy_xDutyCycle);

}

void MPWM_setTopValue(TIM_TypeDef *TIMERx , u16 Copy_xPreloadValue)
{
	TIMERx -> ARR . ARR= Copy_xPreloadValue;
}


void MPWM_setDutyCycle(TIM_TypeDef *TIMERx ,u8 Copy_xChannelNo, u8 Copy_xDutyCycle)
{
	//u16 LOC_ARR	= (u16) (TIMERx -> ARR) ;
	u16 LOC_dutyCycle = (u16)((u64)(Copy_xDutyCycle * (TIMERx -> ARR . ARR)) / 100);
	

		switch (Copy_xChannelNo)
	{
		case CHANNEL_1:
			TIMERx -> CCR1 . CCR1 = LOC_dutyCycle;
		break;
		
		case CHANNEL_2:
			TIMERx -> CCR2 . CCR2 = LOC_dutyCycle;
		break;
		
		case CHANNEL_3:
			TIMERx -> CCR3 . CCR3= LOC_dutyCycle;
		break;
		
		case CHANNEL_4:
			TIMERx -> CCR4 . CCR4 = LOC_dutyCycle;
		break;
		
	}
	
	/* enable counter */
	TIMERx -> CR1 . CEN 	= LOGIC_HIGH;
	
}


void MPWM_deInit(TIM_TypeDef *TIMERx ,u8 Copy_xChannelNo)
{
	TIMERx -> CR1 . ARPE	= 0 ;
	TIMERx -> CR1 . DIR		= 0 ;

	TIMERx -> CCMR1	. OC1M	= 0 ;
	TIMERx -> CCMR2	. OC4M	= 0 ;
	TIMERx -> PSC . PSC		= 0 ;
	TIMERx -> ARR . ARR		= 0 ;
	TIMERx -> CCR1 . CCR1	= 0 ;
	TIMERx -> CCR2 . CCR2	= 0 ;
	TIMERx -> CCR3 . CCR3	= 0 ;
	TIMERx -> CCR4 . CCR4	= 0 ;
}
