/***********************************************************
* File Name    : CURT_ADC_private.h
* Author       : Abdallah said & Shehab Aldeen                            
* Version      : V01                                      
* Date         : 10/11/2022                                
* DESCRIPTION  :  Header file for the ADC driver
***********************************************************/

#ifndef CURT_ADC_PRIVATE_H_
#define CURT_ADC_PRIVATE_H_

/*    Libraries     */

#include "STD_TYPES.h"


/***************** ADCx BASE ADDRESS *************************/
#define ADC1_BASEADDRESS     0x40012400
#define ADC2_BASEADDRESS     0x40012800
#define ADC3_BASEADDRESS     0x40013C00


/***************** Register Definitions *********************
 *
 * 		   SR    ------> Status Register
 * 		   CR1   ------> Control Register 1
 * 		   CR2 	 ------> Control Register 2
 * 		   SMPR1 ------> Sample Time Register 1
 * 		   SMPR2 ------> Sample Time Register 2
 * 		   JOFR1 ------> Injected Channel Data Offset Register 1
 * 		   JOFR2 ------> Injected Channel Data Offset Register 2
 * 		   JOFR3 ------> Injected Channel Data Offset Register 3
 * 		   JOFR4 ------> Injected Channel Data Offset Register 4
 * 		   HTR 	 ------> Watchdog High Threshold Register
 * 		   LTR 	 ------> Watchdog Low Threshold Register
 * 		   SQR1  ------> Regular Sequence Register 1
 * 		   SQR2  ------> Regular Sequence Register 2
 * 		   SQR3  ------> Regular Sequence Register 3
 * 		   JSQR  ------> Injected Sequence Register
 * 		   JDR1  ------> Injected Data Register 1
 * 		   JDR2  ------> Injected Data Register 2
 * 		   JDR3  ------> Injected Data Register 3
 * 		   JDR4  ------> Injected Data Register 4
 * 		   DR 	 ------> Regular Data Register
 * 
 ***********************************************************/
typedef struct 
{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR1;
	volatile u32 JOFR2;
	volatile u32 JOFR3;
	volatile u32 JOFR4;
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR1;
	volatile u32 SQR2;
	volatile u32 SQR3;
	volatile u32 JSQR;
	volatile u32 JDR1;
	volatile u32 JDR2;
	volatile u32 JDR3;
	volatile u32 JDR4;
	volatile u32 DR;
}ADC_TypeDef;

#define ADC1 			((ADC_TypeDef	*) ADC1_BASEADDRESS)
#define ADC2 			((ADC_TypeDef	*) ADC2_BASEADDRESS)
#define ADC3 			((ADC_TypeDef	*) ADC3_BASEADDRESS)


/*********************** ADC Modes **************************
 * options:
 * 		   0 ------> SINGLE Channel
 * 		   1 ------> CONTINOUS Channel 
 ***********************************************************/
typedef enum {
	SINGLE_CONVERSION ;
	CONTINOUS_CONVERSION 
}ADC_ModeTypeDef


/********************* CHANNELS Modes ***********************
 * options:
 * 		   0 ------> SINGLE CHANNEL 
 * 		   1 ------> MULTIPLE CHANNEL
 ***********************************************************/
typedef enum {
	SINGLE_CHANNEL ;
	MUTLIPLE_CHANNEL  
}ADC_ChannelsModeTypeDef


/************** Regular Channel   *****************
 * options:
 * 		   0000 ------> 1 channel
 * 		   0001 ------> 2 channel
 * 		   0010 ------> 3 channel
 * 		   0011 ------> 4 channel
 * 		   0100 ------> 5 channel
 * 		   0101 ------> 6 channel
 * 		   0110 ------> 7 channel
 * 		   0111 ------> 8 channel
 * 		   1000 ------> 9 channel
 * 		   1001 ------> 10 channel
 * 		   1010 ------> 11 channel
 * 		   1011 ------> 12 channel
 * 		   1100 ------> 13 channel
 * 		   1101 ------> 14 channel
 * 		   1110 ------> 15 channel
 * 		   1111 ------> 16 channel
 ***********************************************************/

 typedef enum {
	One_Channel ;
	Two_Channel;
	Three_Channel;
	Four_Channel;
	Five_Channel;
	Six_Channel ;
	Seven_Channel ;
	Eight_Channel ;
	Nine_Channel ;
	Ten_Channel ;
	Eleven_Channel ;
	Twelve_Channel ;
	Thirteen_Channel ;
	Fourteen_Channel ;
	Fifteen_Channel ;
	Sicteen_Channel 
}ADC_RegularNumberOfChannel


/************** Injected Channel  *****************
 * options:
 * 		   00 ------> 1  Channel
 * 		   01 ------> 2  Channel
 * 		   10 ------> 3  Channel
 * 		   11 ------> 4  Channel
 ***********************************************************/
typedef enum {
	One_Channel ;
	Two_Channel ;
	Three_Channel ;
	Four_Channel  
}ADC_InjectedNumberOfChannel


/************** Regular Channel Sequence *****************
 * options:
 * 		   1  ------> ch1
 * 		   2  ------> ch2
 * 		   3  ------> ch3
 * 		   4  ------> ch4
 * 		   5  ------> ch5
 * 		   6  ------> ch6
 * 		   7  ------> ch7
 * 		   8  ------> ch8
 * 		   9  ------> ch9
 * 		   10 ------> ch10
 * 		   11 ------> ch11
 * 		   12 ------> ch12
 * 		   13 ------> ch13
 * 		   14 ------> ch14
 * 		   15 ------> ch15
 * 		   16 ------> ch16
 ***********************************************************/

 typedef enum {
	ch1 = 1 ;
	ch2 ;
	ch3 ;
	ch4 ;
	ch5 ;
	ch6 ;
	ch7 ;
	ch8 ;
	ch9 ;
	ch10;
	ch11;
	ch12;
	ch13;
	ch14;
	ch15;
	ch16 
	
}ADC_Sequence

/******************* Sampling Rate time *******************/
typedef enum {
	_1_cycle   ; 
	_7_cycle   ;
	_13_cycle  ;
	_28_cycle  ;
	_41_cycle  ;
	_55_cycl   ;
	_71_cycle  ;
	_239_cycle
}ADC_TimeSamplingRate

/******* External event select for regular group ************
 * options:
 * 		   000 ------> Timer 1 CC1 event
 * 		   001 ------> Timer 1 CC2 event
 *		   010 ------> Timer 1 CC3 event
 * 		   011 ------> Timer 2 CC2 event
 * 		   100 ------> Timer 3 TRGO event
 * 		   101 ------> Timer 4 CC4 event
 *		   110 ------> EXTI line 11/TIM8_TRGO event (TIM8_TRGO is available only in high-density and XLdensity devices)
 * 		   111 ------> SWSTART
 ***********************************************************/
typedef enum {
	TIM1_CC1_EVENT ;
	TIM1_CC2_EVENT ;
	TIM1_CC3_EVENT ;
	TIM2_CC2_EVENT ;
	TIM3_TRGO_EVENT;
	TIM4_CC4_EVENT ;
	EXTI_LINE_11_EVENT ;
	SWSTART;
}ADC_ExternalEventSelect

#endif /* CURT_ADC_PRIVATE_H_ */
