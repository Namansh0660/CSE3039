#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
int main(){
    int n = 7;
    char data[100] = "1001110";
    /*printf("Enter the no of bits in data (n) : ");
    scanf("%d",&n);
    printf("Enter the data : ");
    scanf("%s",data);
    */
    int r = 1;
    while(pow(2,r)<=n+r+1)
    {
        r++;
    }
    
    int pos[r];
    for(int i = 0 ; i<r ; i++){
        pos[i]=(int)pow(2,i);
    }
    int l = n+r;
    int cd[l];
    for(int i=0;i<l;i++)
    {
        for(int j=0;j<r;j++)
        {
            if(i == (int)pow(2,j))
            {
                cd[j] = cd[i++];
            }
        }
    }
    
    
    for(int i = n+r ; i > 0 ; i--){
        printf("|%d",i);
    }
    
    printf("\n");
    
    
    for(int i = 0 ; i < r ; i++){
        if((int)pow(2,i)> 0 ){
            printf("|%d",(int)pow(2,i));
        }
    }
    
    
    printf("\nBits : %d\nData : %s\nRedundant bits :%d\n",n,data,r);
}
