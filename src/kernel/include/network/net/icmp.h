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
 * \file kernel/network/icmp.h
 * \author Davide Gessa
 * \date 02-05-2010
 */
#ifndef NETWORK_ICMP_H
#define NETWORK_ICMP_H

#include <types.h>
#include <config.h>
#include <network/network.h>


#define ICMP_ECHO_REPLY						0 
#define ICMP_DESTINATION_NOT_REACHABLE 		3
#define ICMP_SOURCE_QUENCH					4
#define ICMP_REDIRECT						5
#define ICMP_ALTERNATIVE_HOST_ADDRESS		6
#define ICMP_ECHO_REQUEST					8 
#define ICMP_ROUTER_ADVERTISEMENT			9
#define ICMP_ROUTER_SELECTION				10
#define ICMP_IPV6_WHERE_ARE_YOU				33
#define ICMP_IPV6_I_AM_HERE					34
#define ICMP_ADDRESS_MASK_REQUEST			17
#define ICMP_ADDRESS_MASK_REPLY				18
#define ICMP_TIMESTAMP_REQUEST				13
#define ICMP_TIMESTAMP_REPLY				14
#define ICMP_INFORMATION_REQUEST			15
#define ICMP_INFORMATION_REPLY				16
#define ICMP_TRACEROUTE						30
#define ICMP_MOBILE_HOST_REDIRECT			32
#define ICMP_MOBILE_REG_REQUEST				35
#define ICMP_MOBILE_REG_REPLY				36 
#define ICMP_DOMAIN_NAME_REQUEST			37
#define ICMP_DOMAIN_NAME_REPLY				38
#define ICMP_DATAGRAM_CONVERSION_ERROR		31
#define ICMP_EXPIRED_REQUEST				11
#define ICMP_PARAMETERS_ERROR				12




typedef struct
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
} icmp_header_t;


uint32_t icmp_handle_packet(network_iface_t *, packet_t *);


#endif
