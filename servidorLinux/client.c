
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "common.h"


int sock;

int init(int port, char *server_name)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *server = gethostbyname(server_name);

    if (server == NULL)
        error(1, 0, "Servidor %s no encontrado.\n", server_name);

    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    printf("Connecting to %s:%d...\n", server->h_name, port);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // Conectamos con el servidor
        error(1, 0, "No se puede conectar.\n");
    printf("Termino el init()");
    return sock;
}

int main(int argc, char *argv[])
{


    if (argc < 3)
        error(1, 0, "Ingrese el numero de puerto y el servidor\n");

    sock = init(atoi(argv[1]), argv[2]);

    


}
