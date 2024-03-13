#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//void decimalToBinary(int decimalNum) 
//{
//    int binaryNum[32];
//    int i = 0;
//
//    while (decimalNum > 0) {
//        binaryNum[i] = decimalNum % 2;
//        decimalNum = decimalNum / 2;
//        i++;
//    }
//    for (int j = i - 1; j >= 0; j--) {
//        printf("%d", binaryNum[j]);
//    }
//    printf("\n");
//}
//

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
    }
}

int main()
{
    char ip_address[16]; 
    char *token;
    
    printf("Enter an IP address: ");
    scanf("%15s", ip_address);
    
    int choice;
    printf("1\t-\tClassfull\n2\t-\tClassless\n3\t-\tExit\nEnter your choice : ");
    scanf("%d",&choice);
    
    switch(choice){
    
        case 1 :
        
            token = strtok(ip_address, ".");
            
            while (token != NULL) {
                int digit = atoi(token);
                printf("\n%d\n", digit);
                
                decimalToBinary(digit);
                
                token = strtok(NULL, ".");
            }
            break;
        
        
        case 2 : 
            printf("Working on it\n");
            break;
            
        
        case 3 : exit(0);
    }
    
    return 0;

}
