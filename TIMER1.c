/*
 * TIMER1.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include"TIMER1.h"
#include"ICU.h"
/*****************************************************************************************/
void TIMER1_vidSetCallBack(void (*ptr)(void))
{
	TIMER1_ptr = ptr;
	ICU_ptr = ptr;
}

//// Capture interrupt
//void  __vector_6(void)__attribute__( (signal,__INTR_ATTRS) );
//void __vector_6(void)
//{
//	TIMER1_ptr();
//}

// Compare match A interrupt
void  __vector_7(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_7(void)
{
	TIMER1_ptr();
}

// Compare match B interrupt
void  __vector_8(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_8(void)
{
	TIMER1_ptr();
	SET_BIT(TIFR,OCF1B);
}

// overflow interrupt
void  __vector_9(void)__attribute__( (signal,__INTR_ATTRS) );
void __vector_9(void)
{
	TIMER1_ptr();
}
/*************************************************************************************************************/
void TIMER1_u32Normal(u8 prescall)
// prescall[6] ={stop,1,8,64,256,1024}
{
	TCCR1A = 0;
	TCCR1B |= prescall ;
	// normal timer enable
	SET_BIT(TIMSK,TOIE1);
	// global enable
	SET_BIT(SREG,7);
}
/*************************************************************************************************************/
void TIMER1_u32Ctc(u8 prescall, u16 top_value,u8 WAVE1_WAVE2,u8 TIMER1A_TIMER1B)
// prescall[6] ={stop,1,8,64,256,1024}
// top_value >> range from 0 to 65536 depends on the operation u need
// WAVE1/2 >> WAVE1 for CTC on OCRA/B & WAVE2 for CTC on ICR1
// TIMER1A/B select >> TIMER1A for A & TIMER1B for B
{
	switch (WAVE1_WAVE2)
	{
	case WAVE1:
		// initializing
		TCCR1A |= (4 & 3);
		TCCR1B |= ((4 & 12)<<1) | (prescall) ;
		if (TIMER1A_TIMER1B == TIMER1A)
		{
			OCR1A = top_value;
			// CTC on OCRA timer enable
			SET_BIT(TIMSK,OCIE1A);
		}else if (TIMER1A_TIMER1B == TIMER1B)
		{///////// there is a problem in this case >> interrupt excuted once then never change////////
			OCR1B = top_value;
			// CTC on OCRB timer enable
			SET_BIT(TIMSK,OCIE1B);
		}else {}
		break;
	case WAVE2:
		// initializing
		TCCR1A = 0;
		TCCR1B |= (12 <<1) | (prescall) ;
		ICR1 = top_value;
		// CTC on ICR1 timer enable
		SET_BIT(TIMSK,TICIE1);
		break;
	default:
		// nothing
		break;
	}
	// global interrupt enable
	SET_BIT(SREG,7);
}
/*************************************************************************************************************/
u16 TIMER1_u16TimeRegesterValue(void)
{
	return TCNT1;
}
/*************************************************************************************************************/
void TIMER1_vidStop(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK &= 195;
}
/*************************************************************************************************************/
