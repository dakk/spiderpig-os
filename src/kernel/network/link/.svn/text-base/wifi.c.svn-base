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
 * \file kernel/network/link/wifi.c
 * \author Davide Gessa
 * \date 02-4-2010
 */
#include <network/network.h>
#include <network/packet.h>
#include <network/net/ip.h>
#include <network/link/wifi.h>

netlink_t wifi_linkproto =
{

	.up = wifi_up,
	.down = wifi_down,
	.handle_frame = wifi_handle_frame,
	.send_frame = wifi_send_frame
};

uint32_t wifi_handle_frame(network_iface_t *iface, packet_t *p)
{
	return 0;
}

uint32_t wifi_send_frame(network_iface_t *iface, packet_t *p)
{

	// Inviamo il pacchetto tramite la periferica
	uint32_t sended_b;
	
	if((iface->drv)->write != NULL)
		sended_b = (iface->drv)->write(iface->dev, p->data, p->size, 0);
	else
		return 0;	
	
	iface->tx_bytes = iface->tx_bytes + sended_b;
	return sended_b;	
}


uint32_t wifi_up(network_iface_t *iface)
{
	
}

uint32_t wifi_down(network_iface_t *iface)
{
	
}

