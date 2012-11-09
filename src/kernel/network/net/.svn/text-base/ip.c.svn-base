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
 * \file kernel/network/ip.c
 * \author Davide Gessa
 * \date 02-05-2009
 */
//#include <network/net/ip.h>
#include <network/network.h>
#include <network/net/ipv4.h>
#include <network/transp/udp.h>


/**
 * Gestisce un pacchetto ip
 */
uint32_t ip_handle_packet(network_iface_t *iface, packet_t *p)
{
	uint32_t protocol;
	
	// Estraiamo l'header
	ip_header_t *iphead = (ip_header_t *) p->data;
	
	protocol = iphead->protocol;
	
	#ifdef TEST
	if(video_getx() != 0)
		printf("\n");
	printf("ip: received packet (sizeof %d) of protocol %x\n", p->size, protocol);
	#endif
	
	
	// Inviamo il frame al protocollo specificato nel tipo	
		udp_handle_packet(iface, p);			
		
	switch(protocol)
	{
		#ifdef NICMP
		case IPV4_PROTOCOL_ICMP:
			icmp_handle_packet(iface, p);
			break;
		#endif
		
		#ifdef NUDP
		case IPV4_PROTOCOL_UDP:
			udp_handle_packet(iface, p);			
			break;
		#endif
		
		#ifdef NTCP
		case IPV4_PROTOCOL_TCP:			
			break;
		#endif
	
		#ifdef NIPV6
		case IPV4_PROTOCOL_IPV6:			
			break;
		#endif
		
	}
	
	return 0;
}



/**
 * Invia un pacchetto ip
 */
uint32_t ip_send_frame(network_iface_t *iface, packet_t *p, char *adr, uint8_t proto)
{
	printf("sending ip frame\n");
	// Crea header
	ip_header_t header;
	memcpy(&(header.dest), adr, ADDR_LEN);
	memcpy(&(header.source), (iface->addr), ADDR_LEN);
	//header.protocol = IPV4_PROTOCOL_UDP;
	return ((netlink_t *) (iface->link_protocol))->send_frame(iface, p);
	
	// Verifica la dimensione e la mtu dell'interfaccia
	if((p->size + ((netlink_t *) (iface->link_protocol))->header_size) > ((netlink_t *) (iface->link_protocol))->frame_max_size)
	{
		// Crea l'header
		ip_header_t *fragheader;
		uint32_t i;
		//...
		
		uint32_t nf = (p->size + ((netlink_t *) (iface->link_protocol))->header_size) / 
					((netlink_t *) (iface->link_protocol))->frame_max_size;
		uint32_t offset = 0;
		
		for(i = 0; i < nf; i++)
		{
			// Imposta frammento
			packet_t *frag = packet_create(0, 1);
			fragheader = (ip_header_t *) frag->data;
			
			fragheader->offset = offset;
			fragheader->time_to_live = 255;
			
			// Invia frammento
			((netlink_t *) (iface->link_protocol))->send_frame(iface, frag);
		}
		
	}
	else
		((netlink_t *) (iface->link_protocol))->send_frame(iface, p);
	
	return 0;
}
