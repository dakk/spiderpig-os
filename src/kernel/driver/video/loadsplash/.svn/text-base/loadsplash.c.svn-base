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
 * \file loadsplash.c
 * \date 01-30-2010
 * \author Davide Gessa
 */
#include "loadsplash.h"
#include "render.h"
#include <arch.h>
#include <main.h>
#include <types.h>
#include <debug.h>
#include <config.h>
#include <driver/video/vesa.h>


/**
 * Visualizza uno splash di loading
 */
int loadsplash(int x, int y)
{
	uint32_t i;
	int b;
	char *phys;
	char img[LOADSPLASH_IMGX*LOADSPLASH_IMGY*4];
	
	// Set up vesa buffer
	b = (x - 100) / 5;
	phys = (char *) (((vesa_mode_info_t *) vesa_get_mode_info())->phys_base_ptr);
	
	// Draw the bg with the image
	render_draw_rect_fill(0, 0, x, y, LOADSPLASH_BACKG); 
	if(load_raw_bitmap(LOADSPLASH_IMAGE, img, LOADSPLASH_IMGX, LOADSPLASH_IMGY))
		render_bit_map((uint32_t *) img, x / 2 - 64, y / 2 - 65, LOADSPLASH_IMGX, LOADSPLASH_IMGY);
 
	render_write_text(16, "SpiderpigOS is loading...", 0xFFFFFFF, 10, 10);
	
	memcpy(phys, render_buffer, sizeof(render_buffer));
	
	
	// Loading animation
	
	return 0;	
}
