/*
 * PWM0.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef PWM0_H_
#define PWM0_H_

#define FAST	0
#define PHASE	1

void PWM0_vidInit(u16 freq, u8 FAST_PHASE);
void PWM0_vidStart(u8 duty);
void PWM0_vidStop(void);

#endif /* PWM0_H_ */
