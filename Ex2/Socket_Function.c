#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define PORT 3550
#define BACKLOG 12

int main()
{
	int fd1, fd2 ;
	struct sockaddr_in server;
	struct sockaddr_in client;

	int sin_size;
	if((fd1 = socket(AF_INET, SOCK_STREAM,0)) == -1)
	{
		printf("socket() error\n");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero),8);
	
	if(bind(fd1,(struct sockaddr*)&server,sizeof(struct sockaddr)) == -1)
	{
		printf("bind() error\n");
		exit(-1);
	}
	
	if(listen(fd1,BACKLOG) == -1)
	{
		printf("listen() error\n");
		exit(-1);
	}
	
	printf("server is in accept mode\n");
	
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if((fd2 = accept(fd1,(struct sockaddr*)&client,&sin_size)) == -1)
		{
			printf("accept() error\n");
			exit(-1);
		}
		else
		{
			printf("Server is in accept mode\n");
			printf("You got a connection from %s\n", inet_ntoa(client.sin_addr));
			close(fd2);
		}
	}
}
