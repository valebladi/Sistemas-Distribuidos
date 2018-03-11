
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NUM 8888

int initialization();
int connection(int socket_desc);
int close(int sock);

struct Direccion{
  char calle[10];
  char ciudad[10];
  char numero[10];
};

struct Persona{
  char nombre[10];
  struct Direccion direccion;
};
