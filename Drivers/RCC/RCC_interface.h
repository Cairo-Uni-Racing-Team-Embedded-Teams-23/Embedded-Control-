/***********************************************************
* File Name    : RCC_interface.h
* Author       : Abdallah said                            
* Version      : V01                                      
* Date         : 3/10/2022                                
* DESCRIPTION  :  Header file for the RCC driver
***********************************************************/
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/* Libraries */
#include "STD_TYPES.h"

/* MACROS */
#define RCC_AHB         0
#define RCC_APB1        1
#define RCC_APB2        2

/* Name         : RCC_voidInitSysClock
*  Input        : None
*  Output       : None
* Description   : Initialize the RCC based on the user's configuration on .config file
*/
void RCC_voidInitSysClock (void); 

/* Name         : RCC_voidEnableClock
*  Input        : Copy_u8BusId , Copy_u8PerId
*  Output       : None
* Description   : Enable clock for the selected periphral
*/
void RCC_voidEnableClock (u8 Copy_u8BusId , u8 Copy_u8PerId); 

/* Name         : RCC_voidDisableClock
*  Input        : Copy_u8BusId , Copy_u8PerId
*  Output       : None
* Description   : Disable clock for the selected periphral
*/
void RCC_voidDisableClock (u8 Copy_u8BusId , u8 Copy_u8PerId); 

#endif /* RCC_INTERFACE_H_ */