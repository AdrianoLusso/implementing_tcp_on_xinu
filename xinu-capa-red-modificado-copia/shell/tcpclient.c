#include <xinu.h>


void tcpclient(){
    printf("EMPEZO EL CLIENTE\n");

    uint32 ip = 127 << 24 | 0 << 16 |0 << 8  | 1;
    kprintf("receive ip: %u.%u.%u.%u\n",((ip >> 24) & 0xFF),((ip >> 16) & 0xFF),((ip >> 8) & 0xFF),((ip) & 0xFF));
    tcp_register(ip,5000,1);
    
    mqsend(Tcp.tcpcmdq,"holaaa");
    /*
    uint32 ip;
    uint16 port;
    int32 active=1;
    tcp_register(ip,port,active);
*/

}