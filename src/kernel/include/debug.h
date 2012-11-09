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
 * \file debug.h
 * \author Davide Gessa
 * \date 10-12-09
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <types.h>
#include <config.h>


#define BOCHS_IODEBUG_PORT	0x8A00
#ifdef DEBUG
	#define DEBUGP(x) 			debug_puts(x)
#else
	#define DEBUGP(x)			
#endif

#define DEBUGF_PHYS_ALLOC_LIST		0x01
#define DEBUGF_CPU_DUMP				0x02
#define DEBUGF_MEM_DUMP				0x03


uint32_t debug_ioctl(uint32_t, char *, uint32_t);
void debug_putchar(char);
void debug_puts(char *);
void debug_init();
void debug_ist_trace(uint8_t);
void debug_reg_trace(uint8_t);

#endif
