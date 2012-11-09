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
 * \file screenpig/loading.c
 * \date 01-30-2010
 * \author Davide Gessa
 */
#include "main.h"
#include "include/render.h"
#include <arch.h>
#include <main.h>
#include <types.h>
#include <syscall.h>
#include <task/task.h>
#include <fs/fs.h>
#include <network/network.h>
#include <debug.h>
#include <util.h>
#include <driver.h>
#include <bish.h>
#include <config.h>
#include <driver/video/vesa.h>


/**
 * Visualizza uno splash di loading
 */
int screen_pig_loading(int x, int y)
{
	uint32_t i;
	int b;
	char *phys;
	char img[60*60*4];
	
	// Set up vesa buffer
	b = (x - 100) / 5;
	phys = (char *) (((vesa_mode_info_t *) vesa_get_mode_info())->phys_base_ptr);
	
	// Draw a panel with a text
	render_draw_rect_fill(0, 0, x, y, 0x222222);
	render_write_text(16, "SpiderpigOS is loading...", 0xFFFFFFF, 10, 10);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//render_draw_rect_fill(0, 125, x, 140, 0x444444);
	render_draw_rect_fill(0, 42, x, 143, 0x444444);
	
	
	// Filesystem
	fs_init();
	if(load_raw_bitmap(SCREENP_IMG_HARDDISK, img, 60, 60))
		render_bit_map((uint32_t *) img, b * 0 + 50, 50, 60, 60);
	render_write_text(16, "Filesystem", 0xFFFFFFF, b * 0 + 50, 130);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//arch_sleep(100000);
	
	
	// Device scanning
	device_update();
	if(load_raw_bitmap(SCREENP_IMG_MULTIMEDIA, img, 60, 60))
		render_bit_map((uint32_t *) img, b * 1 + 50, 50, 60, 60);
	render_write_text(16, "Devices", 0xFFFFFFF, b * 1 + 50, 130);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//arch_sleep(100000);
	
	
	// Network
	#ifdef NETWORK
		network_init();
	#endif
	
	if(load_raw_bitmap(SCREENP_IMG_NETWORK, img, 60, 60))
		render_bit_map((uint32_t *) img, b * 2 + 50, 50, 60, 60);
	render_write_text(16, "Network", 0xFFFFFFF, b * 2 + 50, 130);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//arch_sleep(100000);	
	
	
	// System
	if(load_raw_bitmap(SCREENP_IMG_SYSTEM, img, 60, 60))
		render_bit_map((uint32_t *) img, b * 3 + 50, 50, 60, 60);
	render_write_text(16, "System", 0xFFFFFFF, b * 3 + 50, 130);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//arch_sleep(100000);
	
	
	// Interface
	if(load_raw_bitmap(SCREENP_IMG_WINDOW, img, 60, 60))
		render_bit_map((uint32_t *) img, b * 4 + 50, 50, 60, 60);
	render_write_text(16, "Interface", 0xFFFFFFF, b * 4 + 50, 130);
	memcpy(phys, render_buffer, sizeof(render_buffer));
	//arch_sleep(100000);
		
	return 0;	
}
