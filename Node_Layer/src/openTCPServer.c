#include "../headers/tcpCommons.h"

extern FILE *l;

int openTCPServerSocket(int Port, int SocketQueueSize) {
	int socketFD;
	struct sockaddr_in myAddress;
	int yes = 1;

	fprintf(l, "Opening a TCP server socket.\n");
	if( (socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
		logError(errno, "Could not create the socket.");
	fprintf(l, "Created the socket.\n");
	if( (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1 ) 
		logError(errno, "Could not set the socket options.");
	fprintf(l, "Set the socket address to be reusable.\n");

	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(Port);
	myAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(myAddress.sin_zero), '\0', 8);

	if( bind(socketFD, (struct sockaddr *)&myAddress, sizeof(struct sockaddr)) == -1) 
		logError(errno, "Could not bind the port address to the socket.");
	fprintf(l, "Bound the port %d to the socket.\n", Port);

	if( listen(socketFD, SocketQueueSize) == -1) 
		logError(errno, "An error occurred while attempting to listen to the socket.");
	fprintf(l, "Marked the socket to allow for incoming connections.\n");
	
	return socketFD;
}
