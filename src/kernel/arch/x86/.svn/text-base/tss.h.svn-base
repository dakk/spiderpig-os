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
 * \file kernel/arch/x86/tss.h
 * \author Davide Gessa
 * \date 10-19-09
 */
#ifndef TSS_H
#define TSS_H

#include <types.h>


/**
 * Struttura del task segment
 */
typedef struct
{
	unsigned short link;
	unsigned short link_h;

	unsigned long esp0;
	unsigned short ss0;
	unsigned short ss0_h;
	unsigned long esp1;
	unsigned short ss1;
	unsigned short ss1_h;
	unsigned long esp2;
	unsigned short ss2;
	unsigned short ss2_h;
	unsigned long cr3;
	unsigned long eip;
	unsigned long eflags;
	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;
	unsigned long esp;
	unsigned long ebp;
	unsigned long esi;
	unsigned long edi;
	unsigned short es;
	unsigned short es_h;
	unsigned short cs;
	unsigned short cs_h;
	unsigned short ss;
	unsigned short ss_h;
	unsigned short fs;
	unsigned short fs_h;
	unsigned short gs;
	unsigned short gs_h;
	unsigned short ldt;
	unsigned short ldt_h;
	unsigned short trap;
	unsigned short iomap;
} __attribute__((packed)) tss_entry_t;

//static void write_tss(int32_t, uint16_t, uint32_t);


tss_entry_t sys_tss; 		///< TSS del systema


#endif
