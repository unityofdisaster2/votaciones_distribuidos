# Proyecto correspondiente a sistema de Votaciones


Construir proyecto:
> make 

## Modo de uso: 

| instrucción | Descripción |
| ----------- | ----------- |
| ./gen n nombre_archivo  | genera n registros y los guarda en un archivo |
| ./setTime puerto | retorna un timestamp a los servidores que lo consulten |
| ./servConf puerto archivo_destino ipTiempo puertoTiempo  | ejecuta un servidor udp en el puerto indicado, este se conectara al servidor de tiempo para obtener un timestamp y finalmente guardara los registros enviados por el cliente en el archivo destino |
| ./clientConf ipA ptoA ipB ptoB ipC ptoC nombre_archivo n | ejecuta un cliente udp encargado de enviar n registros de un archivo a los servidores A, B y C de tal modo que se distribuya la carga de cada uno de forma equitativa |
