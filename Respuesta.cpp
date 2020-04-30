#include "Respuesta.h"
#include <string.h>
#include <stdio.h>

// dado que el paquete cuenta con la direccion y el puerto del cliente
// sera necesario crear un paquete global para que persista en todo el proceso de
// reception, procesamiento y envio de respuesta
PaqueteDatagrama bid = PaqueteDatagrama(sizeof(struct mensaje));


Respuesta::Respuesta(int pl){
    socketLocal = new SocketDatagrama(pl);
}

struct mensaje * Respuesta::getRequest(){
    // esta funcion solo se encarga de recibir 
    // el mensaje y retornarlo para ser manipulado por
    // el servidor

    socketLocal->recibe(bid);

    printf("Solicitud recibida de:\n");
    printf("direccion: %s\n",bid.obtieneDireccion());
    printf("puerto: %d\n",bid.obtienePuerto());
    // struct mensaje msj;
    // memcpy(&msj, bid.obtieneDatos(),sizeof(struct mensaje));
    // printf("%s\n", msj.arguments);

    return (struct mensaje*) bid.obtieneDatos();
}


void Respuesta::sendReply(char *respuesta){
    struct mensaje resultado;
    memcpy(resultado.arguments, respuesta,sizeof(int));
    resultado.operationId = 0;
    resultado.requestId = 0;
    resultado.messageType = 1;

    bid.inicializaDatos((char*)&resultado);

    socketLocal->envia(bid);

}