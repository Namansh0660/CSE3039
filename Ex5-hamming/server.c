#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#define PORT 4771

int codeword[100];
void Hamming(char data[]){
    int n=0;
    for(int i=0;data[i]!='\n';i++){
        n++;
    }
    printf("n=%d",n);
    int r = 1;
    while(pow(2,r)<n+r+1){
        r++;
    }
     
    printf("Number of redundant bits: %d\n",r);
    
    
    int pos[r];
    int R[r];
    for(int i=0;i<r;i++){
        R[i] = 0;
    }
    for(int i=0;i<r;i++){
        pos[i] = (int)pow(2,i);
    }
    
    for(int i=0;i<r;i++){
        printf("|%d",pos[i]);
    }
    printf("\ndata\n");
    for(int i=0;i<n;i++){
        printf("|%c",data[i]);
    }
    //int c=0;
    printf("\n");
    for(int i=0;i<n+r;i++){
        printf("|%d",n+r-i);
        
    }
    printf("\n");
    int cD=0,cP=r-1;
    
    for(int i=0;i<n+r;i++){
        int p = n+r-i;
        //printf("|%d",p);
        
        if(p==pos[cP]){
            
            printf("|r%d",cP+1); //n+r-i
            codeword[i] = 0;
            cP--;
        }
        else{
            printf("|%c",data[cD]);
            if(data[cD]=='1'){
                codeword[i] = 1;
            }
            else{
                codeword[i] = 0;
            }
            //codeword[i] = (int) data[cD];
            cD++;
        }    
    }
    
    //int R[r];
    printf("\n");
    for(int i=0;i<n+r;i++){
        printf("|%d",codeword[i]);
    }
    
    printf("\nTaking and leaving\n");
    
    
    for(int i=0;i<r;i++){
        
        int sum = 0;
        int start_index = (int)pow(2,i);
        int take = start_index;
        float iterations = (n+r)/take;
        printf("R%d\n",take);
        for(int iter=1;iter<=iterations;iter+=2){
            for(int taken=0;taken<take;taken++){
                if((start_index*iter)+taken >   n+r){
                    break;
                }
                int I = n+r - ((start_index*iter)+taken);
                printf("%d(%d) ",((start_index*iter)+taken),I);
                sum += codeword[I];
            }
        }
        printf("\nR%d=%d as sum = %d \n",take,sum%2,sum);
        codeword[n+r-start_index] = sum%2;
        
    }
    
    printf("\n\nCodeword = ");
    for(int i=0;i<n+r;i++){
        printf("| %d ",codeword[i]);
    }
    
    printf("\n");
    
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
                printf("Server :");
                Hamming(buffer);
                //fgets(buffer,sizeof(buffer),stdin);
                write(connfd,codeword,100);
        }while(strcmp(buffer,"bye\n") != 0);
        stop:
        exit(0);
        close(connfd);
        return 0;
}

