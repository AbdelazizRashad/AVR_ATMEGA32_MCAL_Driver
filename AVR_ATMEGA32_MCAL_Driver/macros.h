/*
 * macros.h
 *
 *  Created on: Mar 9, 2019
 *      Author: zizo rashad
 */

#ifndef MACROS_H_
#define MACROS_H_
#define SET_BIT(data, bit_number)			data |= ((u8) 1<<bit_number)
#define CLR_BIT(data, bit_number)			data &= ~((u8) 1<<bit_number)
#define TOGLLE_BIT(data, bit_number)		data ^= ((u8) 1<<bit_number)
#define GET_BIT(data, bit_number)			(1 & (data>>bit_number) )

#define MAKE_BIT(data,bit_number,status)	do{ switch(status) \
	{ case 0: data &= ~((u8) 1<<bit_number); break; \
	  case 1: data |= ((u8) 1<<bit_number);	 break; }} while (0)

#define power(base,pow)	do{ u8 result = base;\
	for (u8 i=1,i<pow,i++){\
	result *= base ;\
	}\
	result;\
	}while (0)

#endif /* MACROS_H_ */
