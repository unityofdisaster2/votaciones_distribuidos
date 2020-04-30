#include "Solicitud.h"
#include <string.h>
#include <stdio.h>

Solicitud::Solicitud(){
    socketLocal =  new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operId, char *arguments){
    
    struct mensaje msj;
    //memcpy(msj.arguments, arguments, sizeof(arguments));
    memcpy(msj.arguments, arguments, 34);
    msj.operationId = operId;
    msj.requestId = 0;
    msj.messageType = 0;
    PaqueteDatagrama p = PaqueteDatagrama((char *)&msj,sizeof(msj),IP,puerto);

    // se envia mensaje para que servidor procese el contenido
    socketLocal->envia(p);


    PaqueteDatagrama recibido = PaqueteDatagrama(sizeof(struct mensaje));

    // se espera la respuesta del servidor que contendra los datos procesados
    // con la funcion seleccionada (suma)
    //int rec = socketLocal->recibe(recibido);

    int num_solicitudes = 0;
    int rec = 0;

    do{
        rec = socketLocal->recibeTimeout(recibido,2,500000);
        if(rec == -1){
            num_solicitudes++;
        }
    }while(num_solicitudes < 7 && rec != 1);
    if(rec == 1){
        printf("se recibe respuesta de servidor\n");
        printf("direccion: %s\n",recibido.obtieneDireccion());
        printf("puerto: %d\n",recibido.obtienePuerto());
        struct mensaje *aux;
        aux = (struct mensaje *)recibido.obtieneDatos();
        return (char*)aux->arguments;
    }else{
        return NULL;
    }
}

