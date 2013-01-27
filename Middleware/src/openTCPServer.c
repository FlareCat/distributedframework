#include "../headers/tcpCommons.h"

extern FILE *l;

int openTCPServerSocket(int Port, int SocketQueueSize) {
	int socketFD;
	struct sockaddr_in myAddress;
	int yes = 1;

	if( (socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
		logError(errno, "Could not create the socket.");
	if( (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1 ) 
		logError(errno, "Could not set the socket options.");

	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(Port);
	myAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(myAddress.sin_zero), '\0', 8);

	if( bind(socketFD, (struct sockaddr *)&myAddress, sizeof(struct sockaddr)) == -1) 
		logError(errno, "Could not bind the port address to the socket.");

	if( listen(socketFD, SocketQueueSize) == -1) 
		logError(errno, "An error occurred while attempting to listen to the socket.");
	
	return socketFD;
}
