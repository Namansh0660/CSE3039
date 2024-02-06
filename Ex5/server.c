#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void calculateCRC(char data[], char divisor[], char crc[]) {
    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);

    // Append zeros to the data
    for (int i = 0; i < divisorLen - 1; i++) {
        data[dataLen + i] = '0';
    }

    // Perform division
    for (int i = 0; i < dataLen; i++) {
        if (data[i] == '1') {
            for (int j = 0; j < divisorLen; j++) {
                data[i + j] = (data[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Copy the remainder (CRC) to the crc array
    strncpy(crc, &data[dataLen], divisorLen - 1);
    crc[divisorLen - 1] = '\0';
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char data[100];
    char divisor[100];
    char crc[100];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Socket binding failed\n");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        printf("Listening failed\n");
        return -1;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        printf("Acceptance failed\n");
        return -1;
    }

    read(new_socket, buffer, 1024);

    sscanf(buffer, "%s\n%s", data, divisor);

    calculateCRC(data, divisor, crc);

    printf("Calculated CRC is: %s\n", crc);

    close(new_socket);
    close(server_fd);

    return 0;
}

