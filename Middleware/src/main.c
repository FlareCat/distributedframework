#include "broadcast.h"
#include "../headers/tcpCommons.h"

//Log file variable declaration
FILE *l;

// Main function of Middleware where the execution starts
int main(int argc, char* argv[]){
	system("clear");
	
	logInit(l); // Log file Initialization
	// Thread Declaration
	pthread_t send_broadcast;
	pthread_t recv_broadcastReply;
	pthread_t app_recv;
	pthread_t process_distribution;
	pthread_t process;

	// Thread to recieve data from application Layer
	printf("Process Initiated.. Waiting for the Details regarding Application\n");	
	pthread_create(&app_recv, NULL, algo_TCPtoServer, NULL);
	pthread_join(app_recv, NULL);
	printf("Application Details recieved successfully...\n");
	// Thread Creation to Divide the work among multiple nodes
	pthread_create(&process, NULL, divide_chunks, NULL);
	pthread_join(process, NULL);

	// Thread Creation for broadcast send and recieve
	pthread_create(&send_broadcast, NULL, broadcast_send, NULL);
	pthread_create(&recv_broadcastReply, NULL, broadcast_recieve, NULL);

	// Joining Threads
	pthread_join(recv_broadcastReply, NULL);
	pthread_join(send_broadcast, NULL);

	return 0;
}// End of Main Function
