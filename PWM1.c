/*
 * PWM1.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */
#include "types.h"
#include "DIO.h"
#include"registers.h"
#include"macros.h"
#include"PWM1.h"


/***********************************************************************************************/
void PWM1_vidInit(u8 PWM1A_PWM1B,u8 prescall, u8 generation_mode,u16 top_value)
// {1,2,3 + 10,11 (top)} for phase PWM
// {5,6,7 + 14,15 (top) } for fast pwm
// {8,9 (top) } for phase and freq pwm
{
	PWM_var.A_B = PWM1A_PWM1B;
	PWM_var.generation_mode = generation_mode;
	PWM_var.top_value = top_value;
	switch (PWM1A_PWM1B)
	{
	case PWM1A:
		DIO_vidSetPinDirection(D,5,1);
		TCCR1A |= (2<<6) | (generation_mode & 3);
		break;
	case PWM1B:
		DIO_vidSetPinDirection(D,4,1);
		TCCR1A |= (2<<4) | (generation_mode & 3);
		break;
	default:
		break;
	}
	TCCR1B |= ((generation_mode & 12)<<1) | (prescall);
}
/***********************************************************************************************/
void PWM1_vidStart(u8 duty)
{

	// {1,2,3 + 10,11 (top)} for phase PWM
	// {5,6,7 + 14,15 (top) } for fast pwm
	// {8,9 (top) } for phase and freq pwm
	// select duty cycle

	u16 volatile *ptr=0;
	if (PWM_var.A_B == PWM1A) ptr = & OCR1A;
	else if (PWM_var.A_B == PWM1B) ptr = & OCR1B;
	switch (PWM_var.generation_mode)
	{
	// phase 8-bit
	case 1:
		*ptr = ( (f32)256 * duty)/100;
		break;
	// phase 9-bit
	case 2:
		*ptr = ( (f32)512 * duty)/100;
		break;
	//phase 10-bit
	case 3:
		*ptr = ( (f32)1024 * duty)/100;
		break;

	// fast 8-bit
	case 5:
		*ptr = ( (f32)256 * duty)/100;
		break;
	// fast 9-bit
	case 6:
		*ptr = ( (f32)512 * duty)/100;
		break;
	// fast 10-bit
	case 7:
		*ptr = ( (f32)1024 * duty)/100;
		break;

	// phase and freq ICR1 is top
	case 8:
		ICR1=PWM_var.top_value;
		*ptr = ( (f32)ICR1 * duty)/100;
		break;
	// phase and freq OCR1B is top
	case 9:
		/////////// not so goood //////////////////////////////////
		if (PWM_var.A_B == PWM1A)
		{
			OCR1B=PWM_var.top_value;
			OCR1A = ( (f32)OCR1B * duty)/100;
		} else if (PWM_var.A_B == PWM1B)
		{
			OCR1A=PWM_var.top_value;
			OCR1B = ( (f32)OCR1A * duty)/100;
		}else {}
		break;

	// phase ICR is top
	case 10:
		ICR1=PWM_var.top_value;
		*ptr = ( (f32)ICR1 * duty)/100;
		break;
	// phase OCR1B is top
	case 11:
		if (PWM_var.A_B == PWM1A)
		{
			OCR1B=PWM_var.top_value;
			OCR1A = ( (f32)OCR1B * duty)/100;
		} else if (PWM_var.A_B == PWM1B)
		{
			///////////////////////////////////// problem does not work //////////////
			OCR1A=PWM_var.top_value;
			OCR1B = ( (f32)OCR1A * duty)/100;
		}else {}
		break;
	// fast ICR is top
	case 14:
		ICR1=PWM_var.top_value;
		*ptr = ( (f32)ICR1 * duty)/100;
		break;
	// faast OCR1B is top
	case 15:
		if (PWM_var.A_B == PWM1A)
		{
			///////////////////////////////////// problem does not work /////////////
			OCR1B=PWM_var.top_value;
			OCR1A = ( (f32)OCR1B * duty)/100;
		} else if (PWM_var.A_B == PWM1B)
		{
			OCR1A=PWM_var.top_value;
			OCR1B = ( (f32)OCR1A * duty)/100;
		}else {}
		break;
	default:
		break;
	}
}
/***********************************************************************************************/
void PWM1_vidStop(void)
{
	TCCR1A=0;
	TCCR1B=0;
	OCR1A=0;
	OCR1B=0;
	ICR1=0;
}
/***********************************************************************************************/
