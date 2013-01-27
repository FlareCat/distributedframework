// Inbuild Headers
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

// User Defined headers
#include "../headers/udpCommons.h"

// function Declarations
void* broadcast_recieve( void * argv);
void* broadcast_send( void * argv);
void* send_algoData(void * argv);
