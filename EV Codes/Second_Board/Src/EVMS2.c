/***************************** Includes **************************************/

#include "EVMS2.h"

/****************************************************************************/

/************************* Private variables ********************************/

/* 
_ADC_BrakesValues[0] is brakes angle,
_ADC_BrakesValues[1] is brakes pressure
*/
uint16_t _ADC_BrakesValues[2]; 

/*array to carry the flags of error of PINS*/
uint8_t  _Error[3] = {0} ;    

/*array to carry the flags of control of PINS*/ 
uint8_t  _Control[2] = {0} ;   

/*Array to carry values*/
uint8_t  MSG[35] = {'\0'};

/****************************************************************************/

/*********************** Functions defintions *******************************/

/* Name        : EVMS2_init
*  Discribtion : TO initialize ADC , Transmit values of Breaks through UART 
*  Inputs 	   : NONE
*  Outputs     : NONE
*/
void EVMS2_init(void)
{  
    HAL_ADC_Start_DMA(&hadc1,&_ADC_BrakesValues,DMA_LENGTH);
	sprintf(MSG, "%d\r\n", _ADC_BrakesValues[0]);
	HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
}//end FUNC EVMS2_init

/* Name        : ADC_uint16ReadBrakes
*  Discribtion : To read value of brakes angle 
                 and  take average value of break angle on 10 stages
*  Inputs 	   : NONE
*  Outputs     : uint16_t (brakes_read/10)
*/
uint16_t ADC_uint16ReadBrakes(void)
{
    uint16_t brakes_read  = 0 ;
	
	for(int i=0;i<10;i++)
	{
		brakes_read+=_ADC_BrakesValues[0];
	}//end for 
	
	return (brakes_read/10);
	
}//end FUNC ADC_uint16ReadBrakes

/* Name        : LOGIC_uint8CheckIMD
*  Discribtion : TO compare between IMD_RELAY Feedback and IMD Feedback
*                and return TRUE or FAlSE based on the comparision
*  Inputs 	   : NONE
*  Outputs     : uint8_t
*/
uint8_t LOGIC_uint8CheckIMD()
{
	if(HAL_GPIO_ReadPin(IMD_RELAY_FB_GPIO_Port,IMD_RELAY_FB_Pin)!= HAL_GPIO_ReadPin(IMD_FB_GPIO_Port,IMD_FB_Pin))
	{
		return TRUE ;
	}//end if 
	
	return FALSE ;

}//end FUNC LOGIC_uint8CheckIMD

/* Name        : LOGIC_uint8CheckBMS 
*  Discribtion : To check on  BMS feedback
*  Inputs 	   : NONE
*  Outputs     : uint8_t
*/
uint8_t LOGIC_uint8CheckBMS()
{
	if( HAL_GPIO_ReadPin(BMS_FB_GPIO_Port,BMS_FB_Pin) == FALSE )
	{
		return TRUE ;
	}//end if 
	
	return FALSE ;
	
}//end FUNC LOGIC_uint8CheckBMS

/* Name        : LOGIC_uint8CheckBSPD
*  Discribtion : TO compare between BSPD_RELAY Feedback and BSPD Feedback
*                and return TRUE or FAlSE based on the comparision
*  Inputs 	   : NONE
*  Outputs     : uint8_t
*/
uint8_t LOGIC_uint8CheckBSPD()
{
	if(HAL_GPIO_ReadPin(BSPD_RELAY_FB_GPIO_Port,BSPD_RELAY_FB_Pin)!= HAL_GPIO_ReadPin(BSPD_FB_GPIO_Port,BSPD_FB_Pin))
	    {
	        return  TRUE ;
	    }//end if 
		
	return FALSE ;
	
}//end FUNC LOGIC_uint8CheckBSPD

/* Name        : isError
*  Discribtion : TO check if there is any error in BSPD , BMS , IMD
*  Inputs 	   : NONE
*  Outputs     : uint8_t
*/
uint8_t isError(void)
{
	_Error[BSPD_flag] = LOGIC_uint8CheckBSPD();
	_Error[BMS_flag]  = LOGIC_uint8CheckBMS() ;
	_Error[IMD_flag]  = LOGIC_uint8CheckIMD() ;
	
	if( _Error[BSPD_flag] || _Error[BMS_flag]  || _Error[IMD_flag] ) 
	{
		return ERROR; 
	}//end if 
	
    return NOERROR;
	
}//end FUNC isError


/* Name        : LOGIC_voidControlFan
*  Discribtion : TO check that the BSPD_RELAY feedback is greater than PUMP_THRESHOLD(0)
*                if : true ---------> SET FAN_RELAY 
*                     false --------> RESET FAN_RELAY
*  Inputs 	   : NONE
*  Outputs     : NONE
*/
void LOGIC_voidControlFan()
{
	if( HAL_GPIO_ReadPin(BSPD_RELAY_FB_GPIO_Port,BSPD_RELAY_FB_Pin) > FAN_THRESHOLD )
	{
		 HAL_GPIO_WritePin(FAN_RELAY_GPIO_Port,FAN_RELAY_Pin,SET);
	}//end if 
	else
	{
		HAL_GPIO_WritePin(FAN_RELAY_GPIO_Port,FAN_RELAY_Pin,RESET);
	}//end else 
		
}//end FUNC LOGIC_voidControlFan


/* Name        : LOGIC_voidControlPump
*  Discribtion : TO check that the IMD_RELAY feedback is greater than FAN_THRESHOLD(0)
*                if : true ---------> SET PUMP_RELAY 
*                     false --------> RESET PUMP_RELAY
*  Inputs 	   : NONE
*  Outputs     : NONE
*/
void LOGIC_voidControlPump()
{
	if(HAL_GPIO_ReadPin(IMD_RELAY_FB_GPIO_Port,IMD_RELAY_FB_Pin) > PUMP_THRESHOLD )
	{
		 HAL_GPIO_WritePin(PUMP_RELAY_GPIO_Port,PUMP_RELAY_Pin,SET);
	}//end if 
	else
	{
		HAL_GPIO_WritePin(PUMP_RELAY_GPIO_Port,PUMP_RELAY_Pin,RESET);
	}//end else 
		
}//end FUNC LOGIC_voidControlPump

/* Name        : LOGIC_voidControlBrakeLight
*  Discribtion : TO check that ADC Brakes_value have value  greater than Zero 
*                if : true ---------> SET BRAKE_LIGHT_RELAY 
*                     false --------> RESET BRAKE_LIGHT_RELAY
*  Inputs 	   : NONE
*  Outputs     : NONE
*/
void LOGIC_voidControlBrakeLight()
{
	
    if(ADC_uint16ReadBrakes()) // 
    {
        HAL_GPIO_WritePin(BRAKE_LIGHT_RELAY_GPIO_Port,BRAKE_LIGHT_RELAY_Pin,SET);
    }//end if
    else
    {
        HAL_GPIO_WritePin(BRAKE_LIGHT_RELAY_GPIO_Port,BRAKE_LIGHT_RELAY_Pin,RESET);
    }//end else 

}//end FUNC LOGIC_voidControlBrakeLight

/* Name        : Error_Action
*  Discribtion : TO open the shutdown circuit and terminate 
*  Inputs 	   : NONE
*  Outputs     : NONE
*/
void Error_Action(void)
{
    //It's not sure that ERROR value == 0 or 1 
    HAL_GPIO_WritePin(EVMS_RELAY_GPIO_Port,EVMS_RELAY_Pin,ERROR);
	
}//end FUNC Error_Action

