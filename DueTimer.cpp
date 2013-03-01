/******************************************************************************

	Author:			Kody Bennett, Basil Hall
	Created:		1/18/13
	Last Modified:	2/28/13
	
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

/*
 * As demonstrated by RCArduino:
 * pick clock that provides the least error for specified frequency.
 */
uint8_t pickClock(uint32_t frequency, uint32_t& retRC)
{
	/*
	    Timer		Definition
	    TIMER_CLOCK1	MCK/2
	    TIMER_CLOCK2	MCK/8
	    TIMER_CLOCK3	MCK/32
	    TIMER_CLOCK4	MCK/128
	*/
	struct 
	{
		uint8_t flag;
		uint8_t divisor;
	} 
	clockConfig[] = {
		{ TC_CMR_TCCLKS_TIMER_CLOCK1, 2 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK2, 8 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK3, 32 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK4, 128 }
	};
	int clkId = 3;
	int bestClock = 3;
	float bestError = 1.0;
	do 
	{
		float ticks = (float) VARIANT_MCK / (float) frequency / (float) clockConfig[clkId].divisor;
		float error = abs(ticks - round(ticks));
		if (abs(error) < bestError) 
		{
			bestClock = clkId;
			bestError = error;
		}
	} while (clkId-- > 0);
	float ticks = (float) VARIANT_MCK / (float) frequency / (float) clockConfig[bestClock].divisor;
	retRC = (uint32_t) round(ticks);
	return clockConfig[bestClock].flag;
}


void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency)
{
	pmc_set_writeprotect(false);
	pmc_enable_periph_clk((uint32_t)irq);
	uint32_t rc = 0;
	uint8_t clock = pickClock(frequency, rc);
	
	TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | clock);
	TC_SetRA(tc, channel, rc/2); //50% high, 50% low
	TC_SetRC(tc, channel, rc);
	TC_Start(tc, channel);
	tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
	tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
		
	NVIC_EnableIRQ(irq);
}

void startTimer1(uint32_t frequency, volatile void (*function)())
{
    TC0_function = function;
    startTimer(TC0, 0, TC0_IRQn, frequency);
}
void startTimer2(uint32_t frequency, volatile void (*function)())
{
    TC1_function = function;
    startTimer(TC0, 1, TC1_IRQn, frequency);
}
void startTimer3(uint32_t frequency, volatile void (*function)())
{
    TC2_function = function;
    startTimer(TC0, 2, TC2_IRQn, frequency);
}
void startTimer4(uint32_t frequency, volatile void (*function)())
{
    TC3_function = function;
    startTimer(TC1, 0, TC3_IRQn, frequency);
}
void startTimer5(uint32_t frequency, volatile void (*function)())
{
    TC4_function = function;
    startTimer(TC1, 1, TC4_IRQn, frequency);
}
void startTimer6(uint32_t frequency, volatile void (*function)())
{
    TC5_function = function;
    startTimer(TC1, 2, TC5_IRQn, frequency);
}
void startTimer7(uint32_t frequency, volatile void (*function)())
{
    TC6_function = function;
    startTimer(TC2, 0, TC6_IRQn, frequency);
}
void startTimer8(uint32_t frequency, volatile void (*function)())
{
    TC7_function = function;
    startTimer(TC2, 1, TC7_IRQn, frequency);
}
void startTimer9(uint32_t frequency, volatile void (*function)())
{
    TC8_function = function;
    startTimer(TC2, 2, TC8_IRQn, frequency);
}

void stopTimer(IRQn_Type irq)
{
	NVIC_DisableIRQ(irq);
	pmc_disable_periph_clk((uint32_t)irq);
}

void stopTimer1()
{
    stopTimer(TC0_IRQn);
}
void stopTimer2()
{
    stopTimer(TC1_IRQn);
}
void stopTimer3()
{
    stopTimer(TC2_IRQn);
}
void stopTimer4()
{
    stopTimer(TC3_IRQn);
}
void stopTimer5()
{
    stopTimer(TC4_IRQn);
}
void stopTimer6()
{
    stopTimer(TC5_IRQn);
}
void stopTimer7()
{
    stopTimer(TC6_IRQn);
}
void stopTimer8()
{
    stopTimer(TC7_IRQn);
}
void stopTimer9()
{
    stopTimer(TC8_IRQn);
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
