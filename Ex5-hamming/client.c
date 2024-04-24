#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 4771
int main(int argc,char *argv[])
{
        int sockfd;
        struct sockaddr_in serv;
        char buff[100];
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        printf("Client Socket Created Successfully.\n");
        memset(&serv,0,sizeof(serv));
        serv.sin_family=AF_INET;
        serv.sin_port=htons(PORT);
        serv.sin_addr.s_addr=INADDR_ANY;
        if (connect(sockfd,(struct sockaddr *)&serv, sizeof(serv))<0)
        {
                printf("error in connect");
                exit(0);
        }
        printf("Client Socket with Server Successfully.\n");
        do
        {
                strcpy(buff," ");
                printf("Client. :");
                int n,r;
    
    
                printf("Enter the data: ");
                fgets(buff,100,stdin);
                write(sockfd,buff,100);
                if(strcmp(buff,"bye\n")==0)
                {
                        printf("Client: %s",buff);		
                        goto stop;
                }	
                strcpy(buff," ");
                read(sockfd,buff,sizeof(buff));
                printf("From Server :%s\n",buff);
        }while(strcmp(buff,"bye\n")!=0);
        stop: 
        exit(0);
        close(sockfd);
        return 0;
}

