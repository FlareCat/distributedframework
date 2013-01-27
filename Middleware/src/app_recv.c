#include "../headers/udpCommons.h"
#include "../headers/tcpCommons.h"
#include "broadcast.h"
extern FILE *l;

/* This is used to get the library file to be executed on the nodes and a configuration file which contains that the program has to be 
    executed in the no of nodes in parallel and the chunk ids used by the application
 */
void *algo_TCPtoServer() {
        int acceptedSocketFD, socketFD;
        int clientAddrSize = sizeof(struct sockaddr);
	int recv_size;
        struct sockaddr_in clientAddress;
        char lib_buffer[BUFLEN] = "", clientAddr[16];
	char chunk_buffer[BUFLEN] = "";

	// Function used to Open a TCP server Socket and return File Descriptor of the socket
        socketFD = openTCPServerSocket(TCP_PORT, 20);
        if( (acceptedSocketFD = accept(socketFD, (struct sockaddr *)&clientAddress, &clientAddrSize)) == -1)
                logError(errno, "An error occurred while attempting to accept a queued socket connection request.");
        fprintf(l, "Server online. Waiting for a client...\n");
	close(socketFD);
        strcpy(clientAddr, inet_ntoa(clientAddress.sin_addr));
        clientAddr[strlen(clientAddr)] = '\0';
        fprintf(l, "Connection established with %s\n", clientAddr);

	// Receiving Library file
       if( (recv_size = recv(acceptedSocketFD, lib_buffer, sizeof(lib_buffer), 0)) == -1)
                logError(errno, "Could not receive the message from the client.");
       fprintf(l, "Received : %s\n", lib_buffer);

        /* Writing the recieved binary data to output file */
        FILE *b_file = fopen("../ApplicationDetails/ApplicationName.a", "w");
        fwrite(lib_buffer, recv_size, 1, b_file);
        fclose(b_file);

	strcpy(lib_buffer, "SUCCESS_ALGO_BINARY");
 
 	// Sending ACK to binary file
	if(send(acceptedSocketFD, lib_buffer, sizeof(lib_buffer), 0) == -1)
                 logError(errno, "Could not send the message from the client.");
	

	// Recieving CHUNK file
        if( (recv_size = recv(acceptedSocketFD, chunk_buffer, sizeof(chunk_buffer), 0)) == -1)
                 logError(errno, "Could not receive the message from the client.");
       // Writing the chunk data to a file
        FILE *chunk_file = fopen("../ApplicationDetails/chunkDetails", "w");
        fwrite(chunk_buffer, recv_size, 1, chunk_file);
        fclose(chunk_file);
	strcpy(chunk_buffer, "SUCCESS_ALGO_CHUNKS");

	// Sending ACK Chunks file
        if(send(acceptedSocketFD, chunk_buffer, BUFLEN, 0) == -1)
                 logError(errno, "Could not send the message from the client.");

       fprintf(l, "Received : %s\n", chunk_buffer);
}
