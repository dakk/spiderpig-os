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
 * \file kernel/network/packet.c
 * \author Davide Gessa
 * \date 02-02-2010
 */
#include <network/network.h>
#include <network/packet.h>
#include <string.h>		
#include <stdio.h>	
#include <malloc.h>

/**
 * Ridimensiona un pacchetto per farci stare l'header
 */
void packet_add_header(packet_t *p, uint32_t h_size)
{
	char *data = (char *) malloc(p->size + h_size);
	memcpy(data + h_size, p->data, p->size);
	free(p->data);
	p->data = data;
	p->size = p->size + h_size;	
}


/**
 * Ridimensiona un pacchetto togliendo l'header
 */
void packet_del_header(packet_t *p, uint32_t h_size)
{
	char *data = (char *) malloc(p->size - h_size);
	memcpy(data, p->data + h_size, p->size - h_size);
	free(p->data);
	p->data = data;
	p->size = p->size - h_size;
}



/**
 * Alloca un pacchetto
 */
packet_t *packet_create(char *data, uint32_t size)
{
	packet_t *p = (packet_t *) malloc(sizeof(packet_t));
	p->data = (char *) malloc(size);
	memcpy(p->data, data, size);
	p->size = size;
	return p;
}
