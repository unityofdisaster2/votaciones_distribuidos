#ifndef SOLICITUD_H_
#define SOLICITUD_H_
#include "SocketDatagrama.h"
#include "mensaje.h"
#include "PaqueteDatagrama.h"
class Solicitud{
    public:
        Solicitud();
        char * doOperation(char *IP, int puerto, int operationId, char *arguments);
    private:
        SocketDatagrama *socketLocal;
};

#endif