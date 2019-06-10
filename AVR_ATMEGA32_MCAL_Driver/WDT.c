/*
 * WDT.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zizo Rashad
 */

#include"types.h"
#include"registers.h"
#include"macros.h"
#include"WDT.h"

void WDT_vidInit(u8 prescall)
// prescall[8]={16.3 ms,32.5 ms,65 ms,0.13 s,0.26 s,1 s,2.1 s}
{
	// make the prescall
	WDTCR &= 248;
	WDTCR += prescall;
	// enable wdt
	SET_BIT(WDTCR,3);
}

void WDT_vidRefresh(u8 prescall)
// prescall[8]={16.3 ms,32.5 ms,65 ms,0.13 s,0.26 s,1 s,2.1 s}
{
	// disable WDT
	WDT_vidStop();
	// enable WDT
	WDT_vidInit(prescall);
}

void WDT_vidStop(void)
{
	WDTCR = (1<<4) | (1<<3);
	WDTCR = 0;
}
