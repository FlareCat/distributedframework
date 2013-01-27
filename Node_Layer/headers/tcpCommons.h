#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include "log.h"

#define TCP_PORT 16000
#define TCP_PORT_TO_NODES 30000
#define BUFLEN 51200

int openTCPClientSocket(char *, int);
int openTCPServerSocket(int, int);
int openTCPNonblockingServerSocket(int, int);
