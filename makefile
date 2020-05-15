

construir: gen servidor cliente clienteConfiable servidorConfiable servidorTiempo

clienteConfiable: clienteConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.o
	g++ -g clienteConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Solicitud.o -o clientConf -lpthread


servidorTiempo: servidorTiempo.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o TrieUtil.o
	g++ -g servidorTiempo.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o TrieUtil.o -o servTime


servidorConfiable: servidorConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o TrieUtil.o Solicitud.o
	g++ -g servidorConfiable.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o Solicitud.o TrieUtil.o -o servConf



servidor: PaqueteDatagrama.o SocketDatagrama.o servidor.cpp
	g++ -g servidor.cpp PaqueteDatagrama.o SocketDatagrama.o -o servidor

cliente: PaqueteDatagrama.o SocketDatagrama.o cliente.cpp
	g++ -g cliente.cpp PaqueteDatagrama.o SocketDatagrama.o -o cliente

gen: gen_registros_cel_clave_ver3.cpp
	g++ gen_registros_cel_clave_ver3.cpp -o gen


TrieUtil.o: TrieUtil.h TrieUtil.cpp
	g++ -g TrieUtil.cpp -c

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