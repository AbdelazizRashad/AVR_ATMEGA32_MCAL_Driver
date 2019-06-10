/*
 * ICU.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */
#include "types.h"
#include"registers.h"
#include"macros.h"
#include"ICU.h"
#include"DIO.h"
/*************************************************************************************************************/
void ICU_vidSetCallBack(void (*ptr)(void))
{
	ICU_ptr = ptr;
}
// Capture interrupt
void  __vector_6(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_6(void)
{
	ICU_ptr();
}
/*************************************************************************************************************/
void ICU_vidInit(void)
{
	DIO_vidSetPinDirection(D,6,0);
	// ICU timer enable
	SET_BIT(TIMSK,TICIE1);
	// global enable
	SET_BIT(SREG,7);
}
/********************************/
void ICD_vidNoiseCanceler(void)
{
	// activate noise canceler
	SET_BIT(TCCR1B,ICNC1);
}
/********************************/
u16 ICU_Value(void)
{
	return ICR1;
}
/********************************/
void ICU_Raise_Edge(void)
{
	SET_BIT(TCCR1B,ICES1);
}
/********************************/
void ICU_Falling_Edge(void)
{
	CLR_BIT(TCCR1B,ICES1);
}
/********************************/
void ICU_Toggle_Edge(void)
{
	TOGLLE_BIT(TCCR1B,ICES1);
}
