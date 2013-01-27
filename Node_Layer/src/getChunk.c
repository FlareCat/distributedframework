#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE *getChunk(char *chunkID) {
	char *chunkPath = NULL;
	FILE *file;
	chunkPath = (char *)calloc((strlen(chunkID)+10), sizeof(char)); 		// 10 = length(../chunks/)
	strcpy(chunkPath, "../chunks/");
	strcat(chunkPath, chunkID);
	file = fopen(chunkPath, "r");

	if(file != NULL) 	// File exists locally
		return file;
	else { 			// Else broadcast to attempt to retrieve the chunk
		broadcastSend(chunkID);
		mkfifo("../chunks/current.tmp", 0666);
		int bytesRead = 0;
		char *buffer = (char *)calloc(50, sizeof(char));
		printf("Waiting for bytes to be written..\n");
		int chunkRequired = open("../chunks/current.tmp", 0666);
		while(bytesRead == 0) {
			//sleep(5);
			bytesRead = read(chunkRequired, buffer, 50);
		}
		close(chunkRequired);
		printf("Application: Received the chunk data: %s.\n", buffer);
		char chunkFileName[20] = "../chunks/";
		strcat(chunkFileName, chunkID);
		file = fopen(chunkFileName, "w");
		fprintf(file, "%s", buffer);
		printf("Created the chunk %s in chunks/\n", chunkID);
		system("rm -f ../chunks/current.tmp");
		return file;
	}
}	
