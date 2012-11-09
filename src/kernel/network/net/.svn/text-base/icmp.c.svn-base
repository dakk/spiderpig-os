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
 * \file kernel/network/icmp.c
 * \author Davide Gessa
 * \date 02-05-2009
 */
#include <network/net/ipv4.h>
#include <network/network.h>
#include <network/net/icmp.h>


/**
 * Gestisce un pacchetto icmp
 */
uint32_t icmp_handle_packet(network_iface_t *iface, packet_t *p)
{
	uint8_t protocol;

	// Estraiamo gli header
	ip_header_t *iphead = (ip_header_t *) p->data;
	icmp_header_t *icmphead = (icmp_header_t *) p->data + sizeof(ip_header_t);


	protocol = icmphead->type;
	
	#ifdef TEST
	if(video_getx() != 0)
		printf("\n");
	printf("icmp: received packet (sizeof %d) request: %d: ", p->size, protocol);
	#endif
	
	switch(protocol)
	{
		case ICMP_ECHO_REPLY:
			#ifdef TEST
			printf("pong\n");
			#endif
			break;
			
		case ICMP_ECHO_REQUEST:
			#ifdef TEST
			printf("ping\n");
			#endif
			
			// Inviamo il pong!
			packet_t *pong = packet_create(NULL, sizeof(icmp_header_t));
			icmp_header_t *ponghead = (icmp_header_t *) pong->data;
			ponghead->type = ICMP_ECHO_REPLY;
			ponghead->checksum = 0;
			//ponghead->checksum = packet_checksum(pong, 0);
			ip_send_frame(iface, pong, (char *) &(iphead->source), IPV4_PROTOCOL_ICMP);
			
			break;
			
		case ICMP_REDIRECT:
			#ifdef TEST
			printf("redirect\n");
			#endif
			break;
			
		case ICMP_SOURCE_QUENCH:
			#ifdef TEST
			printf("source quench\n");
			#endif
			break;
			
		case ICMP_DESTINATION_NOT_REACHABLE: 	
			#ifdef TEST
			printf("destination not reachable\n");
			#endif
			break;
			
		case ICMP_ALTERNATIVE_HOST_ADDRESS:		
			#ifdef TEST
			printf("alternative host address\n");
			#endif
			break;

		case ICMP_ROUTER_ADVERTISEMENT:			
			#ifdef TEST
			printf("router advertisement\n");
			#endif
			break;

		case ICMP_ROUTER_SELECTION:				
			#ifdef TEST
			printf("router selection\n");
			#endif
			break;

		case ICMP_IPV6_WHERE_ARE_YOU:			
			#ifdef TEST
			printf("ipv6 where are you?\n");
			#endif
			break;

		case ICMP_IPV6_I_AM_HERE:				
			#ifdef TEST
			printf("ipv6 i'm here!\n");
			#endif
			break;

		case ICMP_ADDRESS_MASK_REQUEST:			
			#ifdef TEST
			printf("address mask request\n");
			#endif
			break;

		case ICMP_ADDRESS_MASK_REPLY:				
			#ifdef TEST
			printf("address mask reply\n");
			#endif
			break;

		case ICMP_TIMESTAMP_REQUEST:				
			#ifdef TEST
			printf("timestamp request\n");
			#endif
			break;

		case ICMP_TIMESTAMP_REPLY:				
			#ifdef TEST
			printf("timestamp reply\n");
			#endif
			break;

		case ICMP_INFORMATION_REQUEST:			
			#ifdef TEST
			printf("information request\n");
			#endif
			break;

		case ICMP_INFORMATION_REPLY:				
			#ifdef TEST
			printf("information reply\n");
			#endif
			break;

		case ICMP_TRACEROUTE:					
			#ifdef TEST
			printf("traceroute\n");
			#endif
			break;

		case ICMP_MOBILE_HOST_REDIRECT:			
			#ifdef TEST
			printf("mobile host redirect\n");
			#endif
			break;

		case ICMP_MOBILE_REG_REQUEST:			
			#ifdef TEST
			printf("mobile registration request\n");
			#endif
			break;

		case ICMP_MOBILE_REG_REPLY:				 
			#ifdef TEST
			printf("mobile registration reply\n");
			#endif
			break;

		case ICMP_DOMAIN_NAME_REQUEST:			
			#ifdef TEST
			printf("domain name request\n");
			#endif
			break;

		case ICMP_DOMAIN_NAME_REPLY:				
			#ifdef TEST
			printf("domain name reply\n");
			#endif
			break;

		case ICMP_DATAGRAM_CONVERSION_ERROR:		
			#ifdef TEST
			printf("datagram conversion error\n");
			#endif
			break;

		case ICMP_EXPIRED_REQUEST:				
			#ifdef TEST
			printf("expired request\n");
			#endif
			break;

		case ICMP_PARAMETERS_ERROR:				
			#ifdef TEST
			printf("parameters error\n");
			#endif
			break;
			
		default:
			break;
	}
	
	return 0;
}
