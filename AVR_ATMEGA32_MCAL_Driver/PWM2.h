/*
 * PWM2.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef PWM2_H_
#define PWM2_H_

#define FAST	0
#define PHASE	1

void PMW2_vidStop(void);
void PWM2_vidInit(u16 freq,u8 FAST_PHASE);
void PWM2_vidStart(u8 duty);

#endif /* PWM2_H_ */
