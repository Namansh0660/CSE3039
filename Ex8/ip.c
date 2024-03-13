#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void decimalToBinary(int decimalNum) 
{
    int binaryNum[32];
    int i = 0;

    while (decimalNum > 0) {
        binaryNum[i] = decimalNum % 2;
        decimalNum = decimalNum / 2;
        i++;
    }

    printf("\n-\n");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binaryNum[j]);
    }
}


int main()
{
    char ip_address[16]; // Assuming IPv4 address with maximum length of 15 characters
    char *token;
    
    printf("Enter an IP address: ");
    scanf("%15s", ip_address);
    
    // Split the IP address into individual strings
    token = strtok(ip_address, ".");
    
    // Iterate through each string and convert it to an integer
    while (token != NULL) {
        int digit = atoi(token);
        printf("%d\n", digit);
        
        // Get the next token
        token = strtok(NULL, ".");
        
        //binary to decimal
        decimalToBinary(*token);
    }
    
    return 0;
}
