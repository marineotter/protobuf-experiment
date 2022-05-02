#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "sample.pb.h"

int main(void) {
    char buf_name[60] = {0};
    char buf_email[60] = {0};
    int buf_age = 0;
    for (;;) {
        
        printf("name: \n>");
        scanf("%s", buf_name);

        printf("email: \n>");
        scanf("%s", buf_email);

        printf("age: \n>");
        scanf("%d", &buf_age);

        com_test_Person message = com_test_Person_init_default;
        strncpy(message.name, buf_name, strlen(buf_name));
        strncpy(message.email, buf_email, strlen(buf_email));
        message.id = buf_age;

        uint8_t message_buffer[128] = {0};
        size_t message_length;
        pb_ostream_t stream = pb_ostream_from_buffer(message_buffer, sizeof(message_buffer));
        pb_encode(&stream, com_test_Person_fields, &message);
        message_length = stream.bytes_written;

        WSADATA data;
        WSAStartup(MAKEWORD(2, 0), &data);
        struct sockaddr_in dstAddr;
        memset(&dstAddr, 0, sizeof(dstAddr));
        dstAddr.sin_port = htons(8080);
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        int dstSocket;
        dstSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (dstSocket < 0){
            printf("Failed to create socker...\n");
            return 1;
        }
        if (connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr))) {
            printf("Failed to connect socker...\n");
            return 1;
        }
        send(dstSocket, message_buffer, message_length, 0);
        printf("Send completed.\n");
        closesocket(dstSocket);
        WSACleanup();
    }
}
