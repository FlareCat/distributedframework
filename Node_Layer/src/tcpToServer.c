#include "../headers/tcpCommons.h"

extern FILE *l;

void *TCPtoServer() {
	int socketFD, acceptedSocketFD;
	int clientAddrSize = sizeof(struct sockaddr);
	int libraryBytes = 0, chunkBytes = 0;
	struct sockaddr_in clientAddress;
	char chunk_buffer[BUFLEN] = "", library_buffer[BUFLEN] = "", response[] = "Received the algorithm and the chunk details. Processing...", clientAddr[16];
	FILE *chunk = NULL, *library = NULL;

	socketFD = openTCPServerSocket(TCP_PORT, 50);
	
	fprintf(l, "Created a socket. Waiting for the middleware to connect...\n");

	if( (acceptedSocketFD = accept(socketFD, (struct sockaddr *)&clientAddress, &clientAddrSize)) == -1) 
		logError(errno, "An error occurred while attempting to accept a queued socket connection request.");
		
	fprintf(l, "Server online. Waiting for a client...\n");
	
	strcpy(clientAddr, inet_ntoa(clientAddress.sin_addr));
	clientAddr[strlen(clientAddr)] = '\0';
	fprintf(l, "Connection established with %s\n", clientAddr);
		
	/* Receiving the chunk file */
	if( (chunkBytes = recv(acceptedSocketFD, chunk_buffer, BUFLEN, 0)) == -1) 
		logError(errno, "Could not receive the message from the client.");
		
	fprintf(l, "Received the chunk file.\n");

	if( send(acceptedSocketFD, response, strlen(response), 0) == -1) 
		logError(errno, "An error occurred while trying to send the response to the server.");
	fprintf(l, "Sent (to %s:%d) acknowledgement for receiving the chunk file.\n", clientAddr, ntohs(clientAddress.sin_port));

	chunk = fopen("../application_details/chunks.txt", "w");
	library = fopen("../bin/application.a", "w");

	/* Receiving library file */
	if( (libraryBytes = recv(acceptedSocketFD, library_buffer, BUFLEN, MSG_WAITALL)) == -1) 
		logError(errno, "Could not receive the message from the client.");
	printf("Library file size: %d\n", libraryBytes);
	/*libraryBytes = atoi(library_buffer);
	printf("Library file size: %d\n", libraryBytes);
	int bytesRcvd = 0;
	int tempBytesRcvd = 0;
	while(bytesRcvd < libraryBytes) {
		printf("Waiting for data... Received so far %d.\n", bytesRcvd);
		tempBytesRcvd = recv(acceptedSocketFD, library_buffer, BUFLEN, 0);
		bytesRcvd += tempBytesRcvd;
		library = fopen("../bin/application.a", "a");
		fread(library_buffer, tempBytesRcvd, 1, library);
		library_buffer = "";
		fclose(library);
	}*/
		
	/*if( send(acceptedSocketFD, response, strlen(response), 0) == -1) 
		logError(errno, "An error occurred while trying to send the response to the server.");
	fprintf(l, "Sent (to %s:%d) acknowledgement for receiving the library file.\n", clientAddr, ntohs(clientAddress.sin_port));*/
	
	fprintf(l, "Received the library file.\n");

	fwrite(chunk_buffer, chunkBytes, 1, chunk);
	fclose(chunk);
	fprintf(l, "Created the chunks.txt file in application_details/.\n");
	fwrite(library_buffer, libraryBytes, 1, library);
	fclose(library);
	fprintf(l, "Created the application.a file in bin/.\n");

	return NULL;	
}
