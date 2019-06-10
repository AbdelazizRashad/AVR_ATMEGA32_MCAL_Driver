/*
 * type.h
 *
 *  Created on: Apr 1, 2019
 *      Author: zizo rashad
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef	unsigned char u8;
typedef	signed char s8;
typedef	unsigned short int u16;
typedef	signed short int s16;
typedef	unsigned long int u32;
typedef	signed long int s32;
typedef	unsigned long long int u64;
typedef	signed long long int s64;
typedef	float f32;

/* all float are 4 byte in AVR ATMEGA32
 * so the next data types are invain >> keep it just for the past codes with the same types
 * for no error ,,, or u can delete then and change all f64 and f96 if it was used */
typedef	double f64;
typedef	long double f96;


#endif /* TYPES_H_ */
