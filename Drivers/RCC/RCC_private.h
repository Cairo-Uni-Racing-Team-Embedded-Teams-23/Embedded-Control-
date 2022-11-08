/***********************************************************
* File Name    : RCC_private.h
* Author       : Abdallah said                            
* Version      : V01                                      
* Date         : 3/10/2022                                
* DESCRIPTION  :  Header file for the RCC driver
***********************************************************/
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/* Register Definitions */

/***********CLOCK REGISTERS**************/
/*
        :CR & CFCR to choosing the clock source
        : AHBENR & APB2ENR & APB1ENR to enable 
            and disable clock on diff priphrals
*/
#define RCC_CR                  *(( u32*)Ox40021000)
#define RCC_CFGR                *(( u32*)Ox40021004)
#define RCC_AHBENR              *(( u32*)Ox40021014)
#define RCC_APB2ENR             *(( u32*)Ox40021018)
#define RCC_APB1ENR             *(( u32*)Ox4002101c)

/***********RESET REGISTERS**************/
#define RCC_CIR                 *(( u32*)Ox40021008)
#define RCC_APB2RSTR            *(( u32*)Ox4002100c)
#define RCC_APB1RSTR            *(( u32*)Ox40021010)
#define RCC_BDCR                *(( u32*)Ox40021020)
#define RCC_CSR                 *(( u32*)Ox40021024)

/* Clock Types */
#define         RCC_HSE_CRYSTAL         0
#define         RCC_HSE_RC              1
#define         RCC_HSI                 2
#define         RCC_PLL                 3

/* PLL Options */
#define         RCC_PLL_IN_HSE_DIV_2    0
#define         RCC_PLL_IN_HSI_DIV_2    1
#define         RCC_PLL_IN_HSI          2


#endif /* RCC_PRIVATE_H_ */