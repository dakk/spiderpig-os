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
 * \file kernel/network/link/eth.c
 * \author Davide Gessa
 * \date 02-4-2010
 */
#include <network/network.h>
#include <network/packet.h>
#include <network/net/ipv4.h>
#include <network/link/eth.h>
#include <network/link/arp.h>


netlink_t eth_linkproto =
{
	.frame_min_size = 72,
	.frame_max_size = 1500,
	.header_size = sizeof(eth_header_t),
	
	.up = eth_up,
	.down = eth_down,
	.handle_frame = eth_handle_frame,
	.send_frame = eth_send_frame
};



/**
 * Gestisce un frame
 */
uint32_t eth_handle_frame(network_iface_t *iface, packet_t *p)
{
	
	// Estraiamo l'header
	eth_header_t *ethead = (eth_header_t *) p->data;


		
	// Inviamo il frame al protocollo specificato nel tipo
	if(ethead->len < 1500)
	{
		#ifdef TEST
		printf("eth: received packet (sizeof %d)\n", p->size);
		#endif
		
		// Togliamo l'header
		packet_del_header(p, sizeof(eth_header_t));

		ip_handle_packet(iface, p);
	}
		
		#ifdef NARP
			//arp_handle_frame(iface, p);
		#endif		
	
	return 0;
}



/**
 * Invia un frame
 */
uint32_t eth_send_frame(network_iface_t *iface, packet_t *p)
{
	// Prende l'header del pacchetto ip incapsulato per gli indirizzi
	ip_header_t *iphead = (ip_header_t *) p->data;
	
	// Aggiungiamo l'header specificando i vari campi
	packet_add_header(p, sizeof(eth_header_t));
	eth_header_t *ethead = (eth_header_t *) p->data;
	ethead->preamble[0] = 0xAA;
	ethead->preamble[1] = 0xAA;
	ethead->preamble[2] = 0xAA;
	ethead->preamble[3] = 0xAA;
	ethead->preamble[4] = 0xAA;
	ethead->preamble[5] = 0xAA;
	ethead->preamble[6] = 0xAA;
	ethead->sfd = 0xAB;
	
	arp_resolve((char *) &iphead->dest, ethead->dest);
	arp_resolve((char *) &iphead->source, ethead->source);
	ethead->len = sizeof(p->data);
	
	// Inviamo il pacchetto tramite la periferica
	uint32_t sended_b;
	
	if((iface->drv)->write != NULL)
		sended_b = (iface->drv)->write(iface->dev, p->data, p->size, 0);
	else
		return 0;	
	
	iface->tx_bytes = iface->tx_bytes + sended_b;
	return sended_b;	
}



/**
 * Abilita l'interfaccia
 */
uint32_t eth_up(network_iface_t *iface)
{
	
}



/**
 * Disabilita l'interfaccia
 */
uint32_t eth_down(network_iface_t *iface)
{
	
}

