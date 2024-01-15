#ifndef COMMON_H
#define COMMON_H
#define MSG_SIZE sizeof(struct infoMessage)

//mensaje para mandarle al server 
struct  infoMessage    {
    int clientId;// id de los players
} ;
void sendMessage(int socketDest, struct infoMessage* msg);

//metodo del servidor void recv_move_fuser(int from_sockfd, struct move* m);
void recv_message(int from_sockfd, struct infoMessage* msg);

#endif
