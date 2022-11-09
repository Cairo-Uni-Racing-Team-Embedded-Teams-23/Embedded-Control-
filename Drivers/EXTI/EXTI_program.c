#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/* global pointers to function to hold the call back function */
void (*EXTI0_CallBack) (void) = NULL_PTR;
void (*EXTI1_CallBack) (void) = NULL_PTR;


void MEXTI_init()
{
	#if (EXTI_MODE == RISING)
	SET_BIT(EXTI->RSTR ,EXTI_LINE);   /* enable detect for rising edge */
	#elif (EXTI_MODE == FALLING)
	SET_BIT(EXTI -> FTSR ,EXTI_LINE);	/* enable detect for falling edge */
	#elif (EXYI_MODE == ON_CHANGE)
	SET_BIT(EXTI -> RSTR ,EXTI_LINE);	 /* enable detect for rising edge */
	SET_BIT(EXTI -> FTSR ,EXTI_LINE);	/* enable detect for falling edge */

	#endif
}

void MEXTI_enableEXTI(u8 Copy_u8Line)
{
	SET_BIT(EXTI->IMR , Copy_u8Line);
}

void MEXTI_disableEXTI(u8 Copy_u8Line)
{
	CLR_BIT(EXTI->IMR , Copy_u8Line);
	//SET_BIT(EXTI->PR , Copy_u8Line); //haga mn 3nd doaa
}

void MEXTI_swTrigger (u8 Copy_u8Line)
{
	SET_BIT(EXTI-> SWIER, Copy_u8Line);
}


void MEXTI_setSignalLatch(u8 Copy_u8Line, u8 Copy_u8Mode)
{
	switch(Copy_u8Mode)
	{
		case RISING		:	SET_BIT(EXTI-> RSTR ,Copy_u8Line);
		break;
		case FALLING		:	SET_BIT(EXTI-> FTSR ,Copy_u8Line);
		break;
		case ON_CHANGE	: SET_BIT(EXTI-> RSTR ,Copy_u8Line);
						  SET_BIT(EXTI-> FTSR ,Copy_u8Line);
		break;
	}
}


/*						 ISR functions				*/

void EXTI0_setCallBack( void (*ptr) (void) ){

	EXTI0_CallBack = ptr;

}
void EXTI0_IRQHandler(void){

	//if (EXTI0_CallBack() != NULL_PTR )
		{EXTI0_CallBack();
		SET_BIT( EXTI->PR , 0 );}

}



void EXTI1_setCallBack( void (*ptr) (void) ){

	EXTI1_CallBack = ptr;

}
void EXTI1_IRQHandler(void){

	//if (EXTI0_CallBack() != NULL_PTR )
		{EXTI1_CallBack();
		SET_BIT( EXTI->PR , 1 );
		}

}
