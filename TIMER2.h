/*
 * TIMER2.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#define __INTR_ATTRS used,externally_visible

// pointer to function for call back
void (*TIMER2_ptr)(void);

void TIMER2_vidSetCallBack(void (*ptr)(void));
void TIMER2_vidNormal(u8 prescall, u8 output_mode);
void TIMER2_vidCtcTimeOn(u8 prescall, u8 output_mode , u8 top_value );

#endif /* TIMER2_H_ */
