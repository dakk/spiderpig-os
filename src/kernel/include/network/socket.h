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
 * \file kernel/network/socket.h
 * \author Davide Gessa
 * \date 12-09-2009
 */
#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include <types.h>
#include <config.h>
#include <driver.h>
#include <device.h>
#include <network/packet.h>


#define SOCK_DOMAIN_AF_INET			0x01
#define SOCK_DOMAIN_AF_INET6		0x02
#define SOCK_DOMAIN_AF_UNIX			0x03
#define SOCK_DOMAIN_AF_LOCAL		//   Local communication              unix(7)
#define SOCK_DOMAIN_AF_IPX          //    IPX - Novell protocol
#define SOCK_DOMAIN_AF_NETLINK      //    Kernel user interface device     netlink(7)
#define SOCK_DOMAIN_AF_X25          //    ITU-T X.25 / ISO-8208 protocol   x25(7)
#define SOCK_DOMAIN_AF_AX25         //    Amateur radio AX.25 protocol
#define SOCK_DOMAIN_AF_ATMPVC       //    Access to raw ATM PVCs
#define SOCK_DOMAIN_AF_APPLETALK    //    Appletalk                        ddp(7)
#define SOCK_DOMAIN_AF_PACKET

#define SOCK_TYPE_SOCK_STREAM		0x01 // Provides sequenced, reliable, two-way, connection-based byte streams.  An out-of-band  data  transmission
										 //                    mechanism may be supported.
#define SOCK_TYPE_SOCK_DGRAM    	0x02 //Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
#define SOCK_TYPE_SOCK_SEQPACKET  		 //Provides  a  sequenced,  reliable, two-way connection-based data transmission path for datagrams of fixed
									  	 //    maximum length; a consumer is required to read an entire packet with each input system call.
#define SOCK_TYPE_SOCK_RAW  		0x04	 //      Provides raw network protocol access.
#define SOCK_TYPE_SOCK_RDM  			 //      Provides a reliable datagram layer that does not guarantee ordering.
#define SOCK_TYPE_SOCK_PACKET 
       
typedef uint32_t sa_family_t;
typedef uint32_t socklen_t;
typedef uint32_t in_port_t;

#define SOCKET_BUFFER_SIZE 8192
/**
 * Sessione socket
 */
typedef struct
{
	network_iface_t *iface;		///< Interfaccia
	uint32_t protocol;			///< Protoccollo
	uint32_t type;				///< Tipo
	uint32_t domain;			///< Dominio
	
	uint8_t is_server;			///< E' un server?
	uint16_t port;				///< Porta di connessione
	
	char addr[ADDR_LEN];
	
	uid_t uid;	
	uint32_t used;				
	
	char rec_buf[SOCKET_BUFFER_SIZE];
	int rec_p1;
	int rec_p2;
	int rec_data_len;
	char send_buf[SOCKET_BUFFER_SIZE];
	int send_p1;
	int send_p2;
	int send_data_len;
} socket_t;


struct sockaddr
{
	sa_family_t sa_family;
	char sa_data[14];
};


struct in_addr
{
	uint32_t s_addr;     /* address in network byte order */
};

struct sockaddr_in
{
	sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

#define SOCKET_MAX	1024

socket_t sockets[SOCKET_MAX];
uint32_t sock_first_free;

int sock_shutdown(int, int);
int socket(uint32_t, uint32_t, uint32_t);
int sock_bind(int, const struct sockaddr_in *, socklen_t);
int sock_connect(int, const struct sockaddr *, socklen_t);
uint32_t sock_send(int, const void *, size_t, int);
uint32_t sock_sendto(int, const void *, size_t, int,  const struct sockaddr *, socklen_t);
uint32_t sock_recv(int, void *, size_t, int);
uint32_t sock_recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);                                   
void sock_test();

uint32_t sock_iget(uint32_t, socket_t **);

#endif
