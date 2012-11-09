#include <network/packet.h>
#include <network/link/eth.h>
#include <network/link/ppp.h>
#include <network/link/arp.h>
#include <network/net/ip.h>
#include <network/net/ipv4.h>
#include <network/net/icmp.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>


/**
 * Aggiunge un protocollo ad un pacchetto
 */
int add_proto(packet_t *p, char *proto)
{
	if(strcmp(proto, "udp") == 0)
	{
		return 0;
	}
	if(strcmp(proto, "tcp") == 0)
	{
		return 0;		
	}
	
	if(strcmp(proto, "ipv4") == 0)
	{
		printf(" %d\n", sizeof(ipv4_header_t));
		
		packet_add_header(p, sizeof(ipv4_header_t));
		
		ipv4_header_t *h = (ipv4_header_t *) p->data;
		h->protocol = IPV4_PROTOCOL_ICMP;
		
		return 1;
	}
	if(strcmp(proto, "icmp") == 0)
	{
		printf(" %d\n", sizeof(icmp_header_t));
		
		packet_add_header(p, sizeof(icmp_header_t));
		
		icmp_header_t *h = (icmp_header_t *) p->data;
		h->type = ICMP_ECHO_REQUEST;
		
		return 1;
	}
	
	if(strcmp(proto, "eth") == 0)
	{
		printf(" %d\n", sizeof(eth_header_t));
		
		packet_add_header(p, sizeof(eth_header_t));
		
		eth_header_t *h = (eth_header_t *) p->data;
		
		return 1;
	}
	if(strcmp(proto, "ppp") == 0)
	{
		printf(" %d\n", sizeof(ppp_header_t));
		packet_add_header(p, sizeof(ppp_header_t));
		
		return 1;		
	}
	if(strcmp(proto, "wifi") == 0)
	{
		return 0;		
	}
	if(strcmp(proto, "arp") == 0)
	{
		return 0;		
	}
	
	
	// Protocollo non trovato
	return 0;
}



/**
 * Programma per generare codice C (array) di pacchetti di vari protocolli,
 * 	anche concatenati
 */
int main(int argc,  char *argv[])
{
	if(argc < 3)
	{
		printf("use:\n\t%s ... eth ip tcp data", argv[0]);
		return 0;
	}
	
	int i;
	packet_t *p = packet_create(argv[argc-1], strlen(argv[argc-1]));
	

	for(i = (argc - 2); i > 0; i--)
	{
		if(add_proto(p, argv[i]))
			printf("%s added\n", argv[i]);
		else
		{
			printf("unknow protocol %s\n", argv[i]);
			return 0;
		}
	}
	
	printf("%d\n\n", p->size);
	
	char *c_data = (char *) malloc(p->size * 6 + 30);
	
	strcpy(c_data, "char test_packet[] = {\t");
	
	for(i = 0; i < p->size; i++)
	{
		char t_data[8];
		sprintf(t_data, "0x%.2X", p->data[i]);
		strcat(c_data, t_data);
		
		if(i < p->size -1) 
		{
			if(((i % 7) == 0) && i > 3)
				strcat(c_data, ",\n\t\t\t\t\t\t");
			else
				strcat(c_data, ", ");
		}
	}
	
	strcat(c_data, " };\n");
	
	char t_data[8];
	sprintf(t_data, "%d", p->size);
	strcat(c_data, "packet_t *pack = packet_create(test_packet, ");
	strcat(c_data, t_data);
	strcat(c_data, ");\n\n");
	
	printf("\n%s\n", c_data);
	
	
	return 0;
}
