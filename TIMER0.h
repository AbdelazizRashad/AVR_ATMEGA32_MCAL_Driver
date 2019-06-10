/*
 * TIMER0.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#define __INTR_ATTRS used,externally_visible
// pointer to function for call back
void (* TIMER0_ptr)(void);

#define polling 0
#define interrupt 1

void TIMER0_vidSetCallBack(void (*ptr)(void));
void TIMER0_vidNormal(u8 prescall, u8 output_mode);
void TIMER0_vidCtcTimeOn(u8 prescall, u8 output_mode, u8 time_variation );

#endif /* TIMER0_H_ */
