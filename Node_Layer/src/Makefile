all: node distributedFramework.a
node: node.o tcpToServer.o udpToServer.o openTCPServer.o openTCPClient.o createBinary.o udpListenerForChunkBroadcasts.o tcpClientToSendChunk.o tcpServertoNodes.o
	gcc -o node node.o tcpToServer.o udpToServer.o openTCPServer.o openTCPClient.o createBinary.o udpListenerForChunkBroadcasts.o tcpClientToSendChunk.o tcpServertoNodes.o -g -pthread
	rm -f *.o
tcpServertoNodes.o: tcpServertoNodes.c ../headers/tcpCommons.h
	gcc -c -g tcpServertoNodes.c
node.o: node.c ../headers/udpCommons.h
	gcc -c -g node.c
tcpToServer.o: tcpToServer.c ../headers/udpCommons.h
	gcc -c -g tcpToServer.c
udpToServer.o: udpToServer.c ../headers/udpCommons.h
	gcc -c -g udpToServer.c
openTCPServer.o: openTCPServer.c ../headers/tcpCommons.h
	gcc -c -g openTCPServer.c
openTCPClient.o: openTCPClient.c ../headers/tcpCommons.h
	gcc -c -g openTCPClient.c
createBinary.o: createBinary.c
	gcc -c -g createBinary.c
udpListenerForChunkBroadcasts.o: udpListenerForChunkBroadcasts.c ../headers/udpCommons.h
	gcc -c -g udpListenerForChunkBroadcasts.c
tcpClientToSendChunk.o: tcpClientToSendChunk.c ../headers/tcpCommons.h
	gcc -c -g tcpClientToSendChunk.c
distributedFramework.a: broadcastSend.c tcpServertoNodes.c getChunk.c openTCPNonblockingServer.c ../headers/udpCommons.h ../headers/tcpCommons.h
	gcc -c -g broadcastSend.c getChunk.c openTCPServer.c
	ar rvs ../bin/distributedFramework.a broadcastSend.o getChunk.o openTCPServer.o
	rm -f *.o
clean: 
	rm -f *.o node
	rm -f ../bin/application ../bin/distributedFramework.a
