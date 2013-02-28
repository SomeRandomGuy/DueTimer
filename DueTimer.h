/******************************************************************************

	Author:			Kody Bennett, Basil Hall
	Created:		1/18/13
	Last Modified:	2/18/13
	
	This library allows the use of timed interrupts on the Arduino Due 
	using the ARM processor's built in exception handeling.
	
	// Paramters table:
	// TC0, 0, TC0_IRQn  =>  TC0_Handler()
	// TC0, 1, TC1_IRQn  =>  TC1_Handler()
	// TC0, 2, TC2_IRQn  =>  TC2_Handler()
	// TC1, 0, TC3_IRQn  =>  TC3_Handler()
	// TC1, 1, TC4_IRQn  =>  TC4_Handler()
	// TC1, 2, TC5_IRQn  =>  TC5_Handler()
	// TC2, 0, TC6_IRQn  =>  TC6_Handler()
	// TC2, 1, TC7_IRQn  =>  TC7_Handler()
	// TC2, 2, TC8_IRQn  =>  TC8_Handler()

*****************************************************************************/

#include "Arduino.h"

// Pre:  The first three parameters must be selected from one line 
//       of the above table
// Pre:  The frequency parameter is an interger number that represents the desired number
//       function calls per second in Hertz
// Pre:  The function must recieve a function pointer to another volatile void function
// Post: The interrupt based timer is started
void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency, volatile void (*function)());

// Pre:  The parameter recieved by this function must match the one corresponding to the desired
//       timer to stop
// Post: Specified timer is disabled
void stopTimer(IRQn_Type irq);
