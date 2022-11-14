/***********************************************************
* File Name    : CURT_MPWM_private.h
* Author       : Mina Sobhy & Clara Issa                       
* Version      : V01                                      
* Date         : 9/11/2022                                
* DESCRIPTION  :  Header file for the Timer PWM driver private definitions
***********************************************************/
#ifndef CURT_MPWM_PRIVATE_H_
#define CURT_MPWM_PRIVATE_H_


typedef struct 
{
	u32 CEN: 	1;
	u32 UDIS:	1;
	u32 URS:	1;
	u32 OPM:	1;
	u32 DIR:	1;
	u32 CMS:	2;
	u32 ARPE:	1;
	u32 CKD:	2;
}CR1_bits;

typedef struct 
{
	u32 : 		3;
	u32 CCDS:	1;
	u32 MMS:	3;
	u32 TI1S:	1;
}CR2_bits;

typedef struct 
{
	u32 SMS: 	3;
	u32 :		1;
	u32 TS:		3;
	u32 MSM:	1;
	u32 ETF:	4;
	u32 ETPS:	2;
	u32 ECE:	1;
	u32 ETP:	1;
}SMCR_bits;

typedef struct 
{
	u32 UIE: 	1;
	u32 CC1IE:	1;
	u32 CC2IE:	1;
	u32 CC3IE:	1;
	u32 CC4IE:	1;
	u32 :		1;
	u32 TIE:	1;
	u32 :		1;
	u32 UDE: 	1;
	u32 CC1DE:	1;
	u32 CC2DE:	1;
	u32 CC3DE:	1;
	u32 CC4DE:	1;
	u32 :		1;
	u32 TDE:	1;
	u32 :	1;
}DIER_bits;

typedef struct 
{
	u32 UIF: 	1;
	u32 CC1IF:	1;
	u32 CC2IF:	1;
	u32 CC3IF:	1;
	u32 CC4IF:	1;
	u32 :		1;
	u32 TIF:	1;
	u32 :		2;
	u32 CC1OF:	1;
	u32 CC2OF:	1;
	u32 CC3OF:	1;
	u32 CC4OF:	1;
}SR_bits;

typedef struct 
{
	u32 UG: 	1;
	u32 CC1G:	1;
	u32 CC2G:	1;
	u32 CC3G:	1;
	u32 CC4G:	1;
	u32 :		1;
	u32 TG:		1;
}EGR_bits;

typedef struct 
{
	u32 CC1S: 	2;
	u32 OC1FE:	1;
	u32 OC1PE:	1;
	u32 OC1M:	3;
	u32 OC1CE:	1;
	u32 CC2S:	2;
	u32 OC2FE:	1;
	u32 OC2PE:	1;
	u32 OC2M: 	3;
	u32 OC2CE:	1;
}CCMR1_bits;

typedef struct 
{
	u32 CC3S: 	2;
	u32 OC3FE:	1;
	u32 OC3PE:	1;
	u32 OC3M:	3;
	u32 OC3CE:	1;
	u32 CC4S:	2;
	u32 OC4FE:	1;
	u32 OC4PE:	1;
	u32 OC4M: 	3;
	u32 OC4CE:	1;
}CCMR2_bits;

typedef struct 
{
	u32 CC1E: 	2;
	u32 CC1P:	1;
	u32 :		2;
	u32 CC2E:	1;
	u32 CC2P:	1;
	u32 :		2;
	u32 CC3E:	1;
	u32 CC3P:	1;
	u32 : 		2;
	u32 CC4E:	1;
	u32 CC4P:	1;
}CCER_bits;

typedef struct 
{
	u32 CNT: 	16;
}CNT_bits;


typedef struct 
{
	u32 PSC: 	16;
}PSC_bits;

typedef struct 
{
	u32 ARR: 	16;
}ARR_bits;

typedef struct 
{
	u32 REP: 	8;
}RCR_bits;

typedef struct 
{
	u32 CCR1: 	16;
}CCR1_bits;

typedef struct 
{
	u32 CCR2: 	16;
}CCR2_bits;

typedef struct 
{
	u32 CCR3: 	16;
}CCR3_bits;

typedef struct 
{
	u32 CCR4: 	16;
}CCR4_bits;

typedef struct 
{
	u32 DTG: 	8;
	u32 LOCK:	2;
	u32 OSSI:	1;
	u32 OSSR:	1;
	u32 BKE:	1;
	u32 BKP:	1;
	u32 AOE:	1;
	u32 MOE:	1;
}BDTR_bits;

typedef struct 
{
	u32 DBA: 	5;
	u32 :		3;
	u32 DBL:	5;
}DCR_bits;

typedef struct 
{
	u32 DMAR: 	16;
}DMAR_bits;


typedef struct
{
	volatile CR1_bits		CR1;
	volatile CR2_bits		CR2;
	volatile SMCR_bits		SMCR;
	volatile DIER_bits		DIER;
	volatile SR_bits		SR;
	volatile EGR_bits		EGR;
	volatile CCMR1_bits		CCMR1;
	volatile CCMR2_bits		CCMR2;
	volatile CCER_bits		CCER;
	volatile CNT_bits		CNT;
	volatile PSC_bits		PSC;
	volatile ARR_bits		ARR;
	volatile RCR_bits		RCR;
	volatile CCR1_bits		CCR1;
	volatile CCR2_bits		CCR2;
	volatile CCR3_bits		CCR3;
	volatile CCR4_bits		CCR4;
	volatile BDTR_bits		BDTR;
	volatile DCR_bits		DCR;
	volatile DMAR_bits		DMAR;
}TIM_TypeDef;



#define 	MPWM_TIM2		((TIM_TypeDef *) 0x40000000)
#define 	MPWM_TIM3		((TIM_TypeDef *) 0x40000400)
#define 	MPWM_TIM4		((TIM_TypeDef *) 0x40000800)
#define 	MPWM_TIM5		((TIM_TypeDef *) 0x40000C00)


#endif /* CURT_MPWM_PRIVATE_H_ */
