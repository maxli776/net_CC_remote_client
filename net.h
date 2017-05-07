#ifndef NET_H
#define NET_H

extern unsigned char server_port[];
extern unsigned char server_addr[];

int net_init(void);//Network Config Init,return the socket fd.
void net_close(int sockfd);//Close the sockfd.
int handshake(int sockfd);

#endif
