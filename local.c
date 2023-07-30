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

	char* sended = "Hello";
	char* received = (char*)malloc(16);

	struct sockaddr_un serv;
	struct sockaddr_un client;
	socklen_t length;

	int accept_fd, massege_fd;

	accept_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (-1 == accept_fd) {
		perror("didnt create");
		exit(EXIT_FAILURE);
	}

	memset(&serv, 0, sizeof(struct sockaddr_un));
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, name);

	if (-1 == bind(accept_fd, (struct sockaddr*)&serv, sizeof(struct sockaddr_un))) {
		perror("didnt bind");
		close(accept_fd);
		exit(EXIT_FAILURE);
	}

	if (-1 == listen(accept_fd, 5)) {
		perror("didnt listen");
		close(accept_fd);
		exit(EXIT_FAILURE);
	}

	massege_fd = accept(accept_fd, (struct sockaddr*)&client, &length);
	if (-1 == massege_fd) {
		perror("didnt accept");
		close(accept_fd);
		exit(EXIT_FAILURE);
	}

	if (-1 == send(massege_fd, sended, strlen(sended) + 1, 0)) {
		perror("didnt send");
		close(accept_fd);
		exit(EXIT_FAILURE);
	}

	recv(massege_fd, received, 16, 0);

	close(accept_fd);
	close(massege_fd);

	printf("received: %s\n", received);

	exit(EXIT_SUCCESS);
}