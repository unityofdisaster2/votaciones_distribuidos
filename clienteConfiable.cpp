#include "Solicitud.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <thread>
#define TAMREGISTRO 34

using namespace std;

struct str_registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};


void enviar(const char* ip, int puerto, struct str_registro reg, Solicitud solicitud){
    struct timeval acuse;
    memcpy(&acuse, solicitud.doOperation((char*)ip, puerto, 1, (char*)&reg), sizeof(acuse));
    if(acuse.tv_sec == 0 && acuse.tv_sec == 0){
        printf("ya se ha enviado un voto desde este numero\n");
    }else{
        printf("se ha registrado el voto\n");
    }
}


int main(int argc, char const *argv[])
{
    if(argc < 8){
        printf("modo uso: %s ipA puertoA ipB puertoB ipC puertoC archivo n_registros\n",argv[0]);
        exit(1);
    }

    //char * ip = (char*)argv[1];
    //int pto = atoi(argv[2]);
    int n_registros = atoi(argv[8]);
    int origen;
    struct timeval acuse;
    // int acuse;
    if((origen = open(argv[7], O_RDONLY)) == -1){
        perror("error al abrir archivo\n");
        exit(1);
    }

    
    Solicitud sol = Solicitud();
    char registro[TAMREGISTRO];
    struct str_registro reg_aux; 
    for(int i = 0; i < n_registros; i++){
        read(origen,registro,TAMREGISTRO);
        memcpy(&reg_aux,registro,sizeof(registro));
        if(reg_aux.celular[9] == '0' || reg_aux.celular[9] == '1' || reg_aux.celular[9] == '2' || reg_aux.celular[9] == '3'){
            thread t(enviar,argv[1],atoi(argv[2]), reg_aux, sol);
            t.detach();
        }else if(reg_aux.celular[9] == '4' || reg_aux.celular[9] == '5' || reg_aux.celular[9] == '6'){
            thread t(enviar,argv[3],atoi(argv[4]), reg_aux, sol);
            t.detach();
        }else if(reg_aux.celular[9] == '7' || reg_aux.celular[9] == '8' || reg_aux.celular[9] == '9'){
            thread t(enviar,argv[5],atoi(argv[6]), reg_aux, sol);
            t.detach();            
        }
        usleep(1000);

    }

    close(origen);
    
    return 0;
}
