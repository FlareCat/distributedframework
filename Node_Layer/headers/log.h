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
