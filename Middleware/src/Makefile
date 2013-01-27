broadcast: send_algoData.o broadcast_send.o broadcast_recv.o main.o openTCPClient.o openTCPServer.o app_recv.o work_division.o
	gcc -o broadcast send_algoData.o broadcast_send.o broadcast_recv.o openTCPClient.o openTCPServer.o main.o app_recv.o work_division.o -g -pthread
	rm -rf *.o
work_divide.o:
	gcc -c work_division.c -g
app_recv.o:
	gcc -c app_recv.c -g
openTCPClient.o:
	gcc -c openTCPClient.c -g 
openTCPServer.o:
	gcc -c openTCPServer.c -g 
broadcast_send.o: broadcast_send.c broadcast.h
	gcc -c broadcast_send.c -g -pthread
broadcast_recv.o: broadcast_recv.c broadcast.h
	gcc -c broadcast_recv.c -g -pthread
send_algoData.o: send_algoData.c broadcast.h
	gcc -c send_algoData.c -g -pthread
main.o: main.c broadcast.h
	gcc -c main.c -g -pthread
clean:
	rm -rf *.o broadcast
