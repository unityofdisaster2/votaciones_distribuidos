#include "Respuesta.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;





int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("%s puerto \n",argv[0]);
        exit(1);
    }
    int pto = atoi(argv[1]);
    int destino;
    struct timeval tiempo;
    //vector<string> vec_celulares;

    struct tm *newtime;
    char time_string[40];
    char *tiempo_final;
    Respuesta resp = Respuesta(pto);
    
    struct mensaje msj;
    string cadena;
    char aux[15];
    while(true){
        memcpy(&msj, resp.getRequest(), sizeof(mensaje));
        // newtime = localtime(&tiempo.tv_sec);

        if(msj.operationId == 2){
            gettimeofday(&tiempo,NULL);

            // strftime (time_string, sizeof (time_string),"%H:%M:%S", newtime);
            // cadena = string(time_string) + "." + to_string(tiempo.tv_usec);
            
            // memcpy(aux, cadena.c_str(), 15);
            resp.sendReply((char*)&tiempo, sizeof(tiempo));
            
        }
    }

    return 0;
}
