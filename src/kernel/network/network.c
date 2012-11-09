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
 * \file kernel/network/network.c
 * \author Davide Gessa
 * \date 12-09-2009
 */
#include <network/network.h>
#include <network/route.h>
#include <network/socket.h>
#include <network/link/ppp.h>
#include <network/link/eth.h>
#include <network/link/lo.h>
#include <network/link/bt.h>
#include <network/link/wifi.h>
#include <klibc/string.h>		
#include <klibc/stdio.h>	
#include <debug.h>			
#include <driver/net/modem.h>
#include <driver/net/rs232.h>
#include <driver/net/ne2k.h>

/**
 * Inizializza il modulo di rete
 */
void network_init()
{
	network_iface_t *nt;
	
	DEBUGP("network_init()\n");
	
	network_ifaces = NULL;
	route_table = NULL;
	sock_first_free = 0;
	
	// Interfaccia di loopback
	#ifdef NLO
		nt = network_iface_create(NET_LINK_TYPE_LO, 0, 0);
		if(nt != NULL)
		{
			network_iface_add(nt);
			network_iface_up("lo");

			// Routing entry
			ip_t dest;
			ip_t gw;
			ip_t genmask;
			
			network_toaddr(dest, 127, 0, 0, 1);
			network_toaddr(gw, 127, 0, 0, 1);
			network_toaddr(genmask, 255, 0, 0, 0);
		
			route_add(nt, dest, gw, genmask, 0, 0x0);
		}
	#endif
	
		
	// Interfaccia ppp
	#ifdef NPPP
		nt = network_iface_create(NET_LINK_TYPE_PPP, &driver_modem, &rs232_com1);
		if(nt != NULL)
		{
			network_iface_add(nt);
			network_toaddr(nt->addr, 80, 60, 4, 2);
			network_toaddr(nt->mask, 255, 255, 255, 0);
			network_toaddr(nt->bcast, 255, 255, 255, 255);
			nt->if_mac = 0;

			#ifdef TEST
			//network_iface_up("ppp");
			#endif
		}
	
		#ifdef TEST
		// Facciamo un test per l'invio di un frame su ppp
		//char a[] = "ppp test packet sending\n";
		//packet_t *p = packet_create(a, sizeof("ppp test packet sending\n"));
		//ppp_send_frame(nt, p);
		#endif
	#endif

	// Interfaccia eth
	#ifdef NETH
		nt = network_iface_create(NET_LINK_TYPE_ETH, &driver_ne2k, &device_ne2k_qemu);
		if(nt != NULL)
		{
			network_iface_add(nt);
			network_toaddr(nt->addr, 192, 168, 254, 16);
			network_toaddr(nt->mask, 255, 255, 255, 0);
			network_toaddr(nt->bcast, 255, 255, 255, 0);
			nt->if_mac = 0;

			#ifdef TEST
			//network_iface_up("eth");
			#endif
		}
		
		#ifdef TEST
			char test_packet[] = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
									0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
									0x30, 0x30, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
									0x61, 0x61 };
			
			int i;
			for(i = 0; i < 1; i++) 
			{
				packet_t *pack = packet_create(test_packet, 101);

				//eth_handle_frame(nt, pack);
			}
			sock_test();
		#endif
	
	#endif

}



/**
 * Char based add
 */
uint32_t network_iface_add2(char *type, char *driver, char *device, char *adr, char *mask)
{
	network_iface_t *nt = NULL;
	
	if(strcmp(type, "lo") == 0)
		nt = network_iface_create(NET_LINK_TYPE_LO, NULL, NULL);
	else if(strcmp(type, "eth") == 0)
		nt = NULL;//nt = network_iface_create(NET_LINK_TYPE_ETH, driver_get(driver), device_get(device));
	else if(strcmp(type, "ppp") == 0)
		nt = NULL;//nt = network_iface_create(NET_LINK_TYPE_PPP, driver_get(driver), device_get(device));
	else if(strcmp(type, "wifi") == 0)
		nt = NULL;//nt = network_iface_create(NET_LINK_TYPE_WIFI, driver_get(driver), device_get(device));
	
	if(nt != NULL)
	{
		network_iface_add(nt);
		network_iface_up(type);

		memcpy(nt->addr, adr, ADDR_LEN);
		memcpy(nt->mask, mask, ADDR_LEN);
		//memcpy(nt->bcast, 0, );
		
		return 1;
	}
	return 0;
}

/**
 * Disabilita un interfaccia
 */
uint32_t network_iface_down(char *ifname)
{
	DEBUGP("network_iface_down()\n");

	network_iface_t *ci;
	
	network_iface_get(ifname, &ci);
	
	if(ci != NULL)
	{
		ci->if_up = 0;
		
		return 0;
	}
	
	return 1;
}



/**
 * Abilita un interfaccia
 */
uint32_t network_iface_up(char *ifname)
{
	DEBUGP("network_iface_up()\n");

	network_iface_t *ci;
	
	network_iface_get(ifname, &ci);
	
	if(ci != NULL)
	{
		ci->tx_bytes = 0;
		ci->rx_bytes = 0;
		ci->if_up = 1;

		driver_initd((ci->drv)->name);

		return 0;
	}
	
	return 1;
}

/**
 * Aggiunge un interfaccia
 */
uint32_t network_iface_add(network_iface_t *iface)
{	
	DEBUGP("network_iface_add()\n");

	if(iface != NULL)
	{
		iface->next = network_ifaces;
		iface->if_up = 0;
		iface->tx_bytes = 0;
		iface->rx_bytes = 0;
		network_ifaces = iface;		
		return 0;		
	}
	
	return 1;	
}



/**
 * Crea un iface
 */
network_iface_t *network_iface_create(uint32_t type, driver_t *driver, device_t *device)
{
	if(((driver == NULL) || (device == NULL)) && type != NET_LINK_TYPE_LO)
		return NULL;
		
	network_iface_t *iface = (network_iface_t *) malloc(sizeof(network_iface_t));
	
	iface->tx_bytes = 0;
	iface->rx_bytes = 0;
	iface->drv = driver;
	iface->dev = device;
	iface->type = type;
	iface->if_up = 0;
	
	
	switch(type)
	{
		#ifdef NETH
		case NET_LINK_TYPE_ETH:
			strcpy(iface->name, "eth");
			iface->link_protocol = (void *) &eth_linkproto;
			break;
		#endif
		
		#ifdef NLO
		case NET_LINK_TYPE_LO:
			strcpy(iface->name, "lo");
			network_toaddr(iface->addr, 127, 0, 0, 1);
			network_toaddr(iface->mask, 255, 0, 0, 0);
			network_toaddr(iface->bcast, 0, 0, 0, 0);
			iface->if_mac = 0;

			iface->link_protocol = (void *) &lo_linkproto;
			break;
		#endif
		
		#ifdef NPPP
		case NET_LINK_TYPE_PPP:
			strcpy(iface->name, "ppp");
			iface->link_protocol = (void *) &ppp_linkproto;
			break;
		#endif
		
		#ifdef NBT
		case NET_LINK_TYPE_BT:
			strcpy(iface->name, "bt");
			iface->link_protocol = (void *) &bt_linkproto;
			break;
		#endif

		#ifdef NWIFI
		case NET_LINK_TYPE_WIFI:
			strcpy(iface->name, "wifi");
			iface->link_protocol = (void *) &wifi_linkproto;
			break;
		#endif
			
		default:
			free(iface);
			return NULL;
	}
	
	return iface;
}


/**
 * Restituisce il fs numero x
 * 
 * \return stato operazione
 */
uint32_t network_iface_iget(uint32_t x, network_iface_t **iface)
{
	network_iface_t *cf = network_ifaces;
	uint32_t i = 0;
	*iface = NULL;
	
	while(cf != NULL)
	{
		if(i == x)
		{
			*iface = cf;
			return 0;
		}
		i++;
		cf = cf->next;
	}
	return 1;	
}



/**
 * Restituisce l'interfaccia dato il nome
 * 
 * \return stato operazione
 */
uint32_t network_iface_get(char *name, network_iface_t **iface)
{
	network_iface_t *cf = network_ifaces;
	*iface = NULL;
	
	while(cf != NULL)
	{
		if(strcmp(name, cf->name) == 0)
		{
			*iface = cf;
			return 0;
		}
		
		cf = cf->next;
	}
	return 1;
}



/**
 * Trasforma un indirizzo in una stringa
 */
char *network_addrtoa(ip_t addr, char *str)
{
	strcpy(str, itoa((uint8_t) addr[0]));
	strcat(str, ".");
	strcat(str, itoa((uint8_t) addr[1]));
	strcat(str, ".");
	strcat(str, itoa((uint8_t) addr[2]));
	strcat(str, ".");
	strcat(str, itoa((uint8_t) addr[3]));
	strcat(str, "\0");
	
	return str;
}



/**
 * Trasforma un indirizzo mac in una stringa
 */
char *network_macrtoa(mac_t addr, char *str)
{
	strcpy(str, itox((uint8_t) addr[0]));
	strcat(str, ":");
	strcat(str, itox((uint8_t) addr[1]));
	strcat(str, ":");
	strcat(str, itox((uint8_t) addr[2]));
	strcat(str, ":");
	strcat(str, itox((uint8_t) addr[3]));
	strcat(str, ":");
	strcat(str, itox((uint8_t) addr[4]));
	strcat(str, ":");
	strcat(str, itox((uint8_t) addr[5]));
	strcat(str, "\0");
	
	return str;
}


/**
 * Trasforma dei numeri in un addr
 */
void network_toaddr(ip_t buf, uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	buf[0] = a;
	buf[1] = b;
	buf[2] = c;
	buf[3] = d;
}
