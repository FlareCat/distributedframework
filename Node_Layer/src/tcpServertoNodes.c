#include "../headers/tcpCommons.h"
#include <sys/types.h>
#include <sys/stat.h>
extern FILE *l;

void alarmHandler(int signum) {
	fprintf(l, "Could not locate the missing chunk.\n");
	exit(EXIT_SUCCESS);
}

void *tcpServertoNodes() {
	struct timeval timeout;
	int chunkReceiverSocket, acceptedReceiverSocket;
	int clientAddrSize = sizeof(struct sockaddr);
	int selectRetval;
	struct sockaddr_in clientAddress;
	char buffer[BUFLEN] = "", clientAddr[16];

	chunkReceiverSocket = openTCPServerSocket(TCP_PORT_TO_NODES, 50);
	
	while(1) {
		printf("Waiting for a connection...\n");
		if( (acceptedReceiverSocket = accept(chunkReceiverSocket, (struct sockaddr *)&clientAddress, &clientAddrSize)) == -1)
			logError(errno, "An error occurred while trying to accept a queued socket connection.");
	
		fprintf(l, "Server online. Waiting for a client...\n");
		
		strcpy(clientAddr, inet_ntoa(clientAddress.sin_addr));
		clientAddr[strlen(clientAddr)] = '\0';
		printf("Connection established with %s\n", clientAddr);
	
		int bytesRcvd = 0;
		printf("Waiting for chunk..\n");
		strcpy(buffer, "");
		if( (bytesRcvd = recv(acceptedReceiverSocket, buffer, BUFLEN, 0)) == -1) 
			logError(errno, "Could not receive the message from the client.");
			
		char path[20] = "";
		
		FILE *chunkStorage;
		printf("Received chunk data :%s", buffer);
		printf("Waiting to write to the chunk file...\n");
		int chunkFile = open("../chunks/current.tmp", 0666);
		write(chunkFile, buffer, bytesRcvd);
		printf("Wrote to the chunk file.\n");
		fprintf(l, "Created the chunk file locally in chunks/.\n");
		close(acceptedReceiverSocket);
	}
}
