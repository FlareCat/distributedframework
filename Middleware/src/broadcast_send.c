#include "broadcast.h"

extern FILE *l;

/* thread to send the Broadcast Packets at Regular Intervals */
void *broadcast_send(void *argv) {
	char buf[BUFLEN];
	int clientToServer_socket;
	unsigned int fromLength;
	struct sockaddr_in Remote_Address, Server_Address;
	int message, checkCall;
	int broadcastOn = 1;
	int broadcastOff = 0;
	char *broadcastMessage;
	broadcastMessage = "HELLO";
 
	/*Create client socket*/
	clientToServer_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientToServer_socket==-1)
    	perror("Error: client socket not created");
 
   	/*Fill in client's sockaddr_in */
   	bzero(&Remote_Address, sizeof(Remote_Address));
   	Remote_Address.sin_family=AF_INET;
 
   	// Port no as argument
   	Remote_Address.sin_port=htons(RCV_PORT);
 
   	checkCall = setsockopt(clientToServer_socket, SOL_SOCKET, SO_BROADCAST, &broadcastOn, 4);
   	if(checkCall == -1)
    		perror("Error: setsockopt call failed");

   	Remote_Address.sin_addr.s_addr = INADDR_BROADCAST;

   	// Broadcast Message Used to Ping the Nodes
   	int broadcastMessageLen = sizeof(broadcastMessage) + 1; 
   	while(1){
		printf("Broadcasting...( %s )\n", broadcastMessage);
   		message = sendto(clientToServer_socket, broadcastMessage, broadcastMessageLen, 0, (struct sockaddr *) &Remote_Address, sizeof(Remote_Address));
   		if (message ==-1)
  			perror("Error: sendto call failed");

		sleep(15);
   	}

}// End Broadcast
