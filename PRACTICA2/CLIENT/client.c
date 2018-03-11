
// store messages using a service

#include "client.h"

int sock;                       // server socket
char * host;                    // server name
char * nombre;
char * calle;
char * ciudad;
char * numero;

int store( char * nombre, char * calle, char * ciudad, char * numero );
struct Persona creaPersona( char * nombre, char * calle, char * ciudad, char * numero );
// Persona recieve_reply(int socket);

int main( int argc, char * argv[] )
{

    if( argc != 6 ) {
        fprintf( stderr, "Uso: %s <host> <nombre> <calle> <ciudad> <numero> \n", argv[0] );
        exit( 1 );
    }

    host = argv[1];
    nombre = argv[2];
    calle = argv[3];
    ciudad = argv[4];
    numero = argv[5];

    sock = connection();

    //se creo la persona y regresa que fue exitosa la creacion
    struct Persona p1 = creaPersona(nombre, calle, ciudad, numero);
    printf("Nombre de la persona: %s\n",p1.nombre);
    printf("Calle de la persona: %s\n",p1.direccion.calle);
    printf("Ciudad de la persona: %s\n",p1.direccion.ciudad);
    printf("Numero de la persona: %s\n",p1.direccion.numero);
    printf("----------------------------------------------------------------------------\n\n");

    //se guarda la info en memoria y regresa el length de los caracteres de toda la estructura
    int result = store(nombre, calle, ciudad, numero);      // as if it were a local call!
    printf("Tamaño de estructura: %d\n", result);

    //si todo fue exitoso se muestra el siguiente mensaje
    printf( "El mensaje fue almacenado\n" );
    close(sock);
    return 1;
}
