/**
 * \file kernel/arch/x86/timer.c
 * \author Davide Gessa
 * \date 10-19-09
 */
#include "archinc.h"
#include <types.h>
#include <arch.h>
#include <task/task.h>


uint32_t pit_tick = 0;		///< Contatore dei PIT


/**
 * La callback del timer chiamata ad ogni interruzione
 */
static void timer_callback(regs_t *regs)
{
	task_switch(regs);
	
	pit_tick++;
	
	if(pit_tick%100 == 0)
	{
		clock_data.seconds++;
		if(clock_data.seconds >= 60)
		{
			clock_data.seconds = 0;
			clock_data.minutes++;
		}
		if(clock_data.minutes >= 60)
		{
			clock_data.minutes = 0;
			clock_data.hours++;
		}
		if(clock_data.hours >= 23)
		{
			clock_data.hours = 0;
			clock_data.day++;
		}
		if(clock_data.day >= 30)
		{
			clock_data.day = 0;
			clock_data.month++;
		}
		if(clock_data.month >= 12)
		{
			clock_data.month = 0;
			clock_data.year++;
		}
	}
}


/**
 * Sleep in millisecondi
 * 
 * \param ms millisecondi da attendere
 * \note 1 s = 1000 ms
 */
void arch_sleep(uint32_t ms)
{
	//uint32_t end = pit_tick + (ms / 10);
	//for(pit_tick;pit_tick < end;);	
	
	uint32_t i;
	
	for(i = 0; i < ms; i++)
	{
		uint32_t end = pit_tick + (1 / 10);
		for(pit_tick;pit_tick < end;);	
	}
}



/**
 * Inizializza il timer
 */
void timer_init()
{
	uint32_t divisor;
	uint8_t l;
	uint8_t h;
	uint32_t freq = 100;
	
	handler_reg(0, &timer_callback);

	divisor = 1193180 / freq;

	io_outb(0x43, 0x36);

	l = (uint8_t)(divisor & 0xFF);
	h = (uint8_t)((divisor>>8) & 0xFF );

	io_outb(0x40, l);
	io_outb(0x40, h);
}
 
 
 
/**
 * Restituisce il tick count corrente
 */
uint32_t arch_get_tick()
{
	return pit_tick;	
}
