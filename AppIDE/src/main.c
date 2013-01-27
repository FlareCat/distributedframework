#include "../headers/tcpCommons.h"
#include "../headers/api.h"

// Log file pointer variable Declaration
FILE *l;
// Main Function
int main(int argc, char *argv[]){
	system("clear");
	logInit(l);	// Log File Initialization
	//Function used to Send the Processing Details to Middleware which inturn distributes the work to multiplenodes to process it
	if(argc != 4){
		printf("USAGE: ./app <Middleware IP> <Library File(.a) name> <Chunk File Name>\n");
		exit(1);
	}
	// Function used to send the algorithm and chunk details to the Middleware which inturn divides the chunkfile and assigns job to each node in distributed environment
	/* ** first argument is the IP address of the Server
	   ** second argument is the path refering the library file
	   ** third argument is the path refering the chunk file
	*/
	sendProcessingDetails(argv[1], argv[2], argv[3]);
	
	return 1;
}// End of Main
