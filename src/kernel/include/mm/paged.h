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
 * \file paged.h
 * \author Davide Gessa
 * \date 10-12-09
 */
/*
 * Gestore della memoria paginata
 * 	Consente l'allocazione di pagine virtuali, utilizzabili quindi dai processi
 *  in usermode.
 */
#ifndef PAGED_H
#define PAGED_H

#include <arch.h>
#include <types.h>

#define PAGED_FLAG_PRESENT
#define PAGED_FLAG_READ
#define PAGED_FLAG_WRITE
#define PAGED_FLAG_USER
#define PAGED_FLAG_SUPER


typedef struct
{
	uint32_t present:1;
	uint32_t read_write:1;
	uint32_t user_super:1;
	uint32_t write_through:1;
	uint32_t cache_disabled:1;
	uint32_t accessed:1;
	uint32_t always0:1;
	uint32_t page_size:1; // 0 = 4 kb
	uint32_t ignored:1;
	uint32_t aviable:3;
	uint32_t page_table_addr:20;
} page_dir_entry_t;


/*
 * Page Table
 */
typedef struct
{
	uint32_t present:1;	
	uint32_t read_write:1;
	uint32_t user_super:1;
	uint32_t write_through:1;
	uint32_t chache_disabled:1;
	uint32_t accessed:1;
	uint32_t dirty:1;
	uint32_t always0:1;
	uint32_t global:1;
	uint32_t aviable:3;
	uint32_t phys_page_addr:20;
} page_table_entry_t;

typedef struct
{
	page_dir_entry_t data[1024];
} page_dir_t;

typedef struct
{
	page_table_entry_t data[1024];
} page_table_t;


void *page_get_phys_addr(void *);
void page_map_page(void *, void *, uint32_t);
void page_unmap_page(void *);
void page_fault_handler(regs_t);
void page_init();

#endif
