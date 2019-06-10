/*
 * PWM0.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */
#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include"PWM0.h"

void PWM0_vidInit(u16 freq,u8 FAST_PHASE)
// freq[5]={0,31250,3906,488,122,30}
{
	u8 i;
	u16 prescall[6]={0,31250,3906,488,122,30};
	// set the pb3/ OC0 as output
	DIO_vidSetPinDirection(B,3,1);
	//switching mode
	switch (FAST_PHASE)
	{
	case FAST:
		SET_BIT(TCCR0,3);
		break;
	case PHASE:
		CLR_BIT(TCCR0,3);
		break;
	default:
		break;
	}
	SET_BIT(TCCR0,6);
	// clear ocr0 on compare match
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	// clock select prescaller using bit 0,1,2 in TCCR0 register
	for (i=0;i<6;i++)
	{
		if (prescall[i] == freq)	break;
		else {}
	}
	if (i!=6)
	{
		TCCR0 |= i;		// putting the prescaller or freq
	}

}
/***********************************************************************************************/
void PWM0_vidStart(u8 duty)
{
	// duty cycle value
	OCR0= ( (f32)256 * duty)/100;
}
/***********************************************************************************************/
void PWM0_vidStop(void)
{
	TCCR0 &= 248;	// for reseting the bit 0,1,2 for 0 prescaller
	OCR0 = 0;
}
/***********************************************************************************************/
