#include "../headers/tcpCommons.h"
#include <netinet/tcp.h>

extern FILE *l;

int openTCPClientSocket(char *ServerIP, int Port) {
	int socketFD;
	struct sockaddr_in serverAddress;
	int yes;
	printf("Opening a TCP client socket.\n");
	fprintf(l, "Opening a TCP client socket.\n");
	if( (socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
		logError(errno, "Could not create a socket.");

	fprintf(l, "Created a socket.");

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(Port);
	serverAddress.sin_addr.s_addr = inet_addr(ServerIP);

	setsockopt(socketFD, IPPROTO_TCP, TCP_CORK, &yes, sizeof(yes));		
		
	if( connect(socketFD, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) == -1) 
		logError(errno, "Could not connect to the server.");
	fprintf(l, "Connected to the created socket.");

	return socketFD;
}
