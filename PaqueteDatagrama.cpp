#include "PaqueteDatagrama.h"
#include <string.h>
PaqueteDatagrama::PaqueteDatagrama(char * dat, unsigned int lg, char *dir, int pt){
    datos = new char[lg];

    longitud = lg;
    

    memcpy(ip,dir,sizeof(ip));
    puerto = pt;
    memcpy(datos,dat,lg);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int lg){
    datos = new char[lg];
    longitud = lg;
}

PaqueteDatagrama::~PaqueteDatagrama(){
    delete datos;
    longitud = 0;
    puerto = 0;
}

char * PaqueteDatagrama::obtieneDatos(){
    return datos;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
    return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
    return puerto;
}

char *PaqueteDatagrama::obtieneDireccion(){
    return ip;
}


void PaqueteDatagrama::inicializaPuerto(int pp){
    puerto = pp;
}

void PaqueteDatagrama::inicializaDatos(char * dd){
    memcpy(datos,dd,longitud);
}

void PaqueteDatagrama::inicializaIp(char * dir){
    memcpy(ip,dir,sizeof(ip));
}