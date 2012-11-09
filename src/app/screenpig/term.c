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
 * \file screenpig/term.c
 * \date 01-30-2010
 * \author Davide Gessa
 */
#include "include/term.h"
#include "include/render.h"


/**
 * Renderizza un buffer in un area
 */
void term_render(screen_term_t *term)
{
	uint32_t cur_x = term->x0;
	uint32_t cur_y = term->y0+4;
	uint32_t i;
	
	render_draw_rect_fill(term->x0, term->y0, term->x1, term->y1, term->color_back);
	
	for(i = 0; i < term->size; i++)
	{
		render_write_letter(term->char_size, term->buf[i], term->color, cur_x, cur_y);
		cur_x = cur_x + 8;
		if((cur_x + term->char_size / 2) >= term->x1 || term->buf[i] == '\n')
		{
			cur_x = term->x0;
			cur_y = cur_y + term->char_size;
		}
	}
	
}
