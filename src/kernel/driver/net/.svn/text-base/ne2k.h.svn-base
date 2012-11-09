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
 * \file driver/net/ne2k.h
 * \author Davide Gessa
 * \date 12-05-2009
 */
#ifndef NE2K_H
#define NE2K_H

#include <types.h>
#include <driver.h>
#include <network/packet.h>

#define NE2K_RESET				0x1F
#define NE2K_DATA				0x10

#define NE2K_COMMAND     		0


/**
 * Device ne2k
 */
typedef struct
{
	
} ne2k_device_t;


extern driver_t driver_ne2k;
extern device_t device_ne2k_qemu;

static void ne2k_callback(regs_t *);
uint32_t ne2k_probe(device_t *);
uint32_t ne2k_init();
uint32_t ne2k_ioctl(device_t *, uint32_t, uint32_t, uint32_t);
uint32_t ne2k_send_packet(device_t *, packet_t *);

#endif
