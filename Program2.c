#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define BLOCK_SIZE 1024

char* getData(int fd) {
	char* buf = (char*) malloc(BLOCK_SIZE);
	if (!buf) {
		return NULL;
	}
	if (read(fd, buf, BLOCK_SIZE) != BLOCK_SIZE) {
		free(buf);
		return NULL;
	}
	return buf;
}

int main(int argc, char *argv[])
{
	int fd;
	char* data;

	fd = open("/tmp/test.txt", O_WRONLY | O_APPEND);
	
	data = getData(fd);	
	
	printf("Data readed from file: %s", data);


	data = getData(fd);
	close(fd);

	return 0;
}

