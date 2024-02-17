/*  tcpclient.c  - a tcp client for XINU */

#include <xinu.h>

shellcmd xsh_tcpclient(int nargs, char *args[])
{
	int32 res, i, len;
	int32 sock;
	int32 ipaddr;
	int port;
	unsigned char msg[40];

        if (nargs < 3) {
                printf("%s: invalid arguments\n", args[0]);
                printf("%s IP PORT\n", args[0]);
                return 1;
        }

	res = dot2ip(args[1], &ipaddr);
	if ((int32)res == SYSERR) {
		printf("%s: invalid IP address\n", args[1]);
		return 1;
	}

	port = atoi(args[2]);

	printf("connecting to server... \n");

	/* tcp connection */
	sock = tcp_register(ipaddr, port, 1);
	if (sock == SYSERR) {
		printf("fail \n");
		return;
	}
	printf("Connection ready!... \n");


	strcpy(msg, "ARG 3 - FRA 2");
	len = strlen(msg) + 1;	/* plus one is for end of string char */

	printf("sending message to server... \n");

	/* send msg */
	tcp_send(sock, msg, len);

	/* wait answer */
	res = tcp_recv(sock, msg, 40);

	printf("%d bytes received. answer: %s\n", res, msg);

	tcp_close(sock);

	return OK;
}
