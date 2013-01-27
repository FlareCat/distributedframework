#include "broadcast.h"
#include "../headers/udpCommons.h"
#include "../headers/tcpCommons.h"

extern FILE *l;
//extern int node_no;
//extern int max_nodes;
/* Thread that revieves the reply for the Broadcast Packet */
void* broadcast_recieve( void * argv) {
	pthread_t tcp_client_ProcessInfo;
	
	int socketFD, bytesSent = 0;
	struct sockaddr_in serverAddress, myAddress;
	char buffer[100] = "" , response[] = "Yes I can do work.";
	int bytesRcvd, serverSize, yes = 1;
	int clientAddrSize = sizeof(struct sockaddr);
		
	if( (socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		logError(errno, "Could not create a socket.");
	}
	
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(SEND_PORT);
	myAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(myAddress.sin_zero), '\0', 8);
	memset(&(serverAddress.sin_zero), '\0', 8);

	if( bind(socketFD, (struct sockaddr *)&myAddress, sizeof(myAddress)) == -1) {
		logError(errno, "Could not bind the address to the created socket.");
	}
	
	serverSize = sizeof(serverAddress);

	while(1) {
		bytesRcvd = recvfrom(socketFD, buffer, 100, 0, (struct sockaddr *)&serverAddress, &serverSize);
		if(bytesRcvd == -1) {
			logError(errno, "\nAn error occurred while waiting for data.");
		}
		fprintf(l, "Broadcast recieved from %s..Establishing TCP connection to send the details\n", inet_ntoa(serverAddress.sin_addr));
	//	if(node_no <= max_nodes)
		pthread_create(&tcp_client_ProcessInfo, NULL, send_algoData, (void *)inet_ntoa(serverAddress.sin_addr));
		pthread_join(tcp_client_ProcessInfo, NULL);
		char node_file[] = "cd ../NodeDetails;touch ";
		strcat(node_file, inet_ntoa(serverAddress.sin_addr));
		system(node_file);
	
	}
	return NULL;
}
