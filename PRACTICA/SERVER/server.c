
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
char c1 = 'U';
char c2 = 'U';

long i = -1;     // indicador de valor vacio

char c3 = 'U';
char c4 = 'U';

char *str2 = &c1;
int count = 1;

int main(int argc, char *argv[])
{
    int socket_desc = initialization();

    while(1) {
        int client_sock = connection(socket_desc);
        process(client_sock);
    }

    return 0;
}

void process(int client_sock)
{
    int read_size;
    char client_message[2000];

    // receive a message from client
    while((read_size = recv(client_sock,
                            client_message, 2000, 0)) > 0)
    {
      // send the message back to client
      write( client_sock,
             client_message, strlen(client_message) );
       // receive a reply from the server
       puts("Server reply:");
       puts(client_message);

       char *str = client_message;

       if (count == 2){
         *str2 = str[1];
         str2--;
         *str2 = str[0];
         str2--;
         for(int j=0; j<= 5; j++) {
             *str2 = 0;
             str2--;
         }
        str2+=9;
       }
       else{
         *str2 = str[0];
         str2++;
         *str2 = str[1];
         if (count == 1 ){
           str2 +=14;
         }
       }
       count++;

       // espia de memoria
       char *p2 = &c1;
       for(int j=0; j<18; j++){
           printf("Dato %d:  %d\n", j, p2[j] );
       }

    }

    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
}
