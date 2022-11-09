 /******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC_interface.h
 *
 * Description: Interface file for the STM32 NVIC driver
 *
 * Author: Mohammad Wael
 *
 *******************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "STD_TYPES.H"

void MNVIC_enableInterrupt(u8 Copy_u8IntNumber);
void MNVIC_disableInterrupt(u8 Copy_u8IntNumber);
void MNVIC_setPendingFlag(u8 Copy_u8IntNumber);
void MNVIC_clearPendingFlag(u8 Copy_u8IntNumber);
u8 MNVIC_getActiveFlag(u8 Copy_u8IntNumber);
void MNVIC_setPriority(s8 Copy_s8IntID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority, u32 Copy_u32Group);

/* Macros written to SCB_AIRCR to define number of groups and sub groups */

#define Group4Sub0 0x05FA0300
#define Group3Sub1 0x05FA0400
#define Group2Sub2 0x05FA0500
#define Group1Sub3 0x05FA0600
#define Group0Sub4 0x05FA0700

#define MNVIC_ADC1_2_GIN 18

#endif /* NVIC_INTERFACE_H_ */
