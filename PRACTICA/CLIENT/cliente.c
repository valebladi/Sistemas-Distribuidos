
#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc , char *argv[])
{
    int sock = connection();
    message(sock);      // communicating with server

    close(sock);
    return 0;
}

void message(int sock)
{
    char message[1000];
    char server_reply[2000];

    while(1) {
        printf("Enter message: ");
        scanf("%s", message);

        // send some data
        if( send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            exit(1);
        }

        // receive a reply from the server
        if( recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }

        puts("Server reply:");
        puts("recieved");


    }
}
