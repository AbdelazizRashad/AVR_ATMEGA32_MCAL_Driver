/*
 * TIMER0.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include "TIMER0.h"
/*********************************************************************************************************/
void TIMER0_vidSetCallBack(void (*ptr)(void))
{
	TIMER0_ptr = ptr;
}

// CTC interrupt
void  __vector_10(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_10(void)
{
	TIMER0_ptr();
}

// overflow interrupt
void  __vector_11(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_11(void)
{
	TIMER0_ptr();
}
/*********************************************************************************************************/
void TIMER0_vidNormal(u8 prescall, u8 output_mode)
// prescall[8] = { no-source,1,8,64,256,1024,extern T0 falling edge,extern T0 clk rising edge }
{
	// mode
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	// output mode
	MAKE_BIT(TCCR0,4,output_mode % 2);
	MAKE_BIT(TCCR0,5,output_mode / 2);
	// clock select prescaller using bit 0,1,2 in TCCR0 register
	TCCR0 &= 248;	// for reseting the bit 0,1,2
	TCCR0 += prescall;		// putting the prescaller
	// interrupt mode
	SET_BIT(TIMSK,0);
	SET_BIT(SREG,7);
}
/*********************************************************************************************************/
void TIMER0_vidCtcTimeOn(u8 prescall, u8 output_mode , u8 top_value)
// prescall[8] = { no-source,1,8,64,256,1024,extern T0 falling edge,extern T0 clk rising edge }
// output_mode[4] = {OC0 (PB3) disconnected, toggle, set, clr}
// return time value
{
	// mode
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	// output mode
	MAKE_BIT(TCCR0,4,output_mode % 2);
	MAKE_BIT(TCCR0,5,output_mode / 2);
	// clock select prescaller using bit 0,1,2 in TCCR0 register
	TCCR0 &= 248;	// for reseting the bit 0,1,2
	TCCR0 += prescall;		// putting the prescaller
	OCR0 = top_value;
	// interrupt mode
	SET_BIT(TIMSK,1);
	SET_BIT(SREG,7);
}
/*********************************************************************************************************/
