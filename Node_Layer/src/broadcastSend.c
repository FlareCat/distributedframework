#include "../headers/udpCommons.h"
FILE *l = NULL;

void broadcastSend(char *broadcastMessage) {
	logInit(l);
	if(l == NULL) {
		printf("Log error");
		exit(1);
	}
	int broadcasterSocket;
	struct sockaddr_in listenerAddress;
	int message, checkCall;
	int broadcastOn = 1;
	int broadcastOff = 0;

	broadcasterSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (broadcasterSocket == -1)
		logError(errno, " Could not create the broadcaster socket.");

	bzero(&listenerAddress, sizeof(listenerAddress));
	listenerAddress.sin_family=AF_INET;
	listenerAddress.sin_port=htons(NODE_BROADCAST_PORT);
	 
	checkCall = setsockopt(broadcasterSocket, SOL_SOCKET, SO_BROADCAST, &broadcastOn, 4);
	if(checkCall == -1)
		logError(errno, "Could not enable the broadcast option on the created socket.");
	
	listenerAddress.sin_addr.s_addr = INADDR_BROADCAST;
 	
	fprintf(l, "Created a broadcaster socket.\n");
	
	int broadcastMessageLen = sizeof(broadcastMessage) + 1; 
	message = sendto(broadcasterSocket, broadcastMessage, broadcastMessageLen, 0, (struct sockaddr *) &listenerAddress, sizeof(listenerAddress));
	if (message ==-1)
		logError(errno, "An error occurred while trying to broadcast the required chunk ID.");
	fprintf(l, "Broadcasted for chunk %s.\n", broadcastMessage);
}
