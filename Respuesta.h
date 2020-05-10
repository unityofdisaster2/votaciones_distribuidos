#ifndef RESPUESTA_H_
#define RESPUESTA_H_
#include "SocketDatagrama.h"
#include "mensaje.h"
class Respuesta{
    public:
        Respuesta(int pl);
        struct mensaje *getRequest(void);
        void sendReply(char *respuesta, unsigned int);
    private:
        SocketDatagrama *socketLocal;
};

#endif