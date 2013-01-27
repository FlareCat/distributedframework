#include "../headers/tcpCommons.h"

extern FILE *l;

void sendChunk(char *destinationIP, char *chunkID) {
	int socketFD;
	char buffer[BUFLEN] = "";
	char chunkPath[30] = "../chunks/";
	strcat(chunkPath, chunkID);
	FILE *chunkPtr = fopen(chunkPath, "r");
	long chunkFileSize = 0;
	
	// Calculate the chunk file size
	fseek(chunkPtr, 0, SEEK_END);
	chunkFileSize = ftell(chunkPtr);
	fseek(chunkPtr, 0, SEEK_SET);

	// Send the file contents to the destination IP
	socketFD = openTCPClientSocket(destinationIP, TCP_PORT_TO_NODES);
	fread(buffer, chunkFileSize, 1, chunkPtr);
	if( send(socketFD, buffer, chunkFileSize, 0) == -1)
		logError(errno, "An error occurred while trying to send the requested chunk.");
	printf("Sent chunk %s to %s successfully.\n", chunkID, destinationIP);
	return;
}
