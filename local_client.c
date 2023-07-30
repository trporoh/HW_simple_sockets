#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/un.h>
#include <unistd.h>

#define name "/tmp/sockbuffer"

int main(int argc, char** argv) {

	struct sockaddr_un serv;

	char* sended = "Hi";
	char* received = (char*)malloc(16);

	int request_fd, massege_fd;
	socklen_t length;

	massege_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, name);

	if (-1 == connect(massege_fd, (struct sockaddr*) &serv, sizeof(struct sockaddr_un))) {
		perror("didnt connected");
		exit(EXIT_FAILURE);
	}

	recv(massege_fd, received, 16, 0);

	send(massege_fd, sended, strlen(sended), 0);

	close(massege_fd);

	printf("received: %s\n", received);

	exit(EXIT_SUCCESS);

}