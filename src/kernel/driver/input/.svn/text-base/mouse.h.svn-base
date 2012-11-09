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
 * \file kernel/driver/hid/mouse.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef DRIVER_HID_MOUSE_H
#define DRIVER_HID_MOUSE_H

#include <types.h>
#include <klibc/ctype.h>
#include <driver.h>

#define IRQ_MOUSE		12


#define	MOUSE_IOCTL_GETX	0x01
#define	MOUSE_IOCTL_GETY	0x02
#define	MOUSE_IOCTL_READ	0x03
#define	MOUSE_IOCTL_WRITE	0x04

		
extern driver_t driver_mouse;

/**
 * Pacchetto mouse
 */
typedef struct
{
	uint8_t y_overflow:1;
	uint8_t x_overflow:1;
	uint8_t y_sign_bit:1;
	uint8_t x_sign_bit:1;
	uint8_t alw_1:1;
	uint8_t middle_btn:1;
	uint8_t right_btn:1;
	uint8_t left_btn:1;
} mouse_packet_t;




static void mouse_callback(regs_t *);
uint32_t mouse_init();
uint8_t mouse_read();
void mouse_write(uint8_t);
void mouse_wait(uint8_t);
int32_t mouse_get_x();
int32_t mouse_get_y();
uint32_t mouse_probe(device_t *);
uint32_t mouse_ioctl(device_t *, uint32_t, uint32_t, uint32_t);

#endif
