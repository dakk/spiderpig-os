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
 * \file screenpig/term.h
 * \date 01-30-2010
 * \author Davide Gessa
 * \note rendering di un terminale in una finestra
 */
#ifndef SCREENPIG_TERM_H
#define SCREENPIG_TERM_H

#include <types.h>

typedef struct
{
	uint32_t x0;
	uint32_t x1;
	uint32_t y0;
	uint32_t y1;
	uint8_t char_size;
	uint32_t color;
	uint32_t color_back;
	char *buf;
	uint32_t size;	
} screen_term_t;

void term_render(screen_term_t *);

#endif
