#include "../headers/udpCommons.h"
#include "../headers/tcpCommons.h"

extern FILE *l;
extern int noOfFiles;
static int node_no = 0;
//extern int max_nodes;


void *send_algoData(void *get) {

	char* binary = "../ApplicationDetails/ApplicationName.a";
	char  chunks[33]; 
	sprintf(chunks, "../ApplicationDetails/chunk%d.dat",node_no);
	
	node_no++;
	int socketFD;
	int size;
        int clientAddrSize = sizeof(struct sockaddr);
        struct sockaddr_in clientAddress;
        char *lib_buffer;
	char clientAddr[16];
	char *chunk_buffer;
	unsigned long lib_fileLen;
	unsigned long chunk_fileLen;
	char *IP = (char *)get;
	FILE *lib_file;
	FILE *chunk_file;

	/* Code to Send the to Middleware Application*/
	/* put the App binary code in buffer and then send */
	// Open file
	lib_file = fopen(binary, "r");
	chunk_file = fopen(chunks, "r");

	if(!lib_file){
                logError(errno, "Cannot open Binary file.");
	}
	if(!chunk_file){
                logError(errno, "Cannot open Chunks file.");
	}
	// get b_file length
	fseek(lib_file, 0, SEEK_END);
	lib_fileLen = ftell(lib_file);
	fseek(lib_file, 0, SEEK_SET);
	
	// get c_file length
	fseek(chunk_file, 0, SEEK_END);
	chunk_fileLen = ftell(chunk_file);
	fseek(chunk_file, 0, SEEK_SET);

	// Allocate memory
	lib_buffer = (char *)malloc(lib_fileLen+1);
	chunk_buffer = (char *)malloc(chunk_fileLen+1);
	printf("liblen = = %d\nchunk len==%d\n",lib_fileLen,chunk_fileLen);
	if(!lib_buffer){
                	logError(errno, "Memory Error in Binary Buffer.");
	}
	if(!chunk_buffer){
                	logError(errno, "Memory Error in Chunk Buffer.");
	}
	// Reading Contents into B_BUFFER from Binary file
	fread(lib_buffer,lib_fileLen, 1,lib_file);
	// Reading Contents into C_BUFFER from Chunks file
	fread(chunk_buffer, chunk_fileLen, 1,chunk_file);
	fclose(lib_file);
	fclose(chunk_file);

	// Opening Client Socket and Connecting to IP
printf("About to open connection\n");
        socketFD = openTCPClientSocket(IP,16000);
	
	// Sending CHUNKS file
	printf("chunk buffer contents is :::%s",chunk_buffer);
	if( send(socketFD, chunk_buffer, chunk_fileLen, 0) == -1)
               	logError(errno, "Could not receive the message from the client.");
	printf("Data Sent successfully... \n");
	/* Recv the ackowledgement for the binary file */
        if( recv(socketFD, chunk_buffer, BUFLEN, 0) == -1)
        	logError(errno, "Could not receive the message from the client.");
	/* End of Sending Data */
	/* Code to send the binary data...... */
	if( send(socketFD, lib_buffer, lib_fileLen, MSG_MORE) == -1)
               	logError(errno, "Could not receive the message from the client.");
	shutdown(socketFD, SHUT_RDWR);
	/* Code to send the chunk data...... */
        if( recv(socketFD, lib_buffer, lib_fileLen, 0) == -1)
        	logError(errno, "Could not receive the message from the client.");
	printf("Recieved Message from Middleware is ::: %s\n",lib_buffer);
	
	printf("Processing Details Sent Successfully...\n");
}
