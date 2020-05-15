#include "Respuesta.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
#include "TrieUtil.h"
#include "Solicitud.h"

using namespace std;
struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};





int main(int argc, char const *argv[])
{
    if(argc < 4){
        printf("%s puertoLocal archivo ipTiempo puertoTiempo\n",argv[0]);
        exit(1);
    }
    int pto = atoi(argv[1]);
    int destino;

    struct TrieNode *root = getNode();

    struct registro reg_individual;

    if((destino = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1){
        perror("error al abrir el archivo");
        exit(1);
    }

    Respuesta resp = Respuesta(pto);
    Solicitud sol = Solicitud();
    struct mensaje msj;
    int codigo = 1;
    int index;
    struct timeval tiempo;
    char timestamp[15];
    char time_string[40];
    char separador[1];
    struct tm *newTime;
    string cadena;
    // separador binario
    separador[0] = '\0';
    while(true){
        msj = *resp.getRequest();


        if(msj.operationId == 1){
            // se guarda el registro recibido en una estructura
            memcpy(&reg_individual,msj.arguments,34);
            //printf("%s\n",reg_individual.celular);
            
            string auxString(reg_individual.celular);
            // se verifica que el numero de celular no este repetido
            if(!search(root, auxString)){

                write(destino, msj.arguments, 34);
                //write(destino,time_string,20);
                
                // se inserta el numero telefonico en el arbol
                memcpy(&tiempo, sol.doOperation((char*)argv[3],atoi(argv[4]),2,(char*)&codigo,sizeof(int)), sizeof(tiempo));
                
                //formateo de timestamp
                strftime (time_string, sizeof (time_string),"%H:%M:%S", newTime);
                cadena = string(time_string) + "." + to_string(tiempo.tv_usec); 
                memcpy(timestamp, cadena.c_str(), 15);

                write(destino, timestamp, sizeof(timestamp));
                
                write(destino, separador, sizeof(separador));
                fsync(destino);
                
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
