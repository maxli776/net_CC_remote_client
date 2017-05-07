#include "../include/includes.h"


unsigned char server_port[] = "6349";
unsigned char server_addr[] = "123.206.62.143";
unsigned char myname[] = "client";

int net_init(void)//Network Config Init,return the socket fd.
{
    int client_fd;
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    client_fd = socket(AF_INET,SOCK_STREAM,0);
    if(client_fd < 0)
    {
        perror("client socket creat error");
        exit(1);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(server_port));
    inet_pton(AF_INET,server_addr,&serveraddr.sin_addr.s_addr);
    if(connect(client_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
    {
        perror("connect to server error");
        exit(1);
    }
    return client_fd;
}


void net_close(int sockfd)
{
    close(sockfd);
}

int handshake(int sockfd)
{
    unsigned char buf[3];
    write(sockfd,myname,sizeof(myname));
    read(sockfd,buf,sizeof(buf));
    if(strcmp(buf,"yes") == 0)
        return 1;
    else
        return 0;
}
