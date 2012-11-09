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
 * \file task/elf.c
 * \author Davide Gessa
 * \date 15-02-10
 */
#include <task/message.h>
#include <task/task.h>
#include <task/elf.h>
#include <video.h>
#include <debug.h>


/**
 * Check if the data is elf data
 * 
 * \return 1 if data is an elf
 */
uint32_t elf_check(char *buf)
{
	elf_header_t *header = (elf_header_t *) buf;
		
	if( (*(header->ident+1) == 'E') &&
		(*(header->ident+2) == 'L') &&
		(*(header->ident+3) == 'F') &&
		(*(header->ident) == 0x7f))
		return 1;
	
	return 0;		
}
