#ifndef SENDATA_H
#define SENDATA_H

unsigned char buffer[4];

void send_dirction(int sockfd,unsigned char LOW,unsigned char HIGH);//sned direction values 
void send_engine(int sockfd,unsigned char LOW,unsigned char HIGH);//send engine values
void send_backEngine(int sockfd,unsigned char LOW,unsigned char HIGH);//send back engine values
void send_ramX(int sockfd,unsigned char Data);//send ramX values
void send_ramY(int sockfd,unsigned char Data);//send ramX values

#endif
