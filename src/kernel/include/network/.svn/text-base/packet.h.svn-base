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
 * \file kernel/network/packet.h
 * \author Davide Gessa
 * \date 02-01-2010
 */
#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>


/**
 * Pacchetto
 */
typedef struct
{
	uint32_t size;
	char *data;
} packet_t;


void packet_del_header(packet_t *, uint32_t);
void packet_add_header(packet_t *, uint32_t);
packet_t *packet_create(char *, uint32_t);
uint32_t packet_checksum(packet_t *, uint32_t);

#endif
