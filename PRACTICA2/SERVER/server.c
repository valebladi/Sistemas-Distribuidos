
/* servidor.c: Código para el servidor */

#include "server.h"


struct Persona creaPersona( char * nombre, char * calle, char * ciudad, char * numero );

// Agrega un nuevo mensaje al archivo
struct Persona store( char * nombre, char * calle, char * ciudad, char * numero )
{
    FILE * fp = fopen( "mensajes.txt", "a" );

    fprintf( fp, "%s\n", nombre );
    fprintf( fp, "%s\n", calle );
    fprintf( fp, "%s\n", ciudad );
    fprintf( fp, "%s\n", numero );
    fclose( fp );

    int suma = strlen(nombre)+strlen(calle)+strlen(ciudad)+strlen(numero);

    //se creo la persona y regresa que fue exitosa la creacion
    struct Persona p1 = creaPersona(nombre, calle, ciudad, numero);
    printf("Nombre de la persona: %s\n",p1.nombre);
    printf("Calle de la persona: %s\n",p1.direccion.calle);
    printf("Ciudad de la persona: %s\n",p1.direccion.ciudad);
    printf("Numero de la persona: %s\n",p1.direccion.numero);
    printf("----------------------------------------------------------------------------\n\n");

    return p1;
}
