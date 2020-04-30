

construir: gen servidor cliente

servidor: PaqueteDatagrama.o SocketDatagrama.o servidor.cpp
	g++ -g servidor.cpp PaqueteDatagrama.o SocketDatagrama.o -o servidor

cliente: PaqueteDatagrama.o SocketDatagrama.o cliente.cpp
	g++ -g cliente.cpp PaqueteDatagrama.o SocketDatagrama.o -o cliente

gen: gen_registros_cel_clave_ver3.cpp
	g++ gen_registros_cel_clave_ver3.cpp -o gen

SocketDatagrama.o: SocketDatagrama.h SocketDatagrama.cpp
	g++ -g SocketDatagrama.cpp -c

PaqueteDatagrama.o: PaqueteDatagrama.h PaqueteDatagrama.cpp
	g++ -g PaqueteDatagrama.cpp -c