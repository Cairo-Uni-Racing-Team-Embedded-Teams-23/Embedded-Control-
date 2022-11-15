/***********************************************************
* File Name    : CURT_ADC_interface.h
* Author       : Abdallah said & Shehab Aldeen                            
* Version      : V01                                      
* Date         : 10/11/2022                                
* DESCRIPTION  :  Header file for the ADC driver
***********************************************************/

#ifndef CURT_ADC_INTERFACE_H_
#define CURT_ADC_INTERFACE_H_

/*    Libraries     */

#include "STD_TYPES.h"

/*    Functions prototypes */

/* Name         : ADC_voidInit
*  Input        : None
*  Output       : None
* Description   : Initialize the ADC based on the user's configuration on .config file
*/
void ADC_voidInit (void);

/* Name         : ADC_u32ReadData
*  Input        : None
*  Output       : u32
* Description   : Read data in ADC register after conversion
*/
u32 ADC_u32ReadData (void);

/* Name         : ADC_voidStartConversion
*  Input        : None
*  Output       : u32
* Description   : Start conversion
*/
void ADC_voidStartConversion (void);

#endif /*CURT_ADC_INTERFACE_H_*/

