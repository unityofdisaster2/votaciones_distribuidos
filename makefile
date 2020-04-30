

construir: gen servidor cliente clienteConfiable servidorConfiable

clienteConfiable: clienteConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.o
	g++ -g clienteConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.o -o clientConf

servidorConfiable: servidorConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o
	g++ -g servidorConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o -o servConf


servidor: PaqueteDatagrama.o SocketDatagrama.o servidor.cpp
	g++ -g servidor.cpp PaqueteDatagrama.o SocketDatagrama.o -o servidor

cliente: PaqueteDatagrama.o SocketDatagrama.o cliente.cpp
	g++ -g cliente.cpp PaqueteDatagrama.o SocketDatagrama.o -o cliente

gen: gen_registros_cel_clave_ver3.cpp
	g++ gen_registros_cel_clave_ver3.cpp -o gen

Respuesta.o: Respuesta.h Respuesta.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ -g Respuesta.cpp -c

Solicitud.o: Solicitud.h Solicitud.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ -g Solicitud.cpp -c

SocketDatagrama.o: SocketDatagrama.h SocketDatagrama.cpp
	g++ -g SocketDatagrama.cpp -c

PaqueteDatagrama.o: PaqueteDatagrama.h PaqueteDatagrama.cpp
	g++ -g PaqueteDatagrama.cpp -c

.PHONY: clean

clean:
	rm -rf *.o servidor cliente clientConf servConf