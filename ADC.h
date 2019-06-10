/*
 * ADC.h
 *
 *  Created on: Apr 13, 2019
 *      Author: zizo rashad
 */

#ifndef ADC_H_
#define ADC_H_

typedef struct
{
	// volt reference
	// 0 for Aref, internal VREF turned off
	// 1 for AVCC with external capacitor, @ AREF pin
	// 2 for Reserved
	// 3 for Internal 2.56V Voltage Reference with external capacitor at AREF pin
	u8 reference;
	// left adjustment or right adjustment
	// 0 for right adjustment
	//1 for left adjustment
	u8 left_adj;
	// channels selection and gain
	// from 0 to 7 to select single ended input ADC0 : ADC7
	// from 8 to 28 to select differential ADC depends on the datesheet
	u8 chanels_selection;
	// single convertion or free running
	// 0 for single_convertion >> Bit 6 – ADSC: ADC Start Conversion
	// 1 for auto triger activated >> Bit 5 – ADATE: ADC Auto Trigger Enable
	u8 SingleConversion_or_FreeRunning;
	// pooling mode or interrupt mode
	// 0 for polling mode >> read the flag and reset it
	// 1 for interrupt mode	>> enable interrupt enable
	u8 polling_or_interrupt;
	//division factor
	// the total frequancy is divided by division factor selected by prescaller
	// from 0 to 7 for division factor indicator
	// division_factor [8]={2,2,4,8,16,32,64,128} indicator mapping of prescaler
	u8 prescaller;
}ADC;

void ADC_vidInit(ADC ADC_variables);
u8 ADC_u8GetResult( u16 * ptr, ADC ADC_variables );
u16 ADC_u16Get(void);



#endif /* ADC_H_ */
