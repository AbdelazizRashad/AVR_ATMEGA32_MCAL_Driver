/*
 * DIO.c
 *
 *  Created on: Mar 22, 2019
 *      Author: zizo rashad
 */
#include"types.h"
#include"registers.h"
#include"macros.h"


void DIO_vidSetPortValue( u8 port, u8 value)
// port = 0,1,2,3 is for Port A,B,C,D respectively
//set the port value as o/p
{
	switch (port)
	{
		case 0:
		PORTA = value;
		break;
		case 1:
		PORTB = value;
		break;
		case 2:
		PORTC = value;
		break;
		case 3:
		PORTD = value;
		break;
		default:
		break;
	}
}

void DIO_vidSetPortDirection(u8 port, u8 direction)
// port = 0,1,2,3 is for Port A,B,C,D respectively
// set the port or pin direction >>( 0 for i/p , 1 for o/p for each pin )
{
	switch (port)
		{
			case 0:
			DDRA = direction;
			break;
			case 1:
			DDRB = direction;
			break;
			case 2:
			DDRC = direction;
			break;
			case 3:
			DDRD = direction;
			break;
			default:
			break;
		}
}

u8 DIO_u8ReadPortValue(u8 port)
// port = 0,1,2,3 is for Port A,B,C,D respectively
// return the value of the port as u8
{
	u8 value;
	switch (port)
		{
			case 0:
			value = PINA;
			break;
			case 1:
			value = PINB;
			break;
			case 2:
			value = PINC;
			break;
			case 3:
			value = PIND;
			break;
			default:
			break;
		}
	return value;
}
void DIO_vidSetPinDirection(u8 port, u8 pin_number, u8 direction)
// port = 0,1,2,3 is for Port A,B,C,D respectively
// pin_number from 0 to 7 (8 bit)
// set direction 0 for i/p, 1 for o/p
{
	switch (port)
	{
		case 0:
		if (direction == 1)
			SET_BIT(DDRA,pin_number);
		else if(direction == 0)
			CLR_BIT(DDRA,pin_number);
		else {}
			break;
		case 1:
			if (direction == 1)
			SET_BIT(DDRB,pin_number);
		else if(direction == 0)
			CLR_BIT(DDRB,pin_number);
		else {}
		break;
		case 2:
		if (direction == 1)
			SET_BIT(DDRC,pin_number);
		else if(direction == 0)
			CLR_BIT(DDRC,pin_number);
		else {}
		break;
		case 3:
		if (direction == 1)
			SET_BIT(DDRD,pin_number);
		else if(direction == 0)
			CLR_BIT(DDRD,pin_number);
		else {}
		break;
	}
}
void DIO_vidSetPinValue(u8 port, u8 pin_number, u8 value)

{
	switch (port)
	{
	case 0:
		if (value == 1)
			SET_BIT(PORTA,pin_number);
		else if (value == 0)
			CLR_BIT(PORTA,pin_number);
		else {}
		break;
	case 1:
		if (value == 1)
			SET_BIT(PORTB,pin_number);
		else if (value == 0)
			CLR_BIT(PORTB,pin_number);
		else {}
		break;
	case 2:
		if (value == 1)
			SET_BIT(PORTC,pin_number);
		else if (value == 0)
			CLR_BIT(PORTC,pin_number);
		else {}
		break;
	case 3:
		if (value == 1)
			SET_BIT(PORTD,pin_number);
		else if (value == 0)
			CLR_BIT(PORTD,pin_number);
		else {}
		break;

	default:
		break;

	}
}
u8 DIO_u8ReadPinValue(u8 port, u8 pin_number)
{
	u8 x;

	switch (port)
	{
	case 0:
		x = GET_BIT(PINA, pin_number);
		break;
	case 1:
		x = GET_BIT(PINB, pin_number);
		break;
	case 2:
		x = GET_BIT(PINC, pin_number );
		break;
	case 3:
		x = GET_BIT(PIND, pin_number );
		break;
	}
	return x;

	/*
	switch (port)
	{
	case 0:

		x=PINA;
		for (u8 i=0; i<pin_number; i++)
			x /= 2;
		break;
	case 1:
		x=PINB;
		for (u8 i=0; i<pin_number; i++)
			x /= 2;
		break;
	case 2:
		x=PINC;
		for (u8 i=0; i<pin_number; i++)
			x /= 2;
		break;
	case 3:
		x=PIND;
		for (u8 i=0; i<pin_number; i++)
			x /= 2;
		break;
	default :
		break;

	}
	return x%2;
	*/
}
void DIO_vidTogllePin(u8 port, u8 pin )
{
	switch (port)
	{
	case 0:
		TOGLLE_BIT(PORTA,pin);
		break;
	case 1:
		TOGLLE_BIT(PORTB,pin);
		break;
	case 2:
		TOGLLE_BIT(PORTC,pin);
		break;
	case 3:
		TOGLLE_BIT(PORTD,pin);
		break;
	}
}
