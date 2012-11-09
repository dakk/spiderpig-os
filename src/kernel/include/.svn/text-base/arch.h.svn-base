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
 * \file arch.h
 * \author Davide Gessa
 * \date 10-12-09
 */

#ifndef ARCH_H
#define ARCH_H

#include <types.h>

#define ARCH_X86	1
#define ARCH_X86_64	2
#define ARCH_SPARC	3

char ARCH[16];		 ///< Nome dell'architettura
char CPU_VENDOR[16]; ///< Nome del processore



/**
 * Struttura per memorizzare data e ora del sistema
 */
typedef struct
{
	uint8_t hours;			///< Ora
	uint8_t minutes;		///< Minuti
	uint8_t seconds;		///< Secondi
	uint8_t month;			///< Mese
	uint8_t day;			///< Giorno
	uint8_t year;			///< Anno
} clock_data_t;


clock_data_t clock_data;	///< Data e ora globali


/*
 * Cpu
 */
uint32_t cpu_vendor_name(char *);
uint32_t cpu_get_freq();
regs_t cpu_reg_dump();

/*
 * Input Ouput sulle porte della macchina
 */
void io_outb(uint16_t, uint8_t);
uint8_t io_inb(uint16_t);
void io_outw(uint16_t, uint16_t);
uint16_t io_inw(uint16_t);
void io_outd(uint16_t, uint32_t);
uint32_t io_ind(uint16_t);
void io_outl(uint16_t, uint64_t);
uint64_t io_inl(uint16_t);


/*
 * Handler per gli irq
 */
void handler_reg(uint8_t, void (*)(regs_t *r));
void handler_unreg(uint8_t);


/*
 * Timer e Clock
 */
void arch_sleep(uint32_t);
uint32_t arch_get_clock();
uint32_t arch_get_tick();



/*
 * Inizializza l'architettura
 */
void arch_init();
void arch_shutdown();
void arch_reboot();
void arch_standby();


/*
 * Operazioni su sistemi con piu' cpu
 */
#define CPU_USED		2
#define CPU_READY		1
#define CPU_SPLEEP		3
#define CPU_NOTPRESENT	0

uint32_t cpu_get_state(uint32_t);
uint32_t cpu_get_free();
uint32_t cpu_stop(uint32_t);
uint32_t cpu_num();
uint32_t cpu_exec(uint32_t, void *);
uint32_t cpu_whake(uint32_t);
uint32_t cpu_sleep(uint32_t);
uint32_t cpu_reset(uint32_t);
uint32_t cpu_get_id();

#endif
