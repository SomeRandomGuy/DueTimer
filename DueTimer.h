/******************************************************************************

	Author:			Kody Bennett, Basil Hall
	Created:		1/18/13
	Last Modified:	2/18/13
	
	This library allows the use of timed interrupts on the Arduino Due 
	using the ARM processor's built in exception handeling.
	
*****************************************************************************/

#include "Arduino.h"
#ifndef COMBINATIONS
#define COMBINATIONS

void startTimer1(uint32_t frequency, volatile void (*function)());
void startTimer2(uint32_t frequency, volatile void (*function)());
void startTimer3(uint32_t frequency, volatile void (*function)());
void startTimer4(uint32_t frequency, volatile void (*function)());
void startTimer5(uint32_t frequency, volatile void (*function)());
void startTimer6(uint32_t frequency, volatile void (*function)());
void startTimer7(uint32_t frequency, volatile void (*function)());
void startTimer8(uint32_t frequency, volatile void (*function)());
void startTimer9(uint32_t frequency, volatile void (*function)());

void stopTimer1();
void stopTimer2();
void stopTimer3();
void stopTimer4();
void stopTimer5();
void stopTimer6();
void stopTimer7();
void stopTimer8();
void stopTimer9();

#endif
