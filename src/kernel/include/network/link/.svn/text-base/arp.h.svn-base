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
 * \file kernel/network/arp.h
 * \author Davide Gessa
 * \date 02-05-2010
 */
#ifndef NETWORK_ARP_H
#define NETWORK_ARP_H

#include <types.h>
#include <config.h>
#include <network/packet.h>
#include <network/network.h>

#define ARP_ELEMENTS	512			///< Numero massimo elementi della tabella

/**
 * Entry arp
 */
typedef struct
{
	ip_t ip;				///< Indirizzo ip
	mac_t mac;				///< Indirizzo mac
} arp_entry_t;


int32_t arp_resolve(char *, char *);
uint32_t arp_request(network_iface_t *, char *);
uint32_t arp_handle_frame(network_iface_t *, packet_t *);

#endif
