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
 * \file screenpig/window.c
 * \date 01-17-2010
 * \author Davide Gessa
 */
#include "include/render.h"
#include "include/window.h"

uint8_t win_ifgraphics = 0;


/**
 * Carica i file di default per le decorazioni
 */
void window_load_default_dec()
{
	if(!load_raw_bitmap(SP_PATH_WIN_TITLE2, win_title2, 10, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_TITLE4, win_title4, 10, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_TITLE3, win_title3, 10, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_TITLE5, win_title5, 5, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_TOP_LEFT, win_top_left, 5, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_TOP_RIGHT, win_top_right, 5, 25)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_CLOSE, win_close, 18, 20)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_HIDE, win_hide, 18, 20)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_BOTTOM, win_bottom, 5, 5)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_RIGHT, win_right, 5, 5)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_LEFT, win_left, 5, 5)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_BOTTOM_LF, win_bottom_lf, 20, 20)) return;
	if(!load_raw_bitmap(SP_PATH_WIN_BOTTOM_RT, win_bottom_rt, 20, 20)) return;
	win_ifgraphics = 1;
}



/**
 * Crea una finestra
 */
window_t *window_new(char *label, uint32_t x, uint32_t y, uint32_t size_x, uint32_t size_y)
{
	window_t *win = (window_t *) malloc(sizeof(window_t));
	
	strcpy(win->label, label);
	win->x = x;
	win->y = y;
	win->size_x = size_x;
	win->size_y = size_y;
	win->if_decorated = 1;
	win->if_updated = 1;
	
	win->next = window_list;
	window_list = win;
	return win;
}


/**
 * Elimina una finestra
 */
void window_delete(window_t *win)
{
	
	
}



/**
 * Renderizza una finestra
 */
void window_render(window_t *win)
{
	if(win->if_updated)
	{
		if(!win_ifgraphics)
		{
			render_draw_rect(win->x, win->y - 14, win->x + win->size_x, win->y, 0x00B8F5);
			render_draw_rect_bordered(win->x - 1, win->y - 14, win->x + win->size_x + 1, win->y, 1, 0x0, 0x008AB8);
			render_write_text(16, win->label, 0, win->x + 3, win->y - 11);
			render_write_text(16, "_x", 0, win->x + win->size_x - 17, win->y - 11);
			render_draw_rect_bordered(win->x - 1, win->y, win->x + win->size_x + 1, win->y + win->size_y + 1, 1, 0x0, 0xE0E0E0);
			//render_draw_rect(win->x + win->size_x - 5, win->y + win->size_y - 5, win->x + win->size_x, win->y + win->size_y, 0x0);	
			
			//render_draw_rect_fill(win->x, win->y + 14, win->x + win->size_x, win->y + win->size_y , 0x0);
			//render_write_text(16, "/dev$ ", 0xFFFFFFFFF, win->x + 2, win->y + 16);
		}
	
		else
		{
			uint32_t i;
				
			render_draw_rect_fill(win->x - 1, win->y, win->x + win->size_x + 1, win->y + win->size_y + 1, 0xE0E0E0);
			
			i = win->x + 4;
			while(i < (win->x + win->size_x - 3))
			{
				render_bit_map((uint32_t *) win_title5, i, win->y - 25, 5, 25);
				i = i+5;
			}
			
			render_bit_map((uint32_t *) win_top_left, win->x - 1, win->y - 25, 5, 25);
			render_bit_map((uint32_t *) win_top_right, win->x + win->size_x - 3, win->y - 25, 5, 25);
			render_bit_map((uint32_t *) win_close, win->x + win->size_x - 20, win->y - 22, 18, 20);
			//render_bit_map((uint32_t *) win_hide, win->x + win->size_x - 38, win->y - 22, 18, 20);
				
			i = win->x + 4;
			while(i < (win->x + win->size_x - 3))
			{
				render_bit_map((uint32_t *) win_bottom, i, win->y + win->size_y - 3, 5, 5);
				i = i+5;
			}
			
			i = win->y;
			while(i < (win->y + win->size_y - 5))
			{
				render_bit_map((uint32_t *) win_right, win->x + win->size_x - 3, i, 5, 5);
				i = i+5;
			}
			
			
			
			i = win->y;
			while(i < (win->y + win->size_y - 5))
			{
				render_bit_map((uint32_t *) win_left, win->x - 1, i, 5, 5);
				i = i+5;
			}

			render_bit_map((uint32_t *) win_title2, win->x + 5, win->y - 25, 10, 25);
			i = win->x + 15;
			while(i < (win->x + win->size_x - 40))
			{
				render_bit_map((uint32_t *) win_title3, i, win->y - 25, 10, 25);
				i = i+10;
			}
			render_bit_map((uint32_t *) win_title4, i, win->y - 25, 10, 25);
			
			
			render_bit_map((uint32_t *) win_bottom_lf, win->x - 1, win->y + win->size_y - 18, 20, 20);
			render_bit_map((uint32_t *) win_bottom_rt, win->x + win->size_x - 18, win->y + win->size_y - 18, 20, 20);
			
			render_write_text(16, win->label, 0xE0E0E0, win->x + 12, win->y - 15);
		}
		
		win->if_updated = 0;
	}
}
