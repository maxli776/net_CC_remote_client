#include "includes.h"

unsigned char buffer[4];

void send_dirction(int sockfd,unsigned char LOW,unsigned char HIGH)//sned direction values
{
    buffer[0] = 0x01;
    buffer[1] = LOW;
    buffer[2] = HIGH;
    buffer[3] = LOW ^ HIGH;
    write(sockfd,buffer,sizeof(buffer));
}

void send_engine(int sockfd,unsigned char LOW,unsigned char HIGH)//send engine values
{
    buffer[0] = 0x02;
    buffer[1] = LOW;
    buffer[2] = HIGH;
    buffer[3] = LOW ^ HIGH;
    write(sockfd,buffer,sizeof(buffer));
}

void send_backEngine(int sockfd,unsigned char LOW,unsigned char HIGH)//send back engine values
{
    buffer[0] = 0x03;
    buffer[1] = LOW;
    buffer[2] = HIGH;
    buffer[3] = LOW ^ HIGH;
    write(sockfd,buffer,sizeof(buffer));
}

void send_ramX(int sockfd,unsigned char Data)//send ramX values
{
    buffer[0] = 0x04;
    buffer[1] = 0xCD;
    buffer[2] = Data;
    buffer[3] = buffer[1] ^ Data;
    write(sockfd,buffer,sizeof(buffer));
}

void send_ramY(int sockfd,unsigned char Data)//send ramX values
{
    buffer[0] = 0x05;
    buffer[1] = 0xEF;
    buffer[2] = Data;
    buffer[3] = buffer[1] ^ Data;
    write(sockfd,buffer,sizeof(buffer));
}
