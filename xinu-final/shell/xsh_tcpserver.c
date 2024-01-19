/*  tcpclient.c  - a tcp client for XINU */

#include <xinu.h>

shellcmd xsh_tcpserver(int nargs, char *args[])
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
    sock = tcp_register(ipaddr, port, -1);

}
