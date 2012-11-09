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
 * \file kernel/network/link/eth.h
 * \author Davide Gessa
 * \date 02-4-2010
 */
#ifndef NETWORK_ETH_H
#define NETWORK_ETH_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/network.h>
#include <network/packet.h>


typedef struct
{
	uint8_t dsap;
	uint8_t ssap;
	uint8_t control;
} llc_t;

typedef struct
{
	uint8_t preamble[7];
	uint8_t sfd;
	mac_t dest;
	mac_t source;
	uint16_t len;
	llc_t llc;
} eth_header_t;

extern netlink_t eth_linkproto;

uint32_t eth_handle_frame(network_iface_t *, packet_t *);
uint32_t eth_send_frame(network_iface_t *, packet_t *);
uint32_t eth_up(network_iface_t *);
uint32_t eth_down(network_iface_t *);

#endif
