/*
 * DIO.h
 *
 *  Created on: Mar 22, 2019
 *      Author: zizo rashad
 */

#ifndef DIO_H_
#define DIO_H_

typedef enum
{
	A,
	B,
	C,
	D
}dio;
void DIO_vidSetPortDirection(u8 port, u8 direction);
void DIO_vidSetPortValue( u8 port, u8 value);
u8 DIO_u8ReadPortValue(u8 port);
void DIO_vidSetPinDirection(u8 port, u8 pin, u8 direction);
void DIO_vidSetPinValue(u8 port, u8 pin, u8 value);
u8 DIO_u8ReadPinValue(u8 port, u8 pin);
void DIO_vidTogllePin(u8 port, u8 pin );




#endif /* DIO_H_ */
