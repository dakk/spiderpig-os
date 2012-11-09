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
 * \file kernel/network/link/arp.c
 * \author Davide Gessa
 * \date 02-05-2009
 */
#include <network/net/ip.h>
#include <network/network.h>
#include <network/packet.h>
#include <network/link/arp.h>


uint32_t arp_table_pointer = 0;			///< Puntatore tabella
arp_entry_t arp_table[ARP_ELEMENTS];	///< Tabella arp


/**
 * Restituisce il mac di un ip
 */
int32_t arp_resolve(ip_t ip, mac_t hw)
{
	uint32_t i;
	
	for(i = 0; i < arp_table_pointer; i++)
	{
		if(memcmp(ip, arp_table[i].ip, ADDR_LEN) == 0)
		{
			memcpy(hw, arp_table[i].mac, 8);
			return i;
		}
	}
	return -1;
}


/**
 * Invia un arp request per un dato ip
 */
uint32_t arp_request(network_iface_t *iface, ip_t ip)
{
	
	return 0;
}


/**
 * Gestisce un pacchetto arp
 */
uint32_t arp_handle_frame(network_iface_t *iface, packet_t *p)
{
	return 0;
}
