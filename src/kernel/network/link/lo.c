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
 * \file kernel/network/link/lo.c
 * \author Davide Gessa
 * \date 02-4-2010
 */
#include <network/network.h>
#include <network/packet.h>
#include <network/link/lo.h>
#include <network/link/ppp.h>

netlink_t lo_linkproto =
{
	.up = lo_up,
	.down = lo_down,
	.handle_frame = lo_handle_frame,
	.send_frame = lo_send_frame
};

uint32_t lo_handle_frame(network_iface_t *iface, packet_t *p)
{
	uint16_t protocol;
	
	// Estraiamo l'header
	lo_header_t *lohead = (lo_header_t *) p->data;


	protocol = lohead->protocol;
	
	// Togliamo l'header
	packet_del_header(p, sizeof(lo_header_t));


	// Inviamo il frame al protocollo specificato nel tipo
	#ifdef TEST
	
	if(video_getx() != 0)
		printf("\n");
		
	printf("lo: received packet (sizeof %d) of protocol %x\n", p->size, protocol);
	#endif

	ip_handle_packet(iface, p);
	
	switch(protocol)
	{
		#ifdef NIPV4
		case PPP_PROTOCOL_IP:
			ip_handle_packet(iface, p);
			break;
		#endif
	}


	iface->rx_bytes = iface->rx_bytes + p->size;
	return 0;
}

uint32_t lo_send_frame(network_iface_t *iface, packet_t *p)
{
	lo_handle_frame(iface, p);
	
	iface->tx_bytes = iface->tx_bytes + p->size;
	return p->size;	
}




uint32_t lo_up(network_iface_t *iface)
{
	
}

uint32_t lo_down(network_iface_t *iface)
{
	
}
