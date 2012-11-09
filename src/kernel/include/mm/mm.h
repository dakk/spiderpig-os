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
 * \file mm.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef MM_H
#define MM_H

#include <types.h>

void mm_init(uint32_t, uint32_t);
void mm_test();
void mm_free(void *);
void *mm_alloc(size_t);
void mm_kfree(void *);
void *mm_kalloc(size_t);
uint32_t mm_get_total_mem();
uint32_t mm_get_used_mem();
uint32_t mm_get_usable_size(void *);
void show_used_memory();

#endif
