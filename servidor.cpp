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
        printf("forma de uso: %s puerto archivo\n",argv[0]);
        exit(1);
    }

    int destino, puerto;
    puerto = atoi(argv[1]);
    SocketDatagrama servidor = SocketDatagrama(puerto);
    PaqueteDatagrama p = PaqueteDatagrama(TAMREGISTRO);

    servidor.recibe(p);

    char buffer[TAMREGISTRO];

    memcpy(buffer, p.obtieneDatos(), sizeof(char)*34);


    if ((destino = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1){
        perror("error al abrir el archivo");
        exit(1);
    }
    int escritura;
    escritura = write(destino,buffer,TAMREGISTRO);


    close(destino);
    



    return 0;
}
