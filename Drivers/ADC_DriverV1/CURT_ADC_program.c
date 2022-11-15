/***********************************************************
* File Name    : CURT_ADC_program.c
* Author       : Abdallah said & Shehab Aldeen                            
* Version      : V01                                      
* Date         : 10/11/2022                                
* DESCRIPTION  :  Header file for the ADC driver
***********************************************************/

/*     Libraries    */
#include "STD_TYPES.h"

/* Lower Layer Interface Files*/

    /* No lower layers */
	
/* Own Driver Files*/	
#include "CURT_ADC_interface.h"
#include "CURT_ADC_private.h"
#include "CURT_ADC_config.h"
#include "CURT_DMA_private.h"


/* Name         : ADC_voidInit
*  Input        : None
*  Output       : None
* Description   : Initialize the ADC based on the user's configuration on .config file
*/
void ADC_voidInit (void){
	
	/********* General Configrations *************/
	
	/* 1- Set ADC conversion sequence  */
	u8 LOC_num = RESET_VALUE  ;
		
	while ( LOC_num < number_of_channel && LOC_num < = MAX_NUM_OF_SEQ_IN_SQR3 )
	{
		ADC1 -> SQR3 | = ( sequence[LOC_num] << LOC_num * NUM_OF_BITS_EACH_SEQ_SQRX ) ;
		LOC_num++ ;
	}//end while
	
	while ( LOC_num < number_of_channel && LOC_num > MAX_NUM_OF_SEQ_IN_SQR3 && LOC_num < = (MAX_NUM_OF_SEQ_IN_SQR3+MAX_NUM_OF_SEQ_IN_SQR2) )
	{
		ADC1 -> SQR2 | = ( sequence[LOC_num] << (LOC_num-MAX_NUM_OF_SEQ_IN_SQR3+1) * NUM_OF_BITS_EACH_SEQ_SQRX ) ;
		LOC_num++ ;
	}//end while
	
	while ( LOC_num < number_of_channel && LOC_num > (MAX_NUM_OF_SEQ_IN_SQR3+MAX_NUM_OF_SEQ_IN_SQR2) && LOC_num < = (MAX_NUM_OF_SEQ_IN_SQR3+MAX_NUM_OF_SEQ_IN_SQR2+MAX_NUM_OF_SEQ_IN_SQR1) )
	{
		ADC1 -> SQR1 | = ( sequence[LOC_num] << (LOC_num-MAX_NUM_OF_SEQ_IN_SQR3-MAX_NUM_OF_SEQ_IN_SQR2+1) * NUM_OF_BITS_EACH_SEQ_SQRX ) ;
		LOC_num++ ;
	}//end while
    
	/*2- Set Sampling rate for each conversion.*/
	
	LOC_num = RESET_VALUE  ;
	
	while ( LOC_num < Num_Of_channel && LOC_num < = MAX_NUM_OF_SEQ_IN_SMPR2 )
	{
		ADC1 -> SMPR2 | = ( Channel_Sampling_Rate[LOC_num] << LOC_num * NUM_OF_BITS_EACH_SEQ_SMPRX ) ;
		LOC_num++ ;
	}//end while
	
	while ( LOC_num < Num_Of_channel && LOC_num > MAX_NUM_OF_SEQ_IN_SMPR2 && LOC_num < = MAX_NUM_OF_SEQ_IN_SMPR1 )
	{
		ADC1 -> SMPR1 | = ( Channel_Sampling_Rate[LOC_num] << (LOC_num-MAX_NUM_OF_SEQ_IN_SMPR2+1) * NUM_OF_BITS_EACH_SEQ_SMPRX ) ;
		LOC_num++ ;
	}//end while
	
	/* 3- Set regular channel sequence length (L) to (number of conversions – 1). */
		ADC1 -> SQR1 | = (number_of_channel << NUM_OF_BITS_EACH_SEQ_SQRX * MAX_NUM_OF_SEQ_IN_SQR1);
		
	/* 4- Wake up ADC from power down state (ADON). */
		ADC1 -> CR2 |= 0x00000001;
	
	/* 5- Calibrate ADC (ADC_CR2_CAL). */
		ADC1 -> CR2 |= 0x00000004;
	
	/* 6- Set (ADC_CR2_ADON) bit again to start conversion */
		ADC1 -> CR2 |= 0x00000001;
	
	/* 7- To enable Continuous mode, set (ADC_CR2_CONT) bit */
		if(conversion_mode	  == CONTINOUS_CONVERSION)
		{
			ADC1 -> CR2 |= 0x00000002;
		}
	
	/************* Single Channel Configurations***************/
	if(channel_mode == SINGLE_CHANNEL)
	{
		/*Enable End of conversion Interrupt for interrupt mode*/
		ADC1 -> CR1 |= 0x00000020;
	}
	
	/************* Multiple Channel Configurations***************/
	else 
	{
		/*Set ADC to scan mode by setting (ADC_CR1_SCAN) bit.*/
		ADC1 -> CR1 |= 0x00000004;
		
		/* Enable DMA mode by Setting (ADC_CR2_DMA) bit..*/
		ADC1 -> CR2 |= 0x00000100;
		
		/* Enable DMA mode by Setting (ADC_CR2_DMA) bit..*/
		ADC1 -> CR2 |= 0x00000100;
		
		/*Disable DMA by clearing (DMA1_CCR1_EN) bit.*/
		DMA1 -> CCR1|= 0x00000001;
		
		/*Put the address of the peripheral data register (Source of the data) to (DMA1_CPAR1).*/
		DMA1 -> CPAR1 |=  ADC1->DR ;
		
		/*Put the address of the memory location (Destination of the data) to (DMA1_CMAR1) .*/
		LOC_ArrayOfData[number_of_channel] ;
		DMA1 -> CMAR1 |= LOC_ArrayOfData   ;
		
		/* Set (DMA1_CNDTR1) to the number of transfers. */
		DMA1 -> CNDTR1 |=  number_of_channel ;
		
		/*Enable memory Increment mode by setting (DMA1_CCR1_MINC) bit.*/
		DMA1 -> CCR1 |= 0x00000080;
		
		/* Enable circular mode by Setting (DMA1_CCR1_CIRC) bit. */
		DMA1 -> CCR1 |= 0x00000020;
		
		/* Select Peripheral size from options in (DMA_PSIZE_SELECTION) by writing in (DMA_CCR1_PSIZE) bits. */
		if (peripheral_size  == EIGHT_BITS )
		{
			DMA1 -> CCR1 |= 0x00000000;
		}
		else if ( peripheral_size  == SIXTEEN_BITS) 
		{
			DMA1 -> CCR1 |= 0x00000100;
		}
		else 
		{
			DMA1 -> CCR1 |= 0x00000200;
		}
		
		/*Select Memory size from options in (DMA_MSIZE_SELECTION) by writing in (DMA_CCR1_MSIZE) bits.*/
		if (peripheral_size  == EIGHT_BITS )
		{
			DMA1 -> CCR1 |= 0x00000000;
		}
		else if ( peripheral_size  == SIXTEEN_BITS) 
		{
			DMA1 -> CCR1 |= 0x00000400;
		}
		else 
		{
			DMA1 -> CCR1 |= 0x00000800;
		}
		
		/*Enable DMA Channel by Setting (DMA1_CCR1_EN) bit.*/
		DMA1 -> CCR1 |= 0x00000001;
		
		
		
	}
	
	
	
}

/* Name         : ADC_u32ReadData
*  Input        : None
*  Output       : u32
* Description   : Read data in ADC DR register after conversion
*/
u32 ADC_u32ReadData (void){
	
	/*Loops until the end of the Conversion (ADC_SR_EOC) flag is set*/
	while ((ADC1 -> SR)& (0x00000002)== TRUE);
	
	/* returns data from the ADC data register. */
	return ADC1->DR ;
	
}

/* Name         : ADC_voidStartConversion
*  Input        : None
*  Output       : u32
* Description   : Start conversion
*/
void ADC_voidStartConversion (void){
	
	/*Enable external trigger by Setting (ADC_CR2_EXTTRIG) bit in (ADC1_CR2) register.*/
	ADC1 -> CR2 |= 0x00010000;
	
	/* Select trigger mode by writing to (ADC_CR2_EXTSEL) bits in (ADC1_CR2). */
	switch(external_selection)
	{
		case(TIM1_CC1_EVENT):
			ADC1 -> CR2 |= 0x00000000;
			break;
			
		case(TIM1_CC2_EVENT):
			ADC1 -> CR2 |= 0x00020000;
			break;
			
		case(TIM1_CC3_EVENT):
			ADC1 -> CR2 |= 0x00040000;
			break;
			
		case(TIM2_CC2_EVENT):
			ADC1 -> CR2 |= 0x00060000;
			break;
			
		case(TIM3_TRGO_EVENT):
			ADC1 -> CR2 |= 0x00080000;
			break;
			
		case(TIM4_CC4_EVENT):
			ADC1 -> CR2 |= 0x000A0000;
			break;
		
		case(EXTI_LINE_11_EVENT):
			ADC1 -> CR2 |= 0x000C0000;
			break;
			
		case(SWSTART):
			ADC1 -> CR2 |= 0x000E0000;
			break;
			
		default:
			ADC1 -> CR2 |= 0x00000000;
			break;
	
	/*Start conversion by setting (ADC_CR2_SWSTART) bit. “This is done only as we use Software Start Mode”*/
	ADC1 -> CR2 |= 0x00400000;	
}

