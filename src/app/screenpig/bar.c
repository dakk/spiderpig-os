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
 * \file screenpig/bar.c
 * \date 01-17-2010
 * \author Davide Gessa
 */
#include "include/render.h"
#include "include/window.h"
#include "include/bar.h"

#include <arch.h>


/**
 * Renderizza la barra
 */
void bar_render()
{
	render_draw_rect_bordered(0, 0, 1024, 13, 1, 0x0, 0x008AB8);
	
	// Visualizza la lista finestre
	window_t *t = window_list;
	uint32_t t_num = 0;
	uint32_t a = 0;
	
	while(t != NULL)
	{
		t_num++;
		t = t->next;
	}
	
	t_num = (800 - 175) / t_num;
	t = window_list;
	
	while(t != NULL)
	{
		render_write_text(16, t->label, 0, 10 + t_num * a, 3);
		render_draw_line(5 + t_num * a, 0, 5 + t_num * a, 14, 0x0);
		render_draw_line(5 - t_num * (a+1), 0, 5 - t_num * (a+1), 14, 0x0);
		a++;
		t = t->next;
	}
	
	// Ram
	render_draw_line(800 - 174, 0, 800 - 174, 14, 0x0);
	char ram[32];
	strcpy(ram, (char *) itoa(mm_get_used_mem()));
	strcat(ram, "kb/");
	strcat(ram, (char *) itoa(mm_get_total_mem()/1024));
	strcat(ram, "mb");
	render_write_text(16, ram, 0, 800 - 170, 3);
	
	// Ora
	render_draw_line(800 - 49, 0, 800 - 49, 14, 0x0);
	char time[6];
	strcpy(time, itoa(clock_data.hours));
	strcat(time, ":");
	strcat(time, itoa(clock_data.minutes));
	render_write_text(16, time, 0, 800 - 45, 3);
}
