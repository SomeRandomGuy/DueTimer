/******************************************************************************

	Author:			Kody Bennett, Basil Hall
	Created:		1/18/13
	Last Modified:	2/18/13
	
	This library allows the use of timed interrupts on the Arduino Due 
	using the ARM processors built in exception handeling.
*******************************************************************************/

#include "DueTimer.h"

volatile void (*TC0_function)();
volatile void (*TC1_function)();
volatile void (*TC2_function)();
volatile void (*TC3_function)();
volatile void (*TC4_function)();
volatile void (*TC5_function)();
volatile void (*TC6_function)();
volatile void (*TC7_function)();
volatile void (*TC8_function)();

void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency, volatile void (*function)())
{

	pmc_set_writeprotect(false);
	pmc_enable_periph_clk((uint32_t)irq);
	TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
	uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
	TC_SetRA(tc, channel, rc/2); //50% high, 50% low
	TC_SetRC(tc, channel, rc);
	TC_Start(tc, channel);
	tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
	tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
	
	if(tc == TC0 && channel == 0)
		TC0_function = function;
		
	else if(tc == TC0 && channel == 1)
		TC1_function = function;
		
	else if(tc == TC0 && channel == 2)
		TC2_function = function;
		
	else if(tc == TC1 && channel == 0)
		TC3_function = function;
		
	else if(tc == TC1 && channel == 1)
		TC4_function = function;
		
	else if(tc == TC1 && channel == 2)
		TC5_function = function;
		
	else if(tc == TC2 && channel == 0)
		TC6_function = function;
		
	else if(tc == TC2 && channel == 1)
		TC7_function = function;
		
	else if(tc == TC2 && channel == 2)
		TC8_function = function;
		
	NVIC_EnableIRQ(irq);
	
}

void stopTimer(IRQn_Type irq)
{

	NVIC_DisableIRQ(irq);
	pmc_disable_periph_clk((uint32_t)irq);

}
	
void TC0_Handler()
{
	TC_GetStatus(TC0, 0);
	(*TC0_function)();
}

void TC1_Handler()
{
	TC_GetStatus(TC0, 1);	
	(*TC1_function)();
}
	
void TC2_Handler()
{
	TC_GetStatus(TC0, 2);
	(*TC2_function)();
}

void TC3_Handler()
{
	TC_GetStatus(TC1, 0);
	(*TC3_function)();
}

void TC4_Handler()
{
	TC_GetStatus(TC1, 1);
	(*TC4_function)();
}

void TC5_Handler()
{
	TC_GetStatus(TC1, 2);
	(*TC5_function)();
}

void TC6_Handler()
{
	TC_GetStatus(TC2, 0);
	(*TC6_function)();
}

void TC7_Handler()
{
	TC_GetStatus(TC2, 1);
	(*TC7_function)();
}

void TC8_Handler()
{
	TC_GetStatus(TC2, 2);
	(*TC8_function)();
}
