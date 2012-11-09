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
 * \file phys.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef PHYS_H
#define PHYS_H

#include <types.h>

#define PHYS_MAX_PAGE	1048576					///< Numero massimo di pagine (4gb / 4kb / 32)
#define PHYS_PAGE_SIZE 	4						///< Dimensione pagine (kb)
#define PHYS_MAX_BLOCKS	(PHYS_MAX_PAGE / 32)	///< Numero di blocchi di 32 pagine


/**
 * Un blocco di pagine allocate ha una di queste strutture
 */
typedef struct
{
	void *address; 		///< Indirizzo dell'area
	size_t dim;			///< Dimensione dell'area
} phys_page_t;


phys_page_t phys_allocated[PHYS_MAX_BLOCKS];	///< Array che contiene le allocazioni

unsigned phys_bitmap[PHYS_MAX_PAGE]; 			///< La bitmap della memoria fisica

unsigned phys_page_number;						///< Numero di pagine

uint32_t phys_total;							///< Totale memoria del sistema

void phys_reserve(uint32_t, uint32_t);
void phys_free(void *);
void *phys_alloc(size_t);
void phys_init(uint32_t);
uint8_t phys_if_free_page(int *, int *);
uint32_t phys_get_free_pages();
uint32_t phys_first_free_alloc();

#endif
