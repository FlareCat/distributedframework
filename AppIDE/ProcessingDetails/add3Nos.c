#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char *buffer = NULL;
	int bufSize = 0;
	int a = 0, b = 0, c = 0;
	FILE *c1 = getChunk("1.dat");
	FILE *c2 = getChunk("2.dat");
	FILE *c3 = getChunk("3.dat");
	
	if(c1 == NULL) {
		printf("1.dat not found");
		exit(1);
	}
	else {
		getline(&buffer, (size_t *)&bufSize, c1);
		buffer[strlen(buffer)-1] = '\0';
		a = atoi(buffer);
	}
	
	if(c2 == NULL) {
		printf("2.dat not found");
		exit(1);
	}
	else {
		getline(&buffer, (size_t *)&bufSize, c2);
		buffer[strlen(buffer)-1] = '\0';
		b = atoi(buffer);
	}
	
	if(c3 == NULL) {
		printf("3.dat not found");
		exit(1);
	}
	else {
		getline(&buffer, (size_t *)&bufSize, c3);
		buffer[strlen(buffer)-1] = '\0';
		c = atoi(buffer);
	}
	printf("value of a,b,c is ::: %d, %d, %d", a,b,c);
	printf("Sum = %d", (a+b+c));
	return 0;
}
