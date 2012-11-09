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
#ifndef NETWORK_IPV4_H
#define NETWORK_IPV4_H

#include <types.h>
#include <config.h>
#include <network/network.h>

#define IPV4_ADDR_LEN	4

#define IPV4_PROTOCOL_ICMP	1
#define IPV4_PROTOCOL_TCP	6
#define IPV4_PROTOCOL_UDP	17
#define IPV4_PROTOCOL_IPV6	41


typedef struct
{
	uint8_t version:4;
	uint8_t head_len:4;
	uint8_t tos;				///< Type of service
	uint16_t total_len;
	uint16_t ident;
	uint8_t flags:3;
	uint16_t offset:13;
	uint8_t time_to_live;
	uint8_t protocol;
	uint16_t header_checksum;
	uint32_t source;
	uint32_t dest;
} ip_header_t;

uint32_t ip_send_frame(network_iface_t *, packet_t *, char *, uint8_t);
uint32_t ip_handle_frame(network_iface_t *, packet_t *);

#endif
