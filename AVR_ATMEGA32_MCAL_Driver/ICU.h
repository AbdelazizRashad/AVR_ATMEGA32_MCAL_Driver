/*
 * ICU.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#ifndef ICU_H_
#define ICU_H_

// pointer to function for call back
void (*ICU_ptr)(void);
#define __INTR_ATTRS used,externally_visible

#define TOIE1	2
#define OCIE1B	3
#define OCIE1A	4
#define TICIE1	5
#define TOV1	2
#define OCF1B	3
#define OCF1A	4
#define ICF1	5
#define ICNC1	7
#define ICES1	6
#define ICNC1	7

void ICU_vidSetCallBack(void (*ptr)(void));
void ICU_vidInit(void);
u16 ICU_Value(void);
void ICU_Raise_Edge(void);
void ICU_Falling_Edge(void);
void ICU_Toggle_Edge(void);

#endif /* ICU_H_ */
