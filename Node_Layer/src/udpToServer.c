#include "../headers/udpCommons.h"

extern unsigned char IP[15];
extern FILE *l;

void *UDPtoServer() {
	int socketSender, socketReceiver, bytesSent = 0;
	struct sockaddr_in serverAddress, senderAddress, receiverAddress;
	char buffer[BUFLEN] = "" , response[] = "Hi! Give me some work!";
	int bytesRcvd, serverSize, yes = 1;
	int clientAddrSize = sizeof(struct sockaddr);
		
	if( (socketSender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
		logError(errno, "Could not create sender socket.");
	
	if( (socketReceiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) 
		logError(errno, "Could not create receiver socket.");
	
	if( (setsockopt(socketReceiver, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1 ) 
		logError(errno, "Could not make the receiver port reusable.");
	
	fprintf(l, "Created a socket.\n");

	senderAddress.sin_family = AF_INET;
	senderAddress.sin_port = htons(SEND_PORT);
	senderAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(senderAddress.sin_zero), '\0', 8);
	
	receiverAddress.sin_family = AF_INET;
	receiverAddress.sin_port = htons(RCV_PORT);
	receiverAddress.sin_addr.s_addr = INADDR_ANY;
	memset(&(receiverAddress.sin_zero), '\0', 8);
	
	memset(&(serverAddress.sin_zero), '\0', 8);
	
	if( bind(socketReceiver, (struct sockaddr *)&receiverAddress, sizeof(receiverAddress)) == -1) 
		logError(errno, "Could not bind the port address to the receiver socket.");

	serverSize = sizeof(serverAddress);
	fprintf(l, "Waiting for the server request...\n");
	bytesRcvd = recvfrom(socketReceiver, buffer, 100, 0, (struct sockaddr *)&serverAddress, &serverSize);
	if(bytesRcvd == -1) 
		logError(errno, "An error occurred while waiting for data.");
	
	strcpy(IP, inet_ntoa(serverAddress.sin_addr));
	fprintf(l, "Received (from %s:%d): %s\n", IP, ntohs(serverAddress.sin_port), buffer);
	serverAddress.sin_port = htons(SEND_PORT);
	
	if( sendto(socketSender, response, strlen(response), 0, (struct sockaddr *)&serverAddress, serverSize) == -1) 
		logError(errno, "An error occurred while attempting to send the response.");
	
	fprintf(l, "Sent '%s'.\n", response);

	return NULL;
}
