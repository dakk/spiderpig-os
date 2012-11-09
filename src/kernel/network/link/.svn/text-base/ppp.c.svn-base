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
 * \file kernel/network/link/ppp.c
 * \author Davide Gessa
 * \date 02-4-2010
 */
#include <network/network.h>
#include <network/packet.h>
#include <network/link/ppp.h>

netlink_t ppp_linkproto =
{
	.frame_min_size = 12,
	.frame_max_size = 1490,
	
	.up = ppp_up,
	.down = ppp_down,
	.handle_frame = ppp_handle_frame,
	.send_frame = ppp_send_frame
};



/**
 * Gestisce un frame
 */
uint32_t ppp_handle_frame(network_iface_t *iface, packet_t *p)
{
	uint16_t protocol;
	
	// Estraiamo l'header
	ppp_header_t *ppphead = (ppp_header_t *) p->data;


	protocol = ppphead->protocol;
	
	// Togliamo l'header
	packet_del_header(p, sizeof(ppp_header_t));


	// Inviamo il frame al protocollo specificato nel tipo
	#ifdef TEST
	
	if(video_getx() != 0)
		printf("\n");
		
	printf("ppp: received packet (sizeof %d) of protocol %x\n", p->size, protocol);
	#endif
	
	switch(protocol)
	{
		#ifdef NIPV4
		case PPP_PROTOCOL_IP:
			ip_handle_packet(iface, p);
			break;
		#endif
	}
	
	return 0;
}



/**
 * Invia un frame
 */
uint32_t ppp_send_frame(network_iface_t *iface, packet_t *p)
{
	// Aggiungiamo l'header specificando i vari campi
	packet_add_header(p, sizeof(ppp_header_t));
	ppp_header_t *ppphead = (ppp_header_t *) p->data;

	ppphead->flag = PPP_FLAG; 
	ppphead->address = PPP_ADDRESS_BROADCAST;
	ppphead->control = PPP_CONTROL_UI_FRAME;
	ppphead->protocol = PPP_PROTOCOL_IP;

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
uint32_t ppp_up(network_iface_t *iface)
{
	
}



/**
 * Disabilita l'interfaccia
 */
uint32_t ppp_down(network_iface_t *iface)
{
	
}
