#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include "log.h"

#define SEND_PORT 18000
#define RCV_PORT 18001
#define NODE_BROADCAST_PORT 20000
#define SocketQueueSize 20
#define BUFLEN 51200

void *UDPtoServer();
void *TCPtoServer();
void *udpListener();
void *tcpServertoNodes();
