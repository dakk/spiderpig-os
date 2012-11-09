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
 * \file kernel/network/network.h
 * \author Davide Gessa
 * \date 12-09-2009
 */
#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/packet.h>

#define NET_LINK_TYPE_NULL	0
#define NET_LINK_TYPE_LO	1
#define NET_LINK_TYPE_ETH	2
#define NET_LINK_TYPE_PPP	3
#define NET_LINK_TYPE_PPPOA	4
#define NET_LINK_TYPE_PPPOE	5
#define NET_LINK_TYPE_WIFI	6
#define NET_LINK_TYPE_BT	7



//#ifndef ADDR_LEN
	#define ADDR_LEN	4
//#endif

typedef char ip_t[ADDR_LEN];
typedef char mac_t[6];

#include <network/net/ip.h>

/**
 * Interfaccia di rete
 */
typedef struct network_iface_p
{
	char name[32];					///< Nome interfaccia
	
	ip_t addr;						///< Indirizzo interfaccia
	ip_t mask;						///< Mask di rete
	ip_t bcast;						///< Indirizzo bcast della rete
	mac_t mac;						///< Indirizzo mac scheda
	
	uint8_t if_up;					///< L'interfaccia e' attiva?
	uint8_t if_mac;					///< C'e' un mac?
	uint8_t if_bcast;				///< C'e' un broadcast?
	
	uint8_t type;					///< Tipo di interfaccia (livello link)
	
	uint32_t tx_bytes;				///< Byte trasmessi
	uint32_t rx_bytes;				///< Byte ricevuti

	driver_t *drv;					///< Driver che gestisce l'interfaccia
	device_t *dev;					///< Device dell'interfaccia

	void *link_protocol;			///< Puntatore a netlink
	
	struct network_iface_p *next;	///< Puntatore alla prossima iface
} network_iface_t;



/**
 * Struttura di un protocollo a livello link
 */
typedef struct
{
	uint32_t (*up)(network_iface_t *);
	uint32_t (*down)(network_iface_t *);
	
	uint32_t (*handle_frame)(network_iface_t *, packet_t *);	///< Gestisce un frame da questa interfaccia
	uint32_t (*send_frame)(network_iface_t *, packet_t *);		///< Trasmette un frame da questa interfaccia
	
	uint32_t frame_min_size;
	uint32_t frame_max_size;
	uint32_t header_size;
} netlink_t;

network_iface_t *network_ifaces;	///< Interfaccie di rete


void network_init();
uint32_t network_iface_add(network_iface_t *);
uint32_t network_iface_add2(char *, char *, char *, char *, char *);
uint32_t network_iface_up(char *);
uint32_t network_iface_down(char *);
uint32_t network_iface_iget(uint32_t, network_iface_t **);
uint32_t network_iface_get(char *, network_iface_t **);
char *network_addrtoa(char *, char *);
char *network_mactoa(char *, char *);
void network_toaddr(char *, uint8_t, uint8_t, uint8_t, uint8_t);
network_iface_t *network_iface_create(uint32_t, driver_t *, device_t *);

#endif
