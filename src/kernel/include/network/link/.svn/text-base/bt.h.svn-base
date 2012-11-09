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
 * \file kernel/network/link/bt.h
 * \author Davide Gessa
 * \date 02-4-2010
 */
#ifndef NETWORK_BT_H
#define NETWORK_BT_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/network.h>
#include <network/packet.h>


typedef struct
{
	uint8_t control;
} bt_header_t;

extern netlink_t bt_linkproto;

uint32_t bt_handle_frame(network_iface_t *, packet_t *);
uint32_t bt_up(network_iface_t *);
uint32_t bt_down(network_iface_t *);

#endif
