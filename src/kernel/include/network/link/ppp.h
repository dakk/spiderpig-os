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
 * \file kernel/network/link/ppp.h
 * \author Davide Gessa
 * \date 02-4-2010
 */
#ifndef NETWORK_PPP_H
#define NETWORK_PPP_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/network.h>
#include <network/packet.h>


#define PPP_FLAG 				0x7E
#define PPP_ADDRESS_BROADCAST	0xFF
#define PPP_CONTROL_UI_FRAME	0x03
#define PPP_PROTOCOL_IP			0x0021

typedef struct
{
	uint8_t flag;
	uint8_t address;
	uint8_t control;
	uint16_t protocol;	
} ppp_header_t;

extern netlink_t ppp_linkproto;

uint32_t ppp_handle_frame(network_iface_t *, packet_t *);
uint32_t ppp_send_frame(network_iface_t *, packet_t *);
uint32_t ppp_up(network_iface_t *);
uint32_t ppp_down(network_iface_t *);

#endif
