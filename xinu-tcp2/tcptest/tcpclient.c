#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 100

int main() {
    int sockfd;
    struct addrinfo hints, *res;
    char buf[100] = {0};

    // Crear un socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Cannot create socket\n");
        return 1;
    }

    // Configurar la estructura de dirección para la conexión, se setea con 0s para asegurarse de que
	//no haya otra informaciòn en la memoria 
    memset((char *)&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;  // Utilizar la dirección de la máquina local
    hints.ai_family = AF_INET;    // IPv4
    hints.ai_socktype = SOCK_STREAM;  // Socket de flujo (TCP)

    // Solicitar al usuario que ingrese el nombre del servidor
    char server_name[MAX_NAME_LENGTH];
    printf("Enter the server name: ");
    scanf("%s", server_name);
	//getaddrinfo toma un nombre de host y un servicio, realiza la resolución de nombres de dominio,
	// y devuelve información de dirección en términos de estructuras addrinfo. Se puede utilizar para establecer 
	//conexiones de red de manera flexible y compatible con IPv4 


    // Obtener la información de la dirección del servidor
    if (getaddrinfo(server_name, "12345", &hints, &res) == -1) {
        perror("getaddrinfo ");
        return 1;
    }

    // Conectar al servidor
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("connect");
        return 1;
    }
    printf("connected to %s!\n", server_name);

   // Solicitar al usuario que ingrese su nombre
    char name[50];
    char msg[20];

    printf("Enter your name: ");
    scanf("%s", name);

    // Enviar el nombre al servidor
    send(sockfd, name, 10, 0);

    // Recibir un mensaje del servidor
    recv(sockfd, msg, 20, 0);
    msg[19] = 0;  // Asegurarse de que la cadena esté terminada
    printf("%s\n", msg);

    // Cerrar el socket
    close(sockfd);
	return 0;
   
}