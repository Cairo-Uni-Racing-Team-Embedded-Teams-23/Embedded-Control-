/***********************************************************
* File Name    : RCC_program.c
* Author       : Abdallah said                            
* Version      : V01                                      
* Date         : 3/10/2022                                
* DESCRIPTION  :  Source file for the RCC driver
***********************************************************/

/* Libraries*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "common_macros.h"

/* Lower Layer Interface Files*/

    /* No lower layers */

/* Own Driver Files*/
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h" 


/* Name         : RCC_voidInitSysClock
*  Input        : None
*  Output       : None
* Description   : Initialize the RCC based on the user's configuration on .config file
*/
void RCC_voidInitSysClock (void)
{
    RCC_CR   = 0x00000000;                   /* Resset the RCC_CR register */
    RCC_CFGR = 0x00000000;                   /* Resset the RCC_CFGR register */
    RCC_CR   = 0x00080000;                   /* Enable clock security system */

    #if     RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
        RCC_CR   = 0x00010000;               /* Enable HSE with no Bypass */
        RCC_CFGR = 0x00000001;               /* system clock is HSE*/
        while(BIT_IS_CLEAR(RCC_CR,17));      /* Make sure PLL is ready */
    #elif   RCC_CLOCK_TYPE == RCC_HSE_RC
        RCC_CR   = 0x00050000;               /* Enable HSE with Bypass */
        RCC_CFGR = 0x00000001;               /* system clock is HSE*/
        while(BIT_IS_CLEAR(RCC_CR,17));      /* Make sure PLL is ready */
    #elif   RCC_CLOCK_TYPE == RCC_HSI
        RCC_CR   = 0x00000081;               /* Enable HSI & Trimming = 0 */
        RCC_CFGR = 0x00000000;               /* system clock is HSI*/
        while(BIT_IS_CLEAR(RCC_CR,1));       /* Make sure HSI is ready */

    #elif   RCC_CLOCK_TYPE == RCC_PLL
    /* NOTE : we should configure MUL value first then enable the PLL */

        #if RCC_PLL_INPUT  == RCC_PLL_IN_HSE_DIV_2
            /* Check if (the MUL factor > 16) ||  (the clock after scaling > 72Mhz) */
            #if (RCC_PLL_MUL_VAL > 16) || ((RCC_PLL_MUL_VAL * RCC_HSI_CLOCK ) >72)
                #error " Wrong Configrations "
            #endif

            /* Configure the multiplying factor
            *(RCC_PLL_MUL_VAL-2) as if u want to mul by 4 u should write
            * 0010(2) , if u want to mul by 5 u should write 0011 (3)  
             */
            RCC_CFGR= (RCC_PLL_MUL_VAL-2) | (RCC_CFGR & 0XFFC3FFFF);
			RCC_CFGR &= ~(1<<16)	;			/* to configure HSI/2 as Input to the PLL circuit */
        #endif  

        #if RCC_PLL_INPUT  == RCC_PLL_IN_HSI_DIV_2
            /* Check if (the MUL factor > 16) ||  (the clock after scaling > 72Mhz) */
            #if (RCC_PLL_MUL_VAL > 16) || ((RCC_PLL_MUL_VAL * RCC_HSE_CLOCK ) >72)
                #error " Wrong Configrations "
            #endif

            /* Configure the multiplying factor
            *(RCC_PLL_MUL_VAL-2) as if u want to mul by 4 u should write
            * 0010(2) , if u want to mul by 5 u should write 0011 (3)   
             */
            RCC_CFGR= (RCC_PLL_MUL_VAL-2) | (RCC_CFGR & 0XFFC3FFFF);
            RCC_CFGR |= (1<<17);			/* to make HSE clock  divided by 2 */
			RCC_CFGR |= (1<<16)	;			/* to configure HSE as Input to the PLL circuit */  
        #endif 

        #if RCC_PLL_INPUT  == RCC_PLL_IN_HSE
            /* Check if (the MUL factor > 16) ||  (the clock after scaling > 72Mhz) */
            #if (RCC_PLL_MUL_VAL > 16) || ((RCC_PLL_MUL_VAL * RCC_HSE_CLOCK ) >72)
                #error " Wrong Configrations "
            #endif

            /* Configure the multiplying factor
            *(RCC_PLL_MUL_VAL-2) as if u want to mul by 4 u should write
            * 0010(2) , if u want to mul by 5 u should write 0011 (3)  
             */
            RCC_CFGR= (RCC_PLL_MUL_VAL-2) | (RCC_CFGR & 0XFFC3FFFF);
            RCC_CFGR &= ~(1<<17);			/* to make HSE clock not divided */
			RCC_CFGR |= (1<<16)	;			/* to configure HSE as Input to the PLL circuit */  

        #endif

    #else
        #error("WRONG CLOCK TYPE !!!! ")

    #endif
    
}

/* Name         : RCC_voidEnableClock
*  Input        : Copy_u8BusId , Copy_u8PerId
*  Output       : None
* Description   : Enable clock for the selected periphral
*/
void RCC_voidEnableClock (u8 Copy_u8BusId , u8 Copy_u8PerId)
{
    if (Copy_u8PerId<=31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB :
            SET_BIT(RCC_AHBENR,Copy_u8PerId);
                break;
        
        case RCC_APB1 :
            SET_BIT(RCC_APB1ENR,Copy_u8PerId);
                break;
        
        case RCC_APB2 :
            SET_BIT(RCC_APB2ENR,Copy_u8PerId);
                break;

        default:
            /* Return Error*/
            break;
        }
    }

    else
    {
        /*Return Error*/
    }
}

/* Name         : RCC_voidDisableClock
*  Input        : Copy_u8BusId , Copy_u8PerId
*  Output       : None
* Description   : Disable clock for the selected periphral
*/ 
void RCC_voidDisableClock (u8 Copy_u8BusId , u8 Copy_u8PerId)
{
    if (Copy_u8PerId<=31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB :
            CLEAR_BIT(RCC_AHBENR,Copy_u8PerId);
                break;
        
        case RCC_APB1 :
            CLEAR_BIT(RCC_APB1ENR,Copy_u8PerId);
                break;
        
        case RCC_APB2 :
            CLEAR_BIT(RCC_APB2ENR,Copy_u8PerId);
                break;

        default:
            /* Return Error*/
            break;
        }
    }

    else
    {
        /*Return Error*/
    }
}
 