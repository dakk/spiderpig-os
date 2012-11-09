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
 * \file kernel/network/route.h
 * \author Davide Gessa
 * \date 02-02-2010
 */
#ifndef NETWORK_ROUTE_H
#define NETWORK_ROUTE_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/network.h>

/**
 * Un entry della routing table
 */
typedef struct route_entry_p
{
	char gw[ADDR_LEN];					///< Indirizzo gw
	char dest[ADDR_LEN];				///< Indirizzo destinazione	
	char genmask[ADDR_LEN];				///< Maschera generatrice

	uint8_t addr_len;
	uint8_t if_net;						///< Route to net o route to host?
	uint32_t flags;						///< Routing flags	
	
	network_iface_t *iface;				///< Interfaccia
	
	struct route_entry_p *next;			///< Prossima entry
} route_entry_t;


route_entry_t *route_table;

uint32_t route_iget(uint32_t, route_entry_t **);
uint32_t route_add(network_iface_t *, char *, char *, char *, uint8_t, uint32_t);
uint32_t route_del(char *);

#endif
