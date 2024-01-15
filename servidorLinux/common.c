#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"

#define PORT 5000
#define BUFFER_SIZE 8
#define MAX_PLAYERS 2




void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int serverInit()
{
    int sockfd;
    // direccion del socket
    struct sockaddr_in serv_addr;

    // Crea el socket del servidor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error al abrir el socket\n");
    }

    // Inicializa la estructura de dirección del servidor
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Enlaza el socket al puerto
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Error en el enlace\n");
    }

    // Habilita el socket para aceptar conexiones, con una cola de espera de tamaño 1
    listen(sockfd, 1);
    printf(" server listening\n");
    return sockfd;
}

int connectClient(int serverSocket)
{
    // conecta a una jugador al socket del servidor con el nro pasado por parametro

    int socketClient;
    // almacena la información de la dirección del cliente que se conecta al servidor.
    struct sockaddr_in pla_addr;
    int pla_length = sizeof(pla_addr);

    while ((socketClient = accept(serverSocket, (struct sockaddr *)&pla_addr, &pla_length)) < 0)
        close(socketClient);
    printf(" conecte clientesito nro de socket %d\n", socketClient);
    return socketClient;
}







void main()
{
    char h="o";

    int client;
    int socketServer = serverInit();
 
    client = connectClient(socketServer);
    sendMessage(client,&h);

    recv_message(client,&h);

    
    
 
   
    close(socketServer);
}
