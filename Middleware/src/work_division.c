#include "../headers/udpCommons.h"
#include "../headers/tcpCommons.h"
#include <dirent.h>
int getTotalChunks(char *chunk_file) {
	char *line = NULL;
	FILE *fp;
	size_t len = 0;
	size_t read;
	int count = 0;
	fp = fopen(chunk_file, "r");
	if(fp == NULL)
		exit(EXIT_FAILURE);
	else {
		while(getline(&line, &len, fp) != -1){
			count ++;
		}
		return (count-1);
	}
}

void* divide_chunks(void* arg) {
int max_nodes;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int i=0;
	int noOfChunks;
	// Variables used to retrieve files in the directory
        struct dirent **namelist;
	struct dirent *dir_ptr;
	DIR *dir;
	int Total_Chunks=0;
	fp = fopen("../ApplicationDetails/chunkDetails", "r");
	noOfChunks = getTotalChunks("../ApplicationDetails/chunkDetails");	
	if (fp == NULL)
		exit(EXIT_FAILURE);
	if((read = getline(&line, &len,fp)) != -1) {
		max_nodes = atoi(line);
	}
	int j=0;
	for(i=0;i<max_nodes;i++){ 
		char tmp_file[12];
		sprintf(tmp_file, "../ApplicationDetails/chunk%d.dat",i);
		FILE *tmp_chunk = fopen(tmp_file, "w");
		if(tmp_chunk == NULL)
			printf("Error in opening the file");
		for(j=0;j!=(noOfChunks/max_nodes);j++){ 
			if((read = getline(&line, &len,fp)) != -1){
				fwrite(line, read, 1, tmp_chunk);
			}
		}
		fclose(tmp_chunk);
	}
}
