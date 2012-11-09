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
 * \file lib/libc/malloc.c
 * \author Davide Gessa
 * \note Allocazione della memoria
 * \date 10-12-09
 */
#include <ctype.h>
#include <malloc.h>

/**
 * Alloca e azzera
 */
void *calloc(size_t size)
{
	int x;
	char *adr;// = (char *) mm_kalloc(size);
	char *j = adr;

	for(x = 0; x < size; x++)
	{
		*j = 0;
		j++;
	}
	return (void *) adr;
}


/**
 * Alloca
 */
void *malloc(size_t size)
{
	//printf("malloc %d\n", allocazioni);
	//return (void *) mm_kalloc(size);
}


/**
 * Rialloca
 */
/*void *realloc(void *adr, size_t size)
{
	void *new = (void *) mm_kalloc(size);
	memcpy(new, adr, size);
	//free(adr);

	return (void *) new;
}*/


/**
 * Libera
 */
void free(void *adr)
{
	//mm_kfree(adr);
}
