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
 * \file kernel/network/socket.c
 * \author Davide Gessa
 * \date 02-02-2010
 */
#include <network/network.h>
#include <network/socket.h>
#include <network/route.h>
#include <klibc/string.h>		
#include <klibc/stdio.h>	
#include <debug.h>			
#include <config.h>


#ifdef TEST
void sock_test()
{
	printf("\nsock_test()\n");

	// Server
	int sock_s = socket(SOCK_DOMAIN_AF_INET, SOCK_TYPE_SOCK_DGRAM, 0);	
	struct sockaddr_in s;
	s.sin_family = SOCK_DOMAIN_AF_INET;
    s.sin_port = 24;
	sock_bind(sock_s, &s, sizeof(s)); 
	
	// Client
	int sock_c = socket(SOCK_DOMAIN_AF_INET, SOCK_TYPE_SOCK_DGRAM, 0);
	struct sockaddr c;
	
	network_toaddr(c.sa_data, 127, 0, 0, 1);
	c.sa_family = SOCK_DOMAIN_AF_INET;
	sock_connect(sock_c, &c, 4);

	
	sock_send(sock_c, "ciao\0", 5, 0);
	
	char buf[16];
	if(sock_recv(sock_s, buf, 16, 0) != -1)
		printf("Received packet data: %s\n\n", buf);
	
	//sock_shutdown(sock, 0x0);
}
#endif


/**
 * Creazione socket di connessione
 */
int socket(uint32_t domain, uint32_t type, uint32_t protocol)
{
	int sock;
	
	sock = sock_first_free;
	sockets[sock].uid = task_get_uid(task_get_pid());
	

	//if(domain == SOCK_DOMAIN_AF_INET)
	//{
		if(type == SOCK_TYPE_SOCK_DGRAM)
		{
			sockets[sock].type = SOCK_TYPE_SOCK_DGRAM;			
		}
		else if(type == SOCK_TYPE_SOCK_STREAM)
		{
			sockets[sock].type = SOCK_TYPE_SOCK_STREAM;
		}
		else
		{
			return -1;
		}
	//}

	sockets[sock].used = 1;
	sockets[sock].send_p1 = sockets[sock].send_p2 = 0;
	sockets[sock].rec_p1 = sockets[sock].rec_p2 = 0;
	sockets[sock].send_data_len = sockets[sock].rec_data_len = 0;
	sockets[sock].iface = NULL;

	while(sockets[sock_first_free].used)
		sock_first_free++;

	printf("created socket %d\n", sock);
	return sock;
}


/**
 * Chiude il socket
 */
int sock_shutdown(int sockfd, int how)
{
	// Controlliamo l'uid
	//if(sockets[sockfd].uid == task_get_uid(task_get_pid()))
	{
		// Liberiamo i buffer
		
		// Liberiamo l'entry
		sockets[sockfd].used = 0;	
		
		printf("shutdown ok\n");
	}
}


int sock_bind(int sockfd, const struct sockaddr_in *addr, socklen_t addrlen)
{
	socket_t *sock;
	
	sock_iget(sockfd, &sock);
	
	if(sock == NULL)
		return -1;
		
	sock->is_server = 1;
	sock->port = addr->sin_port;
}

/**
 * Connette ad un host
 */
int sock_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int i = 0;

	// Cerca una routing entry valida
	route_entry_t *re;
	
	while(route_iget(i, &re))
	{
		//char ip1[10];
		//char ip2[10];
		//printf("%s %s\n", network_addrtoa((char *) addr->sa_data, ip1),  network_addrtoa((char *) re->dest, ip2)); 
		
		if(strncmp((char *) addr->sa_data, (char *) re->dest, addrlen) == 0)
		{
			sockets[sockfd].iface = re->iface;
			
			printf("found a valid routing rule for this address\n");
			return 0;
		}
		i++;
	}
}

uint32_t sock_send(int sockfd, const void *buf, size_t len, int flags)
{
	socket_t *sock;
	
	sock_iget(sockfd, &sock);
	printf("sending sock pack\n");
	
	if(sock == NULL)
		return -1;

	packet_t *p = packet_create((char *) buf, len);
	if(sock->type == SOCK_TYPE_SOCK_DGRAM)
		return udp_send_packet(sock, p);
}


uint32_t sock_sendto(int sockfd, const void *buf, size_t len, int flags,  const struct sockaddr *dest_addr, socklen_t addrlen)
{
	
	
}


uint32_t sock_recv(int sockfd, void *buf_, size_t len, int flags)
{
	socket_t *sock;
	
	sock_iget(sockfd, &sock);
	
	if(sock == NULL)
		return -1;
		
	if(sock->rec_data_len > 0)
	{
		unsigned i;
	
		for(i = 0; i < len; i++)
		{
			char *buf = buf_;
			buf[i] = sock->rec_buf[sock->rec_p2];
			sock->rec_p2++;
			if(sock->rec_p2 >= sock->rec_p1)
				return i;
			sock->rec_data_len--;
		}
		return len;		
	}
	return -1;
}


uint32_t sock_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
	
}


uint32_t sock_iget(uint32_t x, socket_t **s)
{
	if(x > SOCKET_MAX) 
		return 0;
		
	*s = &sockets[x];
	return 1;
}
