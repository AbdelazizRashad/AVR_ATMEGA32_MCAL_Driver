/*
 * PWM1.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef PWM1_H_
#define PWM1_H_

#define PWM1A	1
#define PWM1B	2

void PWM1_vidInit(u8 PWMA_PWMB,u8 prescall, u8 generation_mode,u16 top_value);
void PWM1_vidStart(u8 duty);
void PWM1_vidStop(void);

typedef struct
{
	u8 A_B;
	u8 generation_mode;
	u16 top_value;
}PWM11;

volatile PWM11 PWM_var;
#endif /* PWM1_H_ */
