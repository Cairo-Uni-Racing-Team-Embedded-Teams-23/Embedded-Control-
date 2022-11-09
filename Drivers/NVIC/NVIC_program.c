 /******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC_program.c
 *
 * Description: Program file for the STM32 NVIC driver
 *
 * Author: Mohammad Wael
 *
 *******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


void MNVIC_enableInterrupt(u8 Copy_u8IntNumber){

	if(Copy_u8IntNumber <= 31){
		NVIC_ISER0 = (1 << Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59){
		NVIC_ISER1 = (1 << (Copy_u8IntNumber-32));
	}
}

void MNVIC_disableInterrupt(u8 Copy_u8IntNumber){

	if(Copy_u8IntNumber <= 31){
		NVIC_ICER0 = (1 << Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59){
		NVIC_ICER1 = (1 << (Copy_u8IntNumber-32));
	}
}

void MNVIC_setPendingFlag(u8 Copy_u8IntNumber){
	if(Copy_u8IntNumber <= 31){
		NVIC_ISPR0 = (1 << Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59){
		NVIC_ISPR1 = (1 << (Copy_u8IntNumber-32));
	}
}

void MNVIC_clearPendingFlag(u8 Copy_u8IntNumber){
	if(Copy_u8IntNumber <= 31){
		NVIC_ICPR0 = (1 << Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59){
		NVIC_ICPR1 = (1 << (Copy_u8IntNumber-32));
	}
}

u8 MNVIC_getActiveFlag(u8 Copy_u8IntNumber){

	u8 Local_u8Result;

	if(Copy_u8IntNumber <= 31){
		Local_u8Result = GET_BIT(NVIC_IABR0, Copy_u8IntNumber);
	}
	else if(Copy_u8IntNumber <= 59){
		Local_u8Result = GET_BIT(NVIC_IABR1, Copy_u8IntNumber-32);
	}
	return Local_u8Result;
}

void MNVIC_setPriority(s8 Copy_s8IntID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority, u32 Copy_u32Group){

	/* The term ((Copy_u32Group - 0x05FA0300)/0x100) gives the number of sub groups
	 * which can be used to shift the group priority by the number of sub groups bits
	 * and write the group priority value in the right place then the or operation
	 * to write the sub group priority values in the least bits                       */
	u8 Local_u8Priority = (Copy_u8SubPriority|(Copy_u8GroupPriority<<((Copy_u32Group - 0x05FA0300)/0x100)));

	/* External peripheral */
	if(Copy_s8IntID >= 0){
		/* Shift by 4 to avoid writing in the reserved bits of IPR */
		NVIC_IPR[Copy_s8IntID] = (Local_u8Priority<<4);
	}
	/* Set the desired config for SCB_AIRCR */
	SCB_AIRCR = Copy_u32Group;
}
