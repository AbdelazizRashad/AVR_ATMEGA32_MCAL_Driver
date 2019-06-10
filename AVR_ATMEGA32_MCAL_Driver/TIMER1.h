/*

 * TIMRT1.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef TIMER1_H_
#define TIMER1_H_



// pointer to function for call back
void (*TIMER1_ptr)(void);
#define __INTR_ATTRS used,externally_visible

#define interrupt	1
#define polling 	0

#define TIMER1A	1
#define TIMER1B	2
#define WAVE1	1
#define WAVE2	2

#define TOIE1	2
#define OCIE1B	3
#define OCIE1A	4
#define TICIE1	5
#define TOV1 	2
#define OCF1B 	3
#define OCF1A 	4
#define ICF1 	5
#define ICNC1 	7
#define ICES1 	6

void TIMER1_vidSetCallBack(void (*ptr)(void));
void TIMER1_u32Normal(u8 prescall);
void TIMER1_u32Ctc(u8 prescall, u16 top_value,u8 WAVE1_WAVE2,u8 TIMER1A_TIMER1B);
u16 TIMER1_u16TimeRegesterValue(void);
void TIMER1_vidStop(void);

#endif /* TIMER1_H_ */
