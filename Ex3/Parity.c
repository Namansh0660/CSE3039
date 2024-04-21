#include <stdio.h>
#include <string.h>

int main(){
    int n,b,opt;
    
    printf("Enter no. of messages = ");
    scanf("%d",&n);
    printf("Enter the size of messages(bits) = ");
    scanf("%d",&b);
    
    char msg[n][b+10];
    
    for(int i=0;i<n;i++){
        printf("Enter msg %d: ",i+1);
        scanf("%s",msg[i]);
    }
    
    printf("Enter option(even=0/odd=1)= ");
    scanf("%d",&opt);
    
    //printf("\n%s\n%s\n%s\n",msg[0],msg[1],msg[2]);
    for(int i=0; i<n; i++){
        printf("%s\n",msg[i]);
    }
    
    for(int i=0; i<n; i++){
        int r_count = 0;
        for(int j=0; j<b+1 ; j++){
            if(msg[i][j]=='1'){
                r_count ++;
            }
        }
        printf("rcount = %d\n",r_count);
        
        if(r_count%2 == opt){
            strcat(msg[i],"0");
            
        }
        else{
            strcat(msg[i],"1");
        }
    }
    for(int i=0; i<n; i++){
        printf("%s\n",msg[i]);
    }
}
