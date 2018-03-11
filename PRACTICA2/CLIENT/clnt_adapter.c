#include "client.h"

//nosotros decidimos mandar puros strings,
// ya que es más facil mandar solo string que integers, long, short, etc.

extern int sock;
char * all;
int lengthNombre, lengthCalle, lengthCiudad, lengthNumero, lengthAll;
void recive_struct(int socket);
struct Persona p1;

int store( char * nombre, char * calle, char * ciudad, char * numero )
{

  lengthNombre = strlen(nombre);              //Length de nombre
  lengthCalle = strlen(calle);                //Length de calle
  lengthCiudad = strlen(ciudad);              //Length de ciudad
  lengthNumero = strlen(numero);              //Lenght numero
  lengthAll = (lengthNombre + lengthCalle + lengthCiudad + lengthNumero);    //tamaño de caracteres que componen toda la persona

  //se guardan todas las strings que componen a la persona en 1 sola string para poder reservar la memoria
  all = (char * ) malloc(lengthAll);

  //concatenamos las cadenas
  snprintf( all, lengthAll+1, "%s%s%s%s", nombre, calle, ciudad, numero );
  printf("%s\n", all );

  //manda los datos de la persona
  send(sock,&lengthNombre,sizeof(lengthNombre),0);
  send(sock,&lengthCalle,sizeof(lengthCalle),0);
  send(sock,&lengthCiudad,sizeof(lengthCiudad),0);
  send(sock,&lengthNumero,sizeof(lengthNumero),0);

  //en el caso de que no se mande bien el mensaje aparecera un error
    if(send(sock,all,lengthAll,0) < 0)
    {
        puts("Send fieled");
        exit(1);
    }

    //llamamos a la respuesta de la estructura del objeto desde el servidor
    recive_struct(sock);
    return lengthAll;
}

struct Persona creaPersona(char * nombre, char * calle, char * ciudad, char * numero )
{
  struct Persona persona;
  strcpy(persona.nombre, nombre);
  strcpy(persona.direccion.calle, calle);
  strcpy(persona.direccion.ciudad, ciudad);
  strcpy(persona.direccion.numero, numero);

  printf("------------------Persona Creada Exitosamente lado CLIENTE------------------\n");
  return persona;
}

void recive_struct(int socket)
{
  int lengthCadena, dir, lengthAllStruct, lenNombre, lenCalle, lenCiudad, lenNumero;
	char * allStruct;
  char * nombre; char * calle; char * ciudad; char * numero ;

	//recibe la info de la estructura mandada al final
	recv(socket, &lengthAllStruct, sizeof(lengthAllStruct), 0);
  recv(socket,&(lenNombre),sizeof(lenNombre),0);
  recv(socket,&(lenCalle),sizeof(lenCalle),0);
  recv(socket,&(lenCiudad),sizeof(lenCiudad),0);
  recv(socket,&(lenNumero),sizeof(lenNumero),0);

  //numero de byte en memoria en donde se guardo la cadena
	recv(socket, &dir, sizeof(dir), 0);

	//Allocate memory
	allStruct = (char *) malloc(lengthAllStruct);
	recv(socket,allStruct,lengthCadena,0);

  printf("------------Prarametros de Estructura Mandada por Servidor------------------\n\n");
	printf("Tamaño estructura: %d\n",lengthAllStruct);
  printf("Tamaño nombre: %d\n",lenNombre);
  printf("Tamaño calle: %d\n",lenCalle);
  printf("Tamaño ciudad: %d\n",lenCiudad);
  printf("Tamaño numero: %d\n",lenNumero);
	printf("Estructura mandada:%s\n",allStruct);
  printf("----------------------------------------------------------------------------\n\n");

  nombre = (char *) malloc(lenNombre);
  calle = (char *) malloc(lenCalle);
  ciudad = (char *) malloc(lenCiudad);
  numero = (char *) malloc(lenNumero);
  //all = (char *) malloc(lengthAll);

	//se creo un objeto persona arriba global, para asignarle todos los valores de la estrcutura mandada
	//struct Persona p1;

  //aca se sacan los caracteres de la memoria

  //esta parte es de la parte del servidor, es para ller lor caracteres mandados
  //y poderlos pasar a forma de objeto de una persona, es el mismo porceso que se encuentra en svc.adapter
  //

  int start = 0;
  int end = lenNombre;

  for(int i = start; i < end; i++)
  {
      nombre[i] = allStruct[i];
  }

  start = end;
  end = start + lenCalle;
  for(int i = start; i < end; i++)
  {
    calle[i-start] = all[i];
  }

  start = end;
  end = start + lenCiudad;
  for(int i = start; i < end; i++)
  {
    ciudad[i-start] = all[i];
  }

  start = end;
  end = start + lenNumero;
  for(int i = start; i < end; i++)
  {
    numero[i-start] = all[i];
  }
  strcpy(p1.nombre, nombre);
  strcpy(p1.direccion.calle, calle);
  strcpy(p1.direccion.ciudad, ciudad);
  strcpy(p1.direccion.numero, numero);

  printf("--------------Caracteres recuperados desde memoria con los tamaños----------\n");
	printf("Nombre: %s\n",p1.nombre);
	printf("Calle: %s\n",p1.direccion.calle);
	printf("Ciudad: %s\n",p1.direccion.ciudad);
	printf("Numero: %s\n",p1.direccion.numero);
  printf("----------------------------------------------------------------------------\n\n");

}
