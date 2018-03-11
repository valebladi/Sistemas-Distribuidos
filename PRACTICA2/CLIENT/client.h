
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NUM 8888

int connection();
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
