#include "../headers/tcpCommons.h"

extern FILE *l;
// Function to create a Client Socket, Connect with Server with provided details and return Socket File Descriptor
int openTCPClientSocket(char *ServerIP, int Port) {
	int socketFD;
	struct sockaddr_in serverAddress;
	fprintf(l, "Opening a TCP client socket.\n");
	if( (socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
		logError(errno, "Could not create a socket.");
	}
	fprintf(l, "Created a socket.");

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(Port);
	serverAddress.sin_addr.s_addr = inet_addr(ServerIP);
	
	if( connect(socketFD, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) == -1) {
		printf("Could not connect to Middleware.. Please verify the IP\n");
		logError(errno, "Could not connect to the server.");
	}
	fprintf(l, "Connected to the created socket.");

	return socketFD;
}
