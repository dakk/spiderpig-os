#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("use:\n\tirc server port nick\n");
		return 0;
	}
	
	// Indirizzo del server e del client
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr;
	int error;
	int sd;
	char buf[1024];

	// Inizializza porta e indirizzo del server
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons((u_short) atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)gethostbyname(argv[1])->h_addr)); 

	// Inizializza il socket tcp
	sd = socket(AF_INET,SOCK_STREAM,0);

	// Connette al server	
	error = connect(sd,(struct sockaddr*) &server_addr, sizeof(server_addr)); 
	if(error)
	{
		printf("cannot connect.\n");
		return 0;
	}
	
	// Invia il nick
	strcpy(buf, "nick ");
	strcat(buf, argv[3]);
	strcat(buf, "\n");
	send(sd, buf, strlen(buf), 0);

	// Identifica l'user
	strcpy(buf, "user ");
	strcat(buf, argv[3]);
	strcat(buf, " 127.0.0.1 ");
	strcat(buf, argv[3]);
	strcat(buf, "@localhost ");
	strcat(buf, argv[3]);
	strcat(buf, "\n");
	send(sd, buf, strlen(buf), 0);

	
	while(1)
	{
		recv(sd, &buf, 1024, 0);
		printf("%s\n", buf);
		scanf("%s", buf);
		
		if(strcmp(buf, "/exit") == 0)
		{
			return 0;
		}
		strcat(buf, "\n");
		send(sd, buf, strlen(buf), 0);
	}	
		
	return 0;
}
