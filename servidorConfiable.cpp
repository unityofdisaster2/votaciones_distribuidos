#include "Respuesta.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <string.h>
#include <string>
//#include<bits/stdc++.h>
#include <algorithm>


using namespace std;
struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};





int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("%s puerto archivo\n",argv[0]);
        exit(1);
    }
    int pto = atoi(argv[1]);
    int destino;
    struct timeval tiempo;
    vector<string> vec_celulares;
    struct tm *newtime;
    struct registro reg_individual;
    char time_string[40];

    if((destino = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1){
        perror("error al abrir el archivo");
        exit(1);
    }

    Respuesta resp = Respuesta(7200);
    
    struct mensaje msj;
    int codigo = 1;
    int index;
    while(true){
        msj = *resp.getRequest();
        gettimeofday(&tiempo,NULL);
        newtime = localtime(&tiempo.tv_sec);

        if(msj.operationId == 1){
            // se guarda el registro recibido en una estructura
            memcpy(&reg_individual,msj.arguments,34);
            //printf("%s\n",reg_individual.celular);
            // se verifica que el numero de celular no este repetido
            if(!binary_search(vec_celulares.begin(),vec_celulares.end(), reg_individual.celular)){
                strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", newtime);
                //printf("%s\n",time_string);
                vec_celulares.push_back(reg_individual.celular);
                write(destino, msj.arguments, 34);
                write(destino,time_string,20);
                fsync(destino);
                // se ordena el vector de numeros celulares para mantener la consistencia en la 
                // busqueda binaria
                sort(vec_celulares.begin(), vec_celulares.end());
            }else{
                //printf("numero repetido\n");
                tiempo.tv_sec = 0;
                tiempo.tv_usec = 0;
            }
            printf("%ld %ld\n",tiempo.tv_sec, tiempo.tv_usec);
            resp.sendReply((char*)&codigo, sizeof(codigo));
            
        }
    }

    return 0;
}
