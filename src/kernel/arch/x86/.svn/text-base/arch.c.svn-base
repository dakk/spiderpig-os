/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file kernel/arch/x86/arch.c
 * \author Davide Gessa
 * \date 10-19-09
 */
#include <main.h>
#include <syscall.h>
#include "archinc.h"
#include <arch.h>
#include <debug.h>
#include <mm/paged.h>
#include <config.h>

/**
 * Callback delle syscall
 */
extern void syscallisr();


/**
 * Inizializza l'architettura
 */
void arch_init()
{
	asm("cli");
	
	DEBUGP("arch_init()\n");
	
	ARCH[0] = 'x';
	ARCH[1] = '8';
	ARCH[2] = '6';
	ARCH[3] = '\0';
	
	cpu_vendor_name(CPU_VENDOR);
	
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();	
	timer_init();
	clock_init();
	
    idt_set_gate(SYSCALL_INT, (uint32_t) syscallisr, 0x08, 0x8E);

	#ifdef PAGING
		idt_set_gate(14, (uint32_t) page_fault_handler, 0x08, 0x8E);
	#endif
	
	asm("sti");
}



/**
 * Spegne il computer
 */
void arch_shutdown()
{
	asm("cli");
	
	asm("hlt");	
}


/**
 * Riavvia il computer
 */
void arch_reboot()
{
	
}



/**
 * Standby mode
 */
void arch_standby()
{
	
}
