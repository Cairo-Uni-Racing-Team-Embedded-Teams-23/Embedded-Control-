/***********************************************************
* File Name    : CURT_DMA_private.h
* Author       : Abdallah said & Shehab Aldeen                            
* Version      : V01                                      
* Date         : 14/11/2022                                
* DESCRIPTION  :  Header file for the DMA driver
***********************************************************/
#ifndef CURT_DMA_PRIVATE_H_
#define CURT_DMA_PRIVATE_H_


/***************** ADCx BASE ADDRESS *************************/
#define DMA1_BASEADDRESS     0x40020000
#define DMA2_BASEADDRESS     0x40020400

/***************** Register Definitions *********************
 *
 * 		   ISR    ------> interrupt status register
 * 		   IFCR   ------> interrupt flag clear register
 * 		   CCR1   ------> channel 1 configuration register
 * 		   CNDTR1 ------> channel 1 number of data register
 * 		   CPAR1  ------> channel 1 peripheral address register
 * 		   CMAR1  ------> channel 1 memory address register
 * 		   CCR2   ------> channel 2 configuration register
 * 		   CNDTR2 ------> channel 2 number of data register
 * 		   CPAR2  ------> channel 2 peripheral address register
 * 		   CMAR2  ------> channel 2 memory address register 		   
 * 		   CCR3   ------> channel 3 configuration register
 * 		   CNDTR3 ------> channel 3 number of data register
 * 		   CPAR3  ------> channel 3 peripheral address register
 * 		   CMAR3  ------> channel 3 memory address register
 * 
 ***********************************************************/
typedef struct 
{
	volatile u32 ISR;
	volatile u32 IFCR;
	volatile u32 CCR1;
	volatile u32 CNDTR1;
	volatile u32 CPAR1;
	volatile u32 CMAR1;
	volatile u32 CCR2;
	volatile u32 CNDTR2;
	volatile u32 CPAR2;
	volatile u32 CMAR2;
	volatile u32 CCR3;
	volatile u32 CNDTR3;
	volatile u32 CPAR3;
	volatile u32 CMAR3;
}DMA_TypeDef;

#define DMA1 			((DMA_TypeDef	*) DMA1_BASEADDRESS)

/*********************** Peripheral size **************************
 * options:
 * 		   00 ------> 8-bits
 * 		   01 ------> 16-bits
 *		   10 ------> 32-bits
 ***********************************************************/
typedef enum {
	EIGHT_BITS ;
	SIXTEEN_BITS;
	THIRTYTWO_BITS
}DMA_PeripheralOrMemorySize

/*********************** Peripheral size **************************
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
}DMA_ExternalEventSelect


#endif /* CURT_DMA_PRIVATE_H_ */