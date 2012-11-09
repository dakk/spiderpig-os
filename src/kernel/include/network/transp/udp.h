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
 * \file kernel/network/transport/udp.h
 * \author Davide Gessa
 * \date 02-4-2010
 */
#ifndef NETWORK_UDP_H
#define NETWORK_UDP_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/network.h>
#include <network/socket.h>

/**
 * Header pacchetto udp
 */
typedef struct
{
	uint16_t source_port;
	uint16_t dest_port;
	uint16_t lenght;
	uint16_t checksum;
} udp_header_t;

uint32_t udp_handle_packet(network_iface_t *, packet_t *);
uint32_t udp_send_packet(socket_t *, packet_t *);

#endif
