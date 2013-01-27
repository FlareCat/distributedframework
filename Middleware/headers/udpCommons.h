#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#define SEND_PORT 18000
#define RCV_PORT 18001
/*
#define logInit(l) { \
	system("touch ../logFile.txt"); \
	l = fopen("../logFile.txt", "a"); \
}

#define logError(errNo, message) { \
	char errDesc[100] = "", temp[100] = ""; \
	strcat(errDesc, message); \
	strcat(errDesc, " "); \
	strerror_r(errNo, temp, 100); \
	strcat(errDesc, temp); \
	strcat(errDesc, "\n\0"); \
	fprintf(l, errDesc); \
	exit(EXIT_FAILURE); \
}
*/
#define SocketQueueSize 20
#define BUFLEN 51200

void *UDPtoServer();
void *algo_TCPtoServer();
