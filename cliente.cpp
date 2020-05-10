#include "SocketDatagrama.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TAMREGISTRO 34


int main(int argc, char const *argv[])
{
    if(argc < 3){
        printf("forma de uso: %s ip_servidor puerto archivo\n",argv[0]);
        exit(1);
    }

    int origen, puerto;
    char * ip = (char*)argv[1];
    puerto = atoi(argv[2]);
    SocketDatagrama cliente = SocketDatagrama(0);
    if ((origen = open(argv[3], O_RDONLY)) == -1){
        perror("error al abrir el archivo");
        exit(1);
    }
    char buffer[34];
    int lectura;
    while( (lectura = read(origen,buffer, BUFSIZ)) != 0);

    PaqueteDatagrama p = PaqueteDatagrama((char*)&buffer,sizeof(buffer),ip,puerto);

    cliente.envia(p);
    printf("registro enviado al servidor\n");

    close(origen);



    return 0;
}
