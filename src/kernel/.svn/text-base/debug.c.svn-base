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
 * \file kernel/debug.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include <debug.h>
#include <arch.h>
#include <types.h>
#include <log.h>
#include <config.h>
#include <fs/fs.h>

/**
 * Scrive un carattere nella console di debug di bochs
 * 
 * \param c carattere da scrivere nell'interfaccia di debug
 */
void debug_putchar(char c)
{
	io_outb(0xe9, c);
}


/**
 * Scrive una stringa di debug
 * 
 * \param str stringa da scrivere
 */
void debug_puts(char *str)
{
	while(*str != '\0')
	{
		debug_putchar(*str);
		str++;
	}	

	#ifdef LOG
		if(log_stat())
			return; //log_write(str);
	#endif
}


/**
 * Inizializza l'interfaccia di debug
 */
void debug_init()
{
	io_outw(BOCHS_IODEBUG_PORT, 0x8A00);
}


/**
 * Imposta lo stato dell'interfaccia di tracing delle istruzioni
 * 
 * \param status stato da impostare
 */
void debug_ist_trace(uint8_t status)
{
	if(status)	io_outw(BOCHS_IODEBUG_PORT, 0x8AE3);
	else 		io_outw(BOCHS_IODEBUG_PORT, 0x8AE2);
}


/**
 * Imposta lo stato dell'interfaccia di tracing dei registri
 * 
 * \param status stato da impostare
 */
void debug_reg_trace(uint8_t status)
{
	if(status)
	{
		debug_ist_trace(1);
		io_outw(BOCHS_IODEBUG_PORT, 0x8AE5);
	}
	else
	{
		debug_ist_trace(0);
		io_outw(BOCHS_IODEBUG_PORT,0x8AE4);
	}
}



/**
 * Debug ioctl
 * 
 * \param func funzione da eseguire
 * \param buf buffer per l'output, e per l'input dei parametri
 * \param size dimensione buffer
 */
uint32_t debug_ioctl(uint32_t func, char *buf, uint32_t size)
{
	switch(func)
	{
		// Show allocated physical block list
		case DEBUGF_PHYS_ALLOC_LIST:
			break;
		
		default:
			break;		
	};
}
