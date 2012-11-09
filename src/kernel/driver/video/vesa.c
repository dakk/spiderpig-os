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
 * \file driver/video/vesa.c
 * \author Davide Gessa
 * \date 12-27-09
 */
#include "vesa.h"
#include <driver.h>
#include <malloc.h>
#include <types.h>
#include <string.h>

driver_t driver_vesa = 
{
	.name = "vesa\0",
	.desc = "vesa video driver\0",
	.author = "Davide Gessa",
						
	.probe = NULL,
						
	.type = DRV_TYPE_VIDEO,
	.video.put_pixel = vesa_draw_pixel,
	.video.get_pixel = vesa_get_pixel,
	.video.set_mode = vesa_set_mode
};

vesa_info_t *vci;
vesa_mode_info_t *vmi;

			
/**
 * Restituisce il puntatore alla struct mode info
 */
vesa_mode_info_t *vesa_get_mode_info()
{
	return vmi;
}


/**
 * Disegna un pixel nello schermo
 */
void vesa_draw_pixel(uint32_t x, uint32_t y, uint32_t cl)
{
	register char *ptmp;
	
	if (x < 0 || x > vmi->width || y < 0 || y > vmi->height) return;
	
	x = (x * (vmi->bits_per_pixel >> 3));
	y = (y * vmi->bytes_per_scan_line);
	
	char *asd = (char *)vmi->phys_base_ptr;
	ptmp = &asd[x+y];
	ptmp[0] = cl & 0xff;
	ptmp[1] = (cl>>8) & 0xff;
	ptmp[2] = (cl>>16) & 0xff;
}



/**
 * Restituisce il colore di un pixel
 */
uint32_t vesa_get_pixel(uint32_t x, uint32_t y)
{
	register char *ptmp;
	
	if (x < 0 || x > vmi->width || y < 0 || y > vmi->height) return 0;
	
	x = (x * (vmi->bits_per_pixel >> 3));
	y = (y * vmi->bytes_per_scan_line);
	
	char *asd = (char *)vmi->phys_base_ptr;
	*ptmp = asd[x+y];
	return *ptmp;	
}


/**
 * Imposta una modalita' vesa
 */
uint32_t vesa_set_mode(uint32_t x, uint32_t y, uint32_t bit)
{
	
}


/**
 * Inizializza il driver vesa
 */
uint32_t vesa_init(void *vbe_control_info, void *vbe_mode_info)
{
	vci = (vesa_info_t *) vbe_control_info;
	vmi = (vesa_mode_info_t *) vbe_mode_info;
}



