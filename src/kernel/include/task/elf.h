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
 * \file task/elf.h
 * \author Davide Gessa
 * \date 15-02-10
 */
#ifndef TASK_ELF_H
#define TASK_ELF_H

#include <types.h>

#define ELF_NIDENT		16
#define ELF_ID_MAG0		0
#define ELF_ID_MAG1		1
#define ELF_ID_MAG2		2
#define ELF_ID_MAG3		3
#define ELF_ID_CLASS	4
#define ELF_ID_DATA		5
#define ELF_ID_VERSION	6
#define ELF_ID_PAD		7
#define ELF_ID_NIDENT	16


#define ELF_TYPE_NONE		0
#define ELF_TYPE_REL		1
#define ELF_TYPE_EXEC		2
#define ELF_TYPE_DYN		3
#define ELF_TYPE_CORE		4
#define ELF_TYPE_LOPROC		0xFF00
#define ELF_TYPE_HIPROC		0xFFFF


#define ELF_MAC_NONE	0
#define ELF_MAC_M32		1
#define ELF_MAC_SPARC	2
#define ELF_MAC_386		3
#define ELF_MAC_68K		4
#define ELF_MAC_88K		5
#define ELF_MAC_860		7
#define ELF_MAC_MIPS	8


#define ELF_VER_NONE	0
#define ELF_VER_CURRENT	1


#define ELF_CLASS_NONE	0
#define ELF_CLASS_32	1
#define ELF_CLASS_64	2


#define ELF_DATA_NONE	0
#define ELF_DATA_2LSB	1
#define ELF_DATA_2MSB	2


/**
 * Struttura header elf
 */
typedef struct
{
	char ident[ELF_NIDENT];
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	uint32_t entry;
	uint32_t phoff;
	uint32_t shoff;
	uint32_t flags;
	uint16_t ehsize;
	uint16_t phentsize;
	uint16_t phnum;
	uint16_t shentsize;
	uint16_t shnum;
	uint16_t shstrndx;
} elf_header_t;


/**
 * Header di una sezione di un file elf
 */
typedef struct
{
	
} elf_section_header_t;

uint32_t elf_check(char *);

#endif
