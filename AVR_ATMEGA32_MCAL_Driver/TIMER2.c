/*
 * TIMER2.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */


#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include "TIMER2.h"
/*************************************************************************************************************/
void TIMER2_vidSetCallBack(void (*ptr)(void))
{
	TIMER2_ptr = ptr;
}

// CTC interrupt
void  __vector_4(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_4(void)
{
	TIMER2_ptr();
}

// overflow interrupt
void  __vector_5(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_5(void)
{
	TIMER2_ptr();
}
/*************************************************************************************************************/
void TIMER2_vidNormal(u8 prescall, u8 output_mode)
// prescall[8] = { no-source,1,8,32,64,128,256,1024}
{
	// mode
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	// output mode
	MAKE_BIT(TCCR2,4,output_mode % 2);
	MAKE_BIT(TCCR2,5,output_mode / 2);
	// clock select prescaller using bit 0,1,2 in TCCR2 register
	TCCR2 &= 248;	// for reseting the bit 0,1,2
	TCCR2 += prescall;		// putting the prescaller
	// enable interrupt
	SET_BIT(TIMSK,6);
	SET_BIT(SREG,7);
}
/*************************************************************************************************************/
void TIMER2_vidCtcTimeOn(u8 prescall, u8 output_mode , u8 top_value )
// prescall[8] = { no-source,1,8,32,64,128,256,1024}
// output_mode[4] = {OC0 (PB3) disconnected, toggle, set, clr}
{
	// mode
	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
	// output mode
	MAKE_BIT(TCCR2,4,output_mode % 2);
	MAKE_BIT(TCCR2,5,output_mode / 2);
	// clock select prescaller using bit 0,1,2 in TCCR2 register
	TCCR2 &= 248;	// for reseting the bit 0,1,2
	TCCR2 += prescall;		// putting the prescaller
	OCR2 = top_value;
	// interrupt mode enable
	SET_BIT(TIMSK,7);
	SET_BIT(SREG,7);
}
/*************************************************************************************************************/
