#include "../headers/udpCommons.h"
#include <dirent.h>

extern FILE *l;

// Function returns 0 if a requested chunk is present and returns -1 otherwise.

int isChunkPresent(char *chunkID) {
	char chunkPath[30] = "../chunks/";
	strcat(chunkPath, chunkID);
	if( fopen(chunkPath, "r") == NULL)
		return -1;
	else
		return 0;
}

void *udpListener() {
	int socketFD, bytesSent = 0;
	struct sockaddr_in serverAddress, myAddress;
	char requestedChunk[BUFLEN] = "";
	int bytesRcvd, serverSize, yes = 1;
	int clientAddrSize = sizeof(struct sockaddr);
		
	if( (socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
		logError(errno, "Could not create a socket.");
		
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(NODE_BROADCAST_PORT);
	myAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(myAddress.sin_zero), '\0', 8);
	memset(&(serverAddress.sin_zero), '\0', 8);
	
	if( (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1 ) 
		logError(errno, "Could not set the socket options.");

	if( bind(socketFD, (struct sockaddr *)&myAddress, sizeof(myAddress)) == -1) 
		logError(errno, "Could not bind the address to the created socket.");
	
	serverSize = sizeof(serverAddress);

	while(1) {
		strcpy(requestedChunk, "");
		bytesRcvd = recvfrom(socketFD, requestedChunk, 100, 0, (struct sockaddr *)&serverAddress, &serverSize);
		if(bytesRcvd == -1) 
			logError(errno, "\nAn error occurred while waiting for data.");
		printf("Received broadcast for chunk from %s:%d : %s\n", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port), requestedChunk);
		if( isChunkPresent(requestedChunk) == 0) {
			fprintf(l, "Found chunk %s.\n", requestedChunk);
			sendChunk(inet_ntoa(serverAddress.sin_addr), requestedChunk);
		}							
	}
	return NULL;
}
