#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int i_ip[4];
char ip[4][9] = {"00000000\0","00000000\0","00000000\0","00000000\0"};
char mask[4][9] = {"00000000\0","00000000\0","00000000\0","00000000\0"};
char FA[4][9] = {"00000000\0","00000000\0","00000000\0","00000000\0"};
char LA[4][9] = {"11111111\0","11111111\0","11111111\0","11111111\0"};
int ip_c = 0;
int i_ip_c = 0;
int maskNum;

void calcCIDR(int maskNum){
    int c = 0;
    int b = 0;
    for(int i=0;i<maskNum;i++){
        if(b==8){
            b = 0;
            c++;
        }
        mask[c][b] = '1';
        FA[c][b] = ip[c][b];
        LA[c][b] = ip[c][b];
        b++;
    }
    printf("Subnet(Binary) = %s.%s.%s.%s\n",mask[0],mask[1],mask[2],mask[3]);
    printf("FA(Binary) = %s.%s.%s.%s\n",FA[0],FA[1],FA[2],FA[3]);
    printf("LA(Binary) = %s.%s.%s.%s\n\n",LA[0],LA[1],LA[2],LA[3]);
    
    
    printf("Mask = %d.%d.%d.%d\n",binaryToDecimal(mask[0]),binaryToDecimal(mask[1]),binaryToDecimal(mask[2]),binaryToDecimal(mask[3]));
    printf("FA = %d.%d.%d.%d\n",binaryToDecimal(FA[0]),binaryToDecimal(FA[1]),binaryToDecimal(FA[2]),binaryToDecimal(FA[3]));
    printf("LA = %d.%d.%d.%d\n",binaryToDecimal(LA[0]),binaryToDecimal(LA[1]),binaryToDecimal(LA[2]),binaryToDecimal(LA[3]));
    
    printf("Number of Hosts: %ld",(long)pow(2,(32-maskNum)));
}

void decimalToBinary(int decimalNum) {
    int binaryNum[8];
    int i = 0;

    while (decimalNum > 0) {
        binaryNum[i] = decimalNum % 2;
        decimalNum = decimalNum / 2;
        i++;
    }

    // Pad with leading zeros if necessary
    while (i < 8) {
        binaryNum[i] = 0;
        i++;
    }

    for (int j = 7; j >= 0; j--) {
        printf("%d", binaryNum[j]);
        if(binaryNum[j]==1){
            
            ip[ip_c][7-j] = '1';
        }
        else{
            ip[ip_c][7-j] = '0';
        }
    }
    ip_c++;
}

int binaryToDecimal(char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    int base = 1; // Initializing base value to 1 (2^0)

    for (int i = length - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2; // Incrementing base for the next position
    }

    return decimal;
}
int main()
{
    char ip_address[16]; 
    char *token;
    
    printf("Enter an IP address: ");
    scanf("%15s", ip_address);
    token = strtok(ip_address, ".");
            
            while (token != NULL) {
                int digit = atoi(token);
                i_ip[i_ip_c]=digit;
                i_ip_c++;
                printf("\n%d\n", digit);
                
                decimalToBinary(digit);
                
                token = strtok(NULL, ".");
            }
            
            printf("\nBinary IP= %s.%s.%s.%s\n",ip[0],ip[1],ip[2],ip[3]);
    int choice;
    printf("\n1.Classfull\n2.Classless\n3.Exit\n>>Enter your choice: ");
    scanf("%d",&choice);
    
    switch(choice){
    
        case 1 :
            char Class;
            
            if(i_ip[0]>=1 && i_ip[0]<= 127){
                Class='A';
                printf("Class %c\n",Class);
                printf("ip=%d.%d.%d.%d/%d\n",i_ip[0],i_ip[1],i_ip[2],i_ip[3],8);
                maskNum = 8;
                calcCIDR(maskNum);
            }
            else if(i_ip[0]<=191){
                Class='B';
                printf("Class %c\n",Class);
                printf("ip=%d.%d.%d.%d/%d\n",i_ip[0],i_ip[1],i_ip[2],i_ip[3],16);
                maskNum = 16;
                calcCIDR(maskNum);
            }
            else if(i_ip[0]<=223){
                Class='C';
                printf("Class %c\n",Class);
                printf("ip=%d.%d.%d.%d/%d\n",i_ip[0],i_ip[1],i_ip[2],i_ip[3],24);
                maskNum = 24;
                calcCIDR(maskNum);
            }
            else if(i_ip[0]<=239){
                Class='D';
                printf("Class %c",Class);
            }
            else{
                Class='E';
                printf("Class %c",Class);
            }
            break;
        
        case 2 : 
            printf("Enter mask number: ");
            scanf("%d",&maskNum);
            //First and Last address(and opt)(simply copy maskNum bits from IP and add zero)
            
            calcCIDR(maskNum);
            
        
        case 3 : exit(0);
    }
    
    return 0;

}
