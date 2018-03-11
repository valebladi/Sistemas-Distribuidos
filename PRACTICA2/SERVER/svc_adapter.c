
#include "server.h"

char * nombre;
char * calle;
char * ciudad;
char * numero;
char * numero;
int lengthNombre, lengthCalle, lengthCiudad, lengthNumero, lengthAll;

char * all;
struct Persona p1;

struct Persona store( char * nombre, char * calle, char * ciudad, char * numero );
void recv_message(int client_sock);
void send_struct(int client_sock, struct Persona p1);
void getChars();

int main(int argc, char *argv[])
{
    int socket_desc = initialization();

    // infinite loop
    while(1) {
        int client_sock = connection(socket_desc);

        recv_message(client_sock);

        free(nombre);
        free(calle);
        free(ciudad);
        free(numero);
        send_struct(client_sock, p1);
    }

    close(socket_desc);
    return 0;
}


void recv_message(int client_sock)
{
    // receive the message length from client
  	recv(client_sock, &lengthNombre, sizeof(lengthNombre), 0);
  	recv(client_sock, &lengthCalle, sizeof(lengthCalle), 0);
  	recv(client_sock, &lengthCiudad, sizeof(lengthCiudad), 0);
    recv(client_sock, &lengthNumero, sizeof(lengthNumero), 0);

  	lengthAll = (lengthNombre + lengthCalle + lengthCiudad + lengthNumero);

    printf("--------------Tamaño de los prametros enviados desd el CLIENTE--------------\n");
  	printf("Nombre: %d \n",lengthNombre);
  	printf("Calle: %d \n",lengthCalle);
    printf("Ciudad: %d \n",lengthCiudad);
    printf("Numero: %d \n",lengthNumero);
    printf("----------------------------------------------------------------------------\n\n");

    // dynamic memory allocation to store the message
  	nombre = (char *) malloc(lengthNombre);
  	calle = (char *) malloc(lengthCalle);
  	ciudad = (char *) malloc(lengthCiudad);
    numero = (char *) malloc(lengthNumero);
  	all = (char *) malloc(lengthAll);
  	recv(client_sock, all, lengthAll,0);

    //llamamos a getChars que obtiene los characteres de la memoria
    getChars();
}

void getChars()
{
  //aca se sacan los caracteres de la memoria
      int start = 0;
      int end = lengthNombre;
      for(int i = start; i < end; i++)
      {
        nombre[i] = all[i];
      }

      start = end;
      end = start + lengthCalle;
      for(int i = start; i < end; i++)
      {
        calle[i-start] = all[i];
      }

      start = end;
      end = start + lengthCiudad;
      for(int i = start; i < end; i++)
      {
        ciudad[i-start] = all[i];
      }

      start = end;
      end = start + lengthNumero;
      for(int i = start; i < end; i++)
      {
        numero[i-start] = all[i];
      }

      printf("--------------Caracteres recuperados desde memoria con los tamaños----------\n");
    	printf("Nombre: %s\n",nombre);
    	printf("Calle: %s\n",calle);
    	printf("Ciudad: %s\n",ciudad);
    	printf("Numero: %s\n",numero);
      printf("----------------------------------------------------------------------------\n\n");


      p1 = store(nombre, calle, ciudad, numero);
}


struct Persona creaPersona(char * nombre, char * calle, char * ciudad, char * numero )
{
  struct Persona persona;
  strcpy(persona.nombre, nombre);
  strcpy(persona.direccion.calle, calle);
  strcpy(persona.direccion.ciudad, ciudad);
  strcpy(persona.direccion.numero, numero);

  printf("-------------------Persona Creada Exitosamente lado SERVIDOR----------------\n");
  return persona;
}



void send_struct(int client_sock, struct Persona p1)
{
  int lengthAllStruct, lenNombre, lenCalle, lenCiudad, lenNumero;
  //la estructura se tiene que mandar por lo cual es necesario generar espacio en la memoria
	char * allStruct = (char *) malloc(lengthAll);

  //tenemos que poner todos los caracteres de la estructura en una variable para mandarla
  lengthAllStruct = sprintf( allStruct,"%s%s%s%s",p1.nombre, p1.direccion.calle,
          p1.direccion.ciudad, p1.direccion.numero);

  lenNombre = strlen(p1.nombre);
  lenCalle = strlen(p1.direccion.calle);
  lenCiudad = strlen(p1.direccion.ciudad);
  lenNumero= strlen(p1.direccion.numero);

	//manda la longitud cadena, estructura y cadena de texto
	send(client_sock,&(lengthAllStruct),sizeof(lengthAllStruct),0);
  send(client_sock,&(lenNombre),sizeof(lenNombre),0);
  send(client_sock,&(lenCalle),sizeof(lenCalle),0);
  send(client_sock,&(lenCiudad),sizeof(lenCiudad),0);
  send(client_sock,&(lenNumero),sizeof(lenNumero),0);

	send(client_sock,allStruct,lengthAllStruct,0);

  printf("----------Se manda la estructura de persona como respuesta------------------\n\n");
  printf("Tamaño estructura: %i\n", lengthAllStruct);
  printf("Estructura a Mandar: %s\n", allStruct);
  printf("----------------------------------------------------------------------------\n\n");


}
