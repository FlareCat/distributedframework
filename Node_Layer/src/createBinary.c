#include "../headers/tcpCommons.h"
#include <unistd.h>
#include <fcntl.h>
extern FILE *l;

void createBinary(int noOfChunks, char **chunkIDs) {
	char command[] = "gcc -o ../bin/application -g ../bin/application.a ../bin/distributedFramework.a";
	system(command);
	system("rm -f ../application_details/result.txt");
	pid_t application = fork();
	if(application == -1) {
		logError(errno, "An error occurred while trying to fork the application.");
	}
	else if(application == 0) {	// Inside the application process space
		char *execCmd = NULL;
		int i = 0;
		execCmd = (char *) calloc(19, sizeof(char));
		strcpy(execCmd, "../bin/application ");
		for (i = 0; i < noOfChunks; i++) {
			strcat(execCmd, chunkIDs[i]);
		}
		strcat(execCmd, ">> ../application_details/result.txt");
		fprintf(l, "Compiled the application with the distributed framework.\n");
		fprintf(l, "Executing the command : '%s' ...\n", execCmd);
		system(execCmd);
	}
	else { 				// Parent process
		waitpid(application, NULL, 0);
		fprintf(l, "Completed execution and stored the result in application_details/result.txt.\n");
	}
	return;
}
