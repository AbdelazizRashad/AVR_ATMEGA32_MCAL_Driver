/*
 * PWM2.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include"PWM2.h"


/***********************************************************************************************/
void PWM2_vidInit(u16 freq, u8 FAST_PHASE)
// prescaller[8]={0,31250,3906,976,488,244,122,30}
// FAST_PHASE mode
{
	u8 i;
	u16 prescall[8]={0,31250,3906,976,488,244,122,30};
	// set the pd7/ OC2 as output
	DIO_vidSetPinDirection(D,7,1);
	//switching mode
	switch (FAST_PHASE)
	{
	case FAST:
		SET_BIT(TCCR2,3);
		break;
	case PHASE:
		CLR_BIT(TCCR2,3);
		break;
	default:
		break;
	}
	SET_BIT(TCCR2,6);
	// clear OCR2 on compare match
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
	// clock select prescaller using bit 0,1,2 in TCCR2 register
	for (i=0;i<8;i++)
	{
		if (prescall[i] == freq)	break;
		else {}
	}
	if (i!=8)
	{
		TCCR2 |= i;		// putting the prescaller or freq
	}

}
/***********************************************************************************************/
void PWM2_vidStart(u8 duty)
{
	// duty cycle value
	OCR2= ( (f32)256 * duty)/100;
//	LCD_vidSetPosition(1,1);
//	LCD_vidWriteNumber(TCCR2);
}
/***********************************************************************************************/
void PWM2_vidStop(void)
{
	TCCR2 &= 248;	// for reseting the bit 0,1,2 for 0 prescaller
	OCR2=0;
}
/***********************************************************************************************/
