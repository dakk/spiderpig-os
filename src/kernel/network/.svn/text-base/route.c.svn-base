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
 * \file kernel/network/route.c
 * \author Davide Gessa
 * \date 02-02-2010
 */
#include <network/network.h>
#include <network/route.h>
#include <klibc/string.h>		
#include <klibc/stdio.h>	
#include <debug.h>			


/**
 * Aggiunge una riga nella tabella
 */
uint32_t route_add(	network_iface_t *iface, ip_t dest, ip_t gw, 
					ip_t genmask, uint8_t if_net, uint32_t flags)
{
	route_entry_t *re = (route_entry_t *) malloc(sizeof(route_entry_t));
	
	re->iface = iface;
	re->flags = flags;
	memcpy(re->gw, gw, ADDR_LEN);
	memcpy(re->dest, dest, ADDR_LEN);
	memcpy(re->genmask, genmask, ADDR_LEN);
	re->if_net = if_net;
	
	re->next = route_table;
	route_table = re;
	
	return 0;
}


/**
 * Elimina una riga della tabella di routing
 */
uint32_t route_del(ip_t dest)
{	
}


/**
 * Restituisce il puntatore alla i routing entry
 */
uint32_t route_iget(uint32_t x, route_entry_t **route)
{
	route_entry_t *cf = route_table;
	uint32_t i = 0;
	*route = NULL;
	
	while(cf != NULL)
	{
		if(i == x)
		{
			*route = cf;
			return 1;
		}
		i++;
		cf = cf->next;
	}
	return 0;	
}


