/*  tcpclient.c  - a tcp client for XINU */

#include <xinu.h>
#include <stdlib.h>
#include <dns.h>


/*############# Codigo para hacer peticion GET a URL con Protocolo TCP a servidor HTTP #############*/

shellcmd xsh_tcpclient(int nargs, char *args[])
{
	int32 res, i, len;
	int32 sock;
	int32 ipaddr;
	int port;
	unsigned char msg[80];


	char * url =args[1]; 
	printf("La URL es: %s\n", url);
	ipaddr= dnslookup (url); 
	port = atoi(args[2]);

	printf("connecting to server... \n");

	/* tcp connection */
	sock = tcp_register(ipaddr, port, 1);
	if (sock == SYSERR) {
		printf("fail \n");
		return;
	}
	printf("Connection ready!... \n");


	strcpy(msg, "GET /philosophy/free-sw.html HTTP/1.0\r\nHost: www.gnu.msn.by\r\n\r\n");
	len = strlen(msg) + 1;	/* plus one is for end of string char */

	printf("El mensaje es: %s\n", msg);
	printf("La longitud del mensaje es: %d\n", len);



	printf("sending message to server... \n");

	/* send msg */
	tcp_send(sock, msg, len);

	printf("mensaje mandadisimo");

	/*wait answer */
	// Bucle para recibir datos hasta que tcp_recv() retorne 0
    while (1) {
        int32 bytesRead = tcp_recv(sock, msg,sizeof(msg));

        if (bytesRead == 0) {
            // No hay más datos para recibir, sale del bucle
            break;
        } else if (bytesRead == SYSERR) {
            // Manejar error de recepción
            printf("Error receiving data from server\n");
            break;
        } else {
            eliminarEtiquetasYmostrar(msg, bytesRead);
        }
    }

    // Cerrar la conexión
    tcp_close(sock);

    return OK;

}
// Función para eliminar los tag y mostrar por pantalla
void eliminarEtiquetasYmostrar(unsigned char *data, int32 length)
    for (int i = 0; i < length; i++) {
        // Sacar etiquetas HTML
        if (data[i] == '<') {
            while (i < length && data[i] != '>')
                i++;
        } else {
            printf("%c", data[i]);
        }
    }
}

/*############# FIN codigo para hacer peticion GET a URL con Protocolo TCP a servidor HTTP #############*/


/*############# Codigo para conectarse a servidor linux #############*/

// shellcmd xsh_tcpclient(int nargs, char *args[])
// {
// 	int32 res, i, len;
// 	int32 sock;
// 	int32 ipaddr;
// 	int port;
// 	unsigned char msg[40];

//         if (nargs < 3) {
//                 printf("%s: invalid arguments\n", args[0]);
//                 printf("%s IP PORT\n", args[0]);
//                 return 1;
//         }

// 	res = dot2ip(args[1], &ipaddr);
// 	if ((int32)res == SYSERR) {
// 		printf("%s: invalid IP address\n", args[1]);
// 		return 1;
// 	}

// 	port = atoi(args[2]);

// 	printf("connecting to server... \n");

// 	/* tcp connection */
// 	sock = tcp_register(ipaddr, port, 1);
// 	if (sock == SYSERR) {
// 		printf("fail \n");
// 		return;
// 	}
// 	printf("Connection ready!... \n");


// 	strcpy(msg, "ARG 3 - FRA 2");
// 	len = strlen(msg) + 1;	/* plus one is for end of string char */

// 	printf("sending message to server... \n");

// 	/* send msg */
// 	tcp_send(sock, msg, len);

// 	/* wait answer */
// 	res = tcp_recv(sock, msg, 40);

// 	printf("%d bytes received. answer: %s\n", res, msg);

// 	tcp_close(sock);

// 	return OK;
// }

/*############# FIN Codigo para conectarse a servidor linux #############*/