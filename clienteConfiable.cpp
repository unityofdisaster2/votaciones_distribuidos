#include "Solicitud.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define TAMREGISTRO 34

int main(int argc, char const *argv[])
{
    if(argc < 4){
        printf("modo uso: %s ip puerto archivo n_registros\n",argv[0]);
        exit(1);
    }

    char * ip = (char*)argv[1];
    int pto = atoi(argv[2]);
    int n_registros = atoi(argv[4]);
    int origen;
    if((origen = open(argv[3], O_RDONLY)) == -1){
        perror("error al abrir archivo\n");
        exit(1);
    }

    Solicitud sol = Solicitud();
    int acuse;
    char registro[TAMREGISTRO];
    int offset = TAMREGISTRO;
    for(int i = 0; i < n_registros; i++){
        read(origen,registro,TAMREGISTRO);
        memcpy(&acuse, sol.doOperation(ip, pto, 1, (char*)&registro), sizeof(int));
        if(acuse == 1){
            printf("servidor ha guardado registro\n");
        }
    }

    close(origen);
    
    return 0;
}