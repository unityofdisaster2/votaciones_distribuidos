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
#include "TrieUtil.h"

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
    //vector<string> vec_celulares;

    struct TrieNode *root = getNode();

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
            
            string auxString(reg_individual.celular);
            // se verifica que el numero de celular no este repetido
            if(!search(root, auxString)){
                strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", newtime);

                write(destino, msj.arguments, 34);
                write(destino,time_string,20);
                fsync(destino);
                // se inserta el numero telefonico en el arbol
                insert(root,auxString);
            }else{
                printf("numero repetido\n");
                tiempo.tv_sec = 0;
                tiempo.tv_usec = 0;
            }
            resp.sendReply((char*)&tiempo, sizeof(tiempo));
            
        }
    }

    return 0;
}
