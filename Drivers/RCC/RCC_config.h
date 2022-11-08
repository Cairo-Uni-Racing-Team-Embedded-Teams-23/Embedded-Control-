/***********************************************************
* File Name    : RCC_config.h
* Author       : Abdallah said                            
* Version      : V01                                      
* Date         : 3/10/2022                                
* DESCRIPTION  :  Header file for the RCC driver
***********************************************************/
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

/* Options :    RCC_HSE_CRYSTAL
                RCC_HSE_RC
                RCC_HSI
                RCC_PLL
*/

#define RCC_CLOCK_TYPE        RCC_HSE_CRYSTAL

/* Frequency of external clock (HSE) (in MHz) to be used */
#define RCC_HSE_CLOCK 			16 

/* Frequency of Internal clock (HEI) (in MHz) */
#define RCC_HSI_CLOCK 			8 

/* Options :    RCC_PLL_IN_HSE_DIV_2
                RCC_PLL_IN_HSI_DIV_2
                RCC_PLL_IN_HSI               
Select Value only if you have PLL as input clock source 
*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT          RCC_PLL_IN_HSE_DIV_2
#endif

/* 
    PLL MUL VALUE 
    Options : 2 to 16 
Set Value only if you have PLL as input clock source 
*/
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL     2       
#endif

#endif /*RCC_CONFIG_H_ */