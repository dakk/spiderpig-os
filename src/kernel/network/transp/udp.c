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
#include <network/packet.h>
#include <network/socket.h>


/**
 * Gestisce un pacchetto udp
 */
uint32_t udp_handle_packet(network_iface_t *iface, packet_t *p)
{
	// Estraiamo gli header
	ip_header_t *iphead = (ip_header_t *) p->data;
	udp_header_t *udphead = (udp_header_t *) p->data + sizeof(ip_header_t);
	
	#ifdef TEST
	if(video_getx() != 0)
		printf("\n");
	printf("udp: received packet (sizeof %d) on port %x\n", p->size - sizeof(ip_header_t) - sizeof(udp_header_t), udphead->dest_port);
	#endif
	
	socket_t *s;
	uint32_t i;

	while(sock_iget(i, &s))
	{
		if(s->port == udphead->source_port)
		{
			for(i = 0; i < (p->size - sizeof(ip_header_t) - sizeof(udp_header_t)); i++)
			{
				s->rec_buf[s->rec_p1] = p->data[i + sizeof(udp_header_t) + sizeof(ip_header_t)];
				s->rec_p1++;
				s->rec_data_len++;
			}	
			
			break;
		}
		i++;
	}
	
	free(p);
}



/**
 * Invia un pacchetto udp
 */
uint32_t udp_send_packet(socket_t *s, packet_t *p)
{
	printf("sending udp pack\n");
	packet_add_header(p, sizeof(udp_header_t));
	udp_header_t *h = p->data;
	h->source_port = s->port;
	h->dest_port = s->port;
	return ip_send_frame(s->iface, p, s->addr, s->protocol);
}
