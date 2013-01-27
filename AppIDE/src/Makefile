./app: main.o  openTCPClient.o sendProcessingDetails.o
	gcc -o app main.o openTCPClient.o sendProcessingDetails.o -g -pthread
	rm *.o
main.o: main.c
	gcc -c main.c -pthread
sendProcessingDetails.o: sendProcessingDetails.c
	gcc -c sendProcessingDetails.c
openTCPClient.o: openTCPClient.c
	gcc -c openTCPClient.c
clean:
	rm *.o app
