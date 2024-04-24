#include <stdio.h>
#include <math.h>


int main(){
    int n,r;
    
    
    printf("Enter the no. of bits in data (n): ");
    scanf("%d",&n);
    
    char data[n];
    
    printf("Enter the data: ");
    scanf("%s",data);
    //finding r
    r = 1;
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
    
    int codeword[n+r+1];
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

































