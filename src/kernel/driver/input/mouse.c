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
 * \file kernel/driver/hid/mouse.c
 * \author Davide Gessa
 * \date 10-12-09
 * \note Driver per i dispositivi mouse ps2
 */
#include "mouse.h"
#include <klibc/stdio.h>
#include <types.h>
#include <arch.h>
#include <video.h>
#include <driver.h>

driver_t driver_mouse = 
{
	.name = "mouse\0",
	.desc = "ps2 mouse driver\0",
	
	.probe = mouse_probe,
	.init = mouse_init,
	.ioctl = mouse_ioctl
};


uint8_t mouse_cycle;
int32_t mouse_x;
int32_t mouse_y;
uint8_t mouse_byte[3];



/**
 * 
 */
uint32_t mouse_probe(device_t *dev)
{
	return 1;	
}


/**
 * Handler del mouse
 */
static void mouse_callback(regs_t *reg)
{	
	switch(mouse_cycle)
	{
		case 0:
			mouse_byte[0]=io_inb(0x60);
			mouse_cycle++;
			break;
			
		case 1:
			mouse_byte[1]=io_inw(0x60);
			mouse_cycle++;
			break;
			
		case 2:
			mouse_byte[2] = io_inw(0x60);
			mouse_x = mouse_byte[1];
			mouse_y = mouse_byte[2];
			mouse_cycle = 0;
			//printf("%d %d\n",  mouse_x, mouse_y);
			break;
	}	
}


/**
 * 
 */
void mouse_wait(uint8_t a_type)
{
	uint32_t time_out = 100000;
	
	if(a_type == 0)
	{
		while(time_out--)
			if((io_inb(0x64) & 1) == 1) return;
		
		return;
	}
	else
	{
		while(time_out--)
		  if((io_inb(0x64) & 2) == 0) return;
		return;
	}
}


/**
 * 
 */
void mouse_write(uint8_t a_write)
{
	mouse_wait(1);
	io_outb(0x64, 0xD4);
	mouse_wait(1);
	io_outb(0x60, a_write);
}


/**
 * 
 */
uint8_t mouse_read()
{
	mouse_wait(0); 
	return io_inb(0x60);
}


/**
 * Inizializza l'handler del mouse
 */
uint32_t mouse_init()
{
	uint8_t status;
	
	mouse_wait(1);
	io_outb(0x64, 0xA8);
  
	mouse_wait(1);
	io_outb(0x64, 0x20);
	mouse_wait(0);
	status = (io_inb(0x60) | 2);
	mouse_wait(1);
	io_outb(0x64, 0x60);
	mouse_wait(1);
	io_outb(0x60, status);
  
	// Valori di default
	mouse_write(0xF6);
	mouse_read();

	// Abilita lo sacmbio dati
	mouse_write(0xF4);
	mouse_read();
	
	// Scaling 1:1
	mouse_write(0xE6);
	mouse_read();
	
	// Imposta l'handler
	handler_reg(IRQ_MOUSE, &mouse_callback);
}



/**
 * 
 */
int32_t mouse_get_x()
{
	int32_t a = mouse_x;
	mouse_x = 0;
	
	if(((mouse_packet_t *) &mouse_byte[0])->x_sign_bit)
		return a;
	else
		return -a;
}



/**
 * 
 */
int32_t mouse_get_y()
{
	int32_t a = mouse_y;
	mouse_y = 0;
	
	if(((mouse_packet_t *) &mouse_byte[0])->y_sign_bit)
		return a;
	else
		return -a;
}


/**
 * IoCTL
 */
uint32_t mouse_ioctl(device_t *d, uint32_t call, uint32_t a, uint32_t b)
{
	switch(call)
	{
		case MOUSE_IOCTL_GETX:
			return mouse_get_x();

		case MOUSE_IOCTL_GETY:
			return mouse_get_y();

		case MOUSE_IOCTL_READ:
			return mouse_read();

		case MOUSE_IOCTL_WRITE:
			mouse_write(a);
			return 0;

		default:
			break;
	}	
}
