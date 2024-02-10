#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"

#define PORT 8080
#define BUFFER_SIZE sizeof(struct infoMessage)
#define MAX_clientS 2



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

    // Habilita el socket para aceptar conexiones, con una cola de espera de tamaño 2
    listen(sockfd, 1);
    printf(" server listening\n");
    
    // Obtener la dirección IP y el puerto del servidor
    char server_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serv_addr.sin_addr), server_ip, INET_ADDRSTRLEN);
    int server_port = ntohs(serv_addr.sin_port);

    printf("Server listening on IP: %s, Port: %d\n", server_ip, server_port);
    return sockfd;
}

/*
int connectClient(int serverSocket)
{
    printf(" Inicio de  coonectCLient: %d\n",serverSocket);
    // conecta a una cliente al socket del servidor con el nro pasado por parametro

    int socketClient;
    // almacena la información de la dirección del cliente que se conecta al servidor.
    struct sockaddr_in pla_addr;
    int pla_length = sizeof(pla_addr);

    printf("antes del accept()\n");\
    socketClient = accept(serverSocket, (struct sockaddr *)&pla_addr, &pla_length);
        printf("despues del accept() %d\n",socketClient);
    while (socketClient < 0){
        printf("el socketclient es %d\n",socketClient);
        close(socketClient);
        }
    printf(" conecte clientesito nro de socket %d\n", socketClient);
    return socketClient;
}
*/

int connectClient(int serverSocket)
{
    int socketClient;
    struct sockaddr_in pla_addr;
    int pla_length = sizeof(pla_addr);

    printf("antes del accept()\n");

    // Keep trying to accept a client until successful
    while ((socketClient = accept(serverSocket, (struct sockaddr *)&pla_addr, &pla_length)) < 0) {
        perror("Error in accept");
        // You may want to add some sleep here to avoid busy-waiting
    }

    printf("despues del accept() %d\n", socketClient);
    printf("conecte clientesito nro de socket %d\n", socketClient);
    
    return socketClient;
}


void main()
{
    int client;
     printf(" Server going to init\n");
    int socketServer = serverInit();
    printf(" Server init finished: %d\n",socketServer);


    printf("antes del connectCLient()\n");
    client = connectClient(socketServer);

    unsigned char msg[40];
    read(client,&msg,sizeof(msg));
    printf("Received message: %s \n",msg);
    
    strcpy(msg,"BIENVENIDOS AL HIMALAYAA,HELADO? :D");
    write(client,&msg,sizeof(msg));
    
    printf("Server goinge to close...\n");
    close(socketServer);
    printf("Server close!!!\n");
}
