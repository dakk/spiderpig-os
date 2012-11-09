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
 * \file cpu.c
 * \author Davide Gessa
 * \date 11-12-09
 */
#include "archinc.h"
#include <types.h>
#include <klibc/stdio.h>
#include <klibc/string.h>
#include <arch.h>

/**
 * Copia tutti i registri in una struttura
 * 
 * \return struttura registri
 */
regs_t cpu_reg_dump()
{
	regs_t r;
	
	asm volatile("mov %%eax, %0":"=r"(r.eax));
	asm volatile("mov %%ebx, %0":"=r"(r.ebx));
	asm volatile("mov %%ecx, %0":"=r"(r.ecx));
	asm volatile("mov %%edx, %0":"=r"(r.edx));
	//asm volatile("mov %%eip, %0":"=r"(r.eip));
	asm volatile("mov %%edi, %0":"=r"(r.edi));
	asm volatile("mov %%esi, %0":"=r"(r.esi));
	asm volatile("mov %%ebp, %0":"=r"(r.ebp));
	asm volatile("mov %%esp, %0":"=r"(r.esp));
	
	asm volatile("mov %%ds, %0":"=r"(r.ds));
	asm volatile("mov %%es, %0":"=r"(r.es));
	asm volatile("mov %%fs, %0":"=r"(r.fs));
	asm volatile("mov %%gs, %0":"=r"(r.gs));

	
	return r;
}


/**
 * Esegue il commando cpuid restituendo i registre
 */
regs_t cpu_cpuid(int code)
{
	regs_t r;
	//int highest;
	asm volatile("cpuid":"=a"(r.eax),"=b"(r.ebx),
                 "=c"(r.ecx),"=d"(r.edx):"0"(code));
	//return highest;
	return r;
}


/**
 * Restituisce la frequenza di lavoro del processore
 * 
 * @return megahertz
 */
uint32_t cpu_get_freq()
{
	return 0;
}


/**
 * Restituisce una stringa con il nome del processore
 * 
 * @param name puntatore ad array di caratteri
 * @return numero caratteri
 */
uint32_t cpu_vendor_name(char *name)
{
		regs_t r = cpu_cpuid(0x00);
		
		char line1[5];
		line1[0] = ((char *) &r.ebx)[0];
		line1[1] = ((char *) &r.ebx)[1];
		line1[2] = ((char *) &r.ebx)[2];
		line1[3] = ((char *) &r.ebx)[3];
		line1[4] = '\0';

		char line2[5];
		line2[0] = ((char *) &r.ecx)[0];
		line2[1] = ((char *) &r.ecx)[1];
		line2[2] = ((char *) &r.ecx)[2];
		line2[3] = ((char *) &r.ecx)[3];
		line2[4] = '\0';
		
		char line3[5];
		line3[0] = ((char *) &r.edx)[0];
		line3[1] = ((char *) &r.edx)[1];
		line3[2] = ((char *) &r.edx)[2];
		line3[3] = ((char *) &r.edx)[3];
		line3[4] = '\0';
							
		strcpy(name, line1);
		strcat(name, line3);
		strcat(name, line2);
		return 15;
}




/**
 * Restituisce lo stato della cpu indicata
 */
uint32_t cpu_get_state(uint32_t cpu)
{
	if(cpu < cpu_num())
		return CPU_READY;
	else
		return CPU_NOTPRESENT;
}


/**
 * Restituisce il numero della prima cpu non impegnata
 */
uint32_t cpu_get_free()
{
	return 0;
}


/**
 * Ferma l'esecuzione in una cpu
 */
uint32_t cpu_stop(uint32_t cpu)
{
	return 0;
}


/**
 * Restituisce il numero di cpu
 */
uint32_t cpu_num()
{
	return 1;
}


/**
 * Esegue del codice in una determinata cpu
 */
uint32_t cpu_exec(uint32_t cpu, void *code)
{
	return 0;
}



/**
 * Sveglia una cpu
 */
uint32_t cpu_whake(uint32_t cpu)
{
	
}



/**
 * Mette a riposo una cpu
 */
uint32_t cpu_sleep(uint32_t cpu)
{
	
}



/**
 * Resetta una cpu
 */
uint32_t cpu_reset(uint32_t cpu)
{
	
}


/**
 * Id della cpu usata dal processo che la richiama
 */
uint32_t cpu_get_id()
{
	
}
