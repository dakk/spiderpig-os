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
#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#define true	1
#define false	0
#define NULL	0

typedef unsigned char 	     u_char;
typedef unsigned int 	     u_int;
typedef unsigned int 	     u_int32;
typedef unsigned short       u_int16;
typedef signed char          int8_t;
typedef unsigned char        uint8_t;
typedef short                int16_t;
typedef unsigned short       uint16_t;
typedef int                  int32_t;
typedef unsigned             uint32_t;
typedef long long            int64_t;
typedef unsigned long long   uint64_t;


/**
 * Struttura dei registri della cpu (da spostare nell'area dedicata 
 * alle architetture)
 */
typedef struct
{
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t ds, es, fs, gs;
	uint32_t which_int, err_code;
	uint32_t eip, cs, eflags, user_esp, user_ss;
} __attribute__((packed)) regs_t;


#endif
