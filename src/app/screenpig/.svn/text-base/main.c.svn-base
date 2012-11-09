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
 * \file screenpig/include/main.c
 * \date 01-21-2010
 * \author Davide Gessa
 */
#include "include/render.h"
#include "include/window.h"
#include "include/events.h"
#include "include/term.h"
#include "include/bar.h"
#include "main.h"
#include <arch.h>
#include <driver/video/vesa.h>
#include <driver/input/keyboard.h>
#include <driver/input/mouse.h>
#include <stdio.h>


/**
 * Main di screenpig
 */
int screen_pig_main(int ax, int ay)
{
	res_x = ax/2;
	res_y = ay/2;

	if(load_raw_bitmap("/initr/cursor.raw", cursor, 13, 15))
		cursor_graphic = 1;
	else
		cursor_graphic = 0;
	
	keyboard_init();
	mouse_init();

	window_load_default_dec();
	
	cur_x = ax / 2;
	cur_y = ax / 2;
	
	window_list = NULL;
	char *phys = (char *) (((vesa_mode_info_t *) vesa_get_mode_info())->phys_base_ptr);

	window_t *a = window_new("term", 150, 150, 400, 250);
	//char buf[] = "ciaooo!! test di buffer visualizzato\na schermo, \nbla \nbla blabla asdjaskdjkassakjdkjcvkjxkjvkvdjxkkskdjfkjdfskj";
	//screen_term_t term = { a->x, a->x + a->size_x, a->y, a->y + a->size_y, 16, 0xFFFFFFF, 0x0, buf, strlen(buf) };


	window_new("pressed", 100-2, 40, 100+10, 66);
	//window_new("config", 450, 100, 300, 100);
	
			
	render_draw_rect_fill(0, 0, res_x + 2000, res_y + 2000, 0x555555);//0A8D5);
	
	char menuaa[70*70*4];
	load_raw_bitmap("/initr/menu.raw", menuaa, 70, 70);

	
	unsigned loop_n = 0;

	// Loop di rendering
	while(1)
	{
		// Sfondo
		//render_draw_rect_fill(0, 0, res_x + 2000, res_y + 2000, 0x555555);//0A8D5);

		render_draw_rect_fill(0, 0, 15, 15, 0x555555);//0A8D5);
		
		// Visualizza tutte le finestre
		window_t *win = window_list;
		
		//bar_render();

		//render_bit_map((uint32_t *) menuaa, 4, ay - 74, 70, 70);

		while(win != NULL)
		{
			//win->x++;
			window_render(win);
			win->if_updated = 1;
			win = win->next;
		}
/*		
		// Visualizza il terminale di test
		//term_render(&term);
		
		// Test di input
		char b[2];
		b[0] = 't'; //a;
		b[1] = '\0';
		
		if(a != 0)
		{
			if(loop_n % 3 == 0) render_write_text(16, "gui test!", 0, 110, 80);
			else if(loop_n % 3 == 1) render_write_text(16, "spiderpig", 0, 110, 80);
			else if(loop_n % 3 == 2) render_write_text(16, "osdev.it", 0, 110, 80);
			else if(loop_n % 3 == 3) render_write_text(16, "gui test!", 0, 110, 80);

			render_write_text(16, "key: ", 0x0, 110, 50);
			render_write_letter(16, a, 0x0, 150, 50);
			
			render_write_text(16, itoa(loop_n), 0x0, 150, 65);
			render_write_text(16, "i: ", 0x0, 110, 65);
			loop_n++;

			window_list->if_updated = 1;
		}


*/
		// Disegna il cursore
		events_step();
		render_draw_cursor(cur_x, cur_y);
		
		render_swap_buffer(phys, render_buffer, sizeof(render_buffer));
		//arch_sleep(1);
		
	}
	
	
	return 0;
}
