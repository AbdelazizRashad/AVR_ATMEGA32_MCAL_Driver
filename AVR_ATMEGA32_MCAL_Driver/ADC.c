/*
 * ADC.c
 *
 *  Created on: Apr 13, 2019
 *      Author: zizo rashad
 */
#include"types.h"
#include"registers.h"
#include"macros.h"
#include"ADC.h"
#include"DIO.h"

void ADC_vidInit(ADC ADC_variables)
// #notes: initialize variables which will not used with zero (never make it wild)
{

	// volt_reference bit 6 & 7
	ADMUX &= 63;	// CLR the bits for saftey
	ADMUX += (ADC_variables.reference << 6);
	// left or right adj on bit 5
	ADMUX &= 223;	// CLR the bits for saftey
	ADMUX += (ADC_variables.left_adj << 5);
	// chanels selection first 5 bits
	ADMUX &= 224;	// CLR the bits for saftey
	ADMUX += (ADC_variables.chanels_selection << 0);
	switch (ADC_variables.chanels_selection)
	{
	case 0 ... 7 :
		DIO_vidSetPinDirection(A,ADC_variables.chanels_selection,0);
		break;
	case 8:
		DIO_vidSetPinDirection(A,0,0);
		break;
	case 9:
		DIO_vidSetPinDirection(A,0,0);
		DIO_vidSetPinDirection(A,1,0);
		break;
	case 10:
		DIO_vidSetPinDirection(A,0,0);
		break;
	case 11:

		break;
	case 12:

		break;
	case 13:

		break;
	case 14:

		break;
	case 15:

		break;

	}
	// single conversion or free running
	if (ADC_variables.SingleConversion_or_FreeRunning == 1)
	{
		// single-conversion or auto-trigger at Bit 5 – ADATE at ADCSRA register
		MAKE_BIT(ADCSRA , 5 , ADC_variables.SingleConversion_or_FreeRunning);
		// this will be did when freerunning only and its by default the same
		// in case no use of SFIOR before, so this prevent error in this case
		CLR_BIT(SFIOR,4);
		SFIOR &= 31;
	} else{}
	// enable ADC by set bit 7 (ADEN) in ADCSRA register
	SET_BIT(ADCSRA,7);
	// start convertions
	SET_BIT(ADCSRA,6);

//	LCD_vidSetPosition(2,13);
//	LCD_vidWriteNumber(GET_BIT(ADCSRA,6));

	if (ADC_variables.polling_or_interrupt == 1)
	{
	// Interrupt Enable
	MAKE_BIT(ADCSRA ,3,ADC_variables.polling_or_interrupt);
	//glopal interrupt enable
	SET_BIT(SREG ,7);
	} else {}


	/*
// 0 for polling
// 1 for interrupt

	//  AVCC with external capicator mode
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	// right method in ADCL and ADCH by default
	CLR_BIT(ADMUX,5);
	// select chanel
	CLR_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	//ADC enable
	SET_BIT(ADCSRA,7);
	// start convertion
	SET_BIT(ADCSRA,6);
	// prescaller  128
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	switch (polling_interupt)
	{
	case 0:
		break;
	case 1:
		//global interrupt enable
		SET_BIT(SREG,7);
		// enable ADC interrupt
		SET_BIT(ADCSRA,3);
		break;
	}
	*/
}
u8 ADC_u8GetResult( u16 * ptr , ADC ADC_variables )
{
	u8 x=100;
	switch (ADC_variables.polling_or_interrupt)
	{
	case 0: // polling
		if (GET_BIT(ADCSRA,4) == 1)	// read the flag
		{
			x=1;
			if (ADC_variables.left_adj == 1)	// for left adjustment
			{
				* ptr = ( (u16) ADCL  | ( (u16) ADCH << 8 ) ) >>6 ;
			}
			else 	// for right adjustment
			{
				* ptr =  (u16) ADCL  | ( (u16) ADCH << 8 ) ;
			}
			// to make sure the unused bits equal zero
			*ptr = *ptr & 1023;
			// reset the flag by setting 1 to the bit
			SET_BIT(ADCSRA,4);
			// start conversion
			if (ADC_variables.SingleConversion_or_FreeRunning == 0)
			{
				SET_BIT(ADCSRA,6);
			}
			else {}	// free running automatic reset bit 6 @ ADCSRA
		}
		else { x=0;}
		break;
	case 1:	// interrupt
		if (ADC_variables.left_adj == 1)	// for left adjustment
		{
			* ptr = (u16) ADCL >>6 | ( (u16) ADCH << 2 ) ;
		}
		else 	// for right adjustment
		{
			* ptr =  (u16) ADCL  | ((u16) ADCH << 8 ) ;
		}
		// to make sure the unused bits equal zero
		*ptr = *ptr & 1023;
		if (ADC_variables.SingleConversion_or_FreeRunning == 0)
		{
			SET_BIT(ADCSRA,6);
		}
		else {}	// free running automatic reset bit 6 @ ADCSRA
		break;
	default:
		break;
	}
	return x;
}







/*
u8 ADC_u8GetResult( u16 * ptr, u8 polling_interrupt)
// 0 for polling
// 1 for interrupt mode
{
	u8 x=0;
	u8 adcl = ADCL;
	u8 adch = ADCH;
	adch = adch & 3;	// for make all bits zero except bit 0 and 1 still remain
	switch (polling_interrupt)
	{
	case 0:
		if (GET_BIT(ADCSRA,4)==1)	// read the flag
		{
			* ptr = ( (u16) ADCH << 8 ) | ( (u16) ADCL ) ;
			// * ptr = *ptr & 1023;
			// reset the flag
			SET_BIT(ADCSRA,4);
			// start convertion
			SET_BIT(ADCSRA,6);
			x=1;
		}
		else
		{
			x=0;
		}
		break;
	case 1:
		break;
	default:
		break;


	}
	return x;
}
u16 ADC_u16Get(void)
{
	u8 adcl = ADCL;
	u8 adch = ADCH;
	adch = adch & 3;	// for make all bits zero except bit 0 and 1 still remain
	u16 ptr = ( (u16) adch << 8 ) | ( adcl ) ;
		// * ptr = *ptr & 1023;
		// start convertion
		SET_BIT(ADCSRA,6);
		//x = 3;
		return ptr;
}
*/
