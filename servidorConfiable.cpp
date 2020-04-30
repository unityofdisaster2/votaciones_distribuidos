#include "Respuesta.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("%s puerto archivo\n",argv[0]);
        exit(1);
    }
    int pto = atoi(argv[1]);
    int destino;
    if((destino = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1){
        perror("error al abrir el archivo");
        exit(1);
    }

    Respuesta resp = Respuesta(7200);

    struct mensaje msj;
    int codigo = 1;
    while(true){
        msj = *resp.getRequest();
        if(msj.operationId == 1){
            write(destino, msj.arguments, 34);
            resp.sendReply((char*)&codigo);
        }
    }

    return 0;
}
