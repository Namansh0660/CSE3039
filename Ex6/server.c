#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 4771

int countWords(int n, char buffer[]){
	FILE* file;
	char str[100],path[100];
	char c;
	int plen=0;
	//strip \n from path;
	for(int i=0;buffer[i]!='\n';i++){
	        plen++;
	        path[i] = buffer[i];
	        
	}
	//strcat(path,"\0");
	path[plen]='\0';
	//strncpy(path,buffer,plen);
	
	printf("\npath=%s\n",path);
	file = fopen(path,"r");
	
	if(file == NULL){
		printf("Error in opening file");
		exit(1);
	}
	int count=0;
	while(fgets(str,100,file) != NULL){
		puts(str);
		printf("---\n");
		
		int len = 0;
		for(int i=0;str[i]!='\n';i++){
		        if(str[i]==' '){
		                printf("length = %d | ",len);
                                
                                for(int j=i-len;j!=i;j++){
                                    printf("%c",str[j]);
                                }
                                
                                if(len==n){ 
                                        printf("  <<<");
                                        count++;
                                }
                                len = 0;
                                printf("\n");
                        }
                        else{
                                len++;
                        }
		        
		} 
	        printf("---\n");
	}
	printf("Word Count(%d characters) = %d",n,count);
	printf(".\n");
	return count;
}

int main(int argc,char *argv[])
{
        char buffer[100];
        int sockfd,a,connfd,len,i=0;
        struct sockaddr_in servaddr,cliaddr;
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd==-1)
        {
                printf("Error creating socket\n");
                exit(0);
        }
        printf("Server Socket Created Successfully.\n");
        bzero((struct sockaddr *)&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(PORT);
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        {
                printf("Error in BIND function");
                exit(0);
        }
        printf("Server Socket Binded.\n");
        if((a=listen(sockfd,5))==-1)
        {
                printf("Error in LISTEN function");
                exit(0);
        }
        printf("Server Socket Listened...\n");
        len=sizeof(cliaddr);
        if((connfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len))<0)
        {
                printf("Error in ACCEPT");
                exit(0);
        }
        do
        {	
                strcpy(buffer," ");
                read(connfd,buffer,100);
                printf("From client :%s",buffer);
                if(strcmp(buffer,"bye\n")==0)
                {
                        printf("from Client: %s",buffer);
                        goto stop;
                }
                int n=0;
                printf("Server\n");
                printf("Enter n: ");
                scanf("%d",&n);
                //fgets(buffer,sizeof(buffer),stdin);
                int w = countWords(n,buffer);
                char count[5];
                sprintf(count,"%d",w);
                write(connfd,count,5);
        }while(strcmp(buffer,"bye\n") != 0);
        stop:
        exit(0);
        close(connfd);
        return 0;
}
