#include "../headers/udpCommons.h"
#include <signal.h>

unsigned char IP[15] = "";
FILE *l = NULL;
static char *chunkIDToReceive = NULL;

void parseChunksFile() {
	FILE *chunksFile = fopen("../application_details/chunks.txt", "r");
	if(chunksFile == NULL) {
		logError(errno, "An error occurred while trying to access the chunk details received from the middleware.");
	}
	char **chunksRequired = NULL;
	size_t lineSize = 0;
	int noOfChunks = 0;
	int eof = 0;
	
	while(1) {
		chunksRequired = (char **) realloc(chunksRequired, ((noOfChunks + 1) * sizeof(*chunksRequired)));
		eof = getline(&chunksRequired[noOfChunks], &lineSize, chunksFile);
		if(eof == -1) {
			chunksRequired = (char **) realloc(chunksRequired, noOfChunks * sizeof(*chunksRequired));
			break;
		}
		if(chunksRequired[noOfChunks][eof-1] == '\n') 
			chunksRequired[noOfChunks][eof-1] = ' ';
		noOfChunks++;
	}
	createBinary(noOfChunks, chunksRequired);    // This function links the received application.a with the distributedFramework.a and produces an executable 
	free(chunksRequired);
}

void interruptedHandler(int signum) {
	fprintf(l, "Received signal %d. Ending the node program.\n", signum);
	fclose(l);
	exit(EXIT_SUCCESS);
}

int main(void) {
	system("clear");
	logInit(l);
	system("date >> ../logFile.txt");
	signal(SIGINT, interruptedHandler);

	pthread_t UDPServerListener, UDPNodeListener; 
	pthread_t TCPServerListener, TCPNodeListener;

	// Start an infinite listener for UDP chunk broadcasts
	pthread_create(&UDPNodeListener, NULL, udpListener, NULL);

	// Start an infinite listener to receive the required chunks
	pthread_create(&TCPNodeListener, NULL, tcpServertoNodes, NULL);
	
	// Wait for a broadcast from the server to 'register' into the distributed network
	pthread_create(&UDPServerListener, NULL, UDPtoServer, NULL);
	pthread_join(UDPServerListener, NULL);

	// Listen to the server for receiving the application specific data (chunk IDs, algorithm, etc)
	pthread_create(&TCPServerListener, NULL, TCPtoServer, NULL);
	pthread_join(TCPServerListener, NULL);
	
	parseChunksFile();

	pthread_join(UDPNodeListener, NULL);	
	fclose(l);
	return 0;
}
