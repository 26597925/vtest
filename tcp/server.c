/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main(void)
{
    /*网络套接字地址结构体 服务端servaddr 客户端cliaddr*/   
    struct sockaddr_in servaddr, cliaddr; 
    socklen_t cliaddr_len;  
    int listenfd, connfd;   //监听文件描述符、连接文件描述符
    char buf[MAXLINE];      
    char str[INET_ADDRSTRLEN];//#define INET_ADDRSTRLEN 16  /* for IPv4 dotted-decimal */ 
    int i, n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //打开一个网络通讯端口，分配一个文件描述符listenfd

    bzero(&servaddr, sizeof(servaddr));          //清空服务端套接字
    servaddr.sin_family = AF_INET;               //地址采用IPv4地址 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//地址从主机字节顺序转换成网络字节顺序
    servaddr.sin_port = htons(SERV_PORT);        //端口号从主机字节顺序转换成网络字节顺序

    /*将文件描述符listenfd和服务器地址绑定在一起*/
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    /*声明listenfd处于监听状态，并且最多允许有20个客户端处于待连接状态*/
    listen(listenfd, 20);

    printf("等待连接中...\n");
    while(1){
        cliaddr_len = sizeof(cliaddr);
        /*connfd文件描述符用于和客户端通信，服务器调用accept()接受连接*/
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        /*从connfd中读取数据*/
        n = read(connfd, buf, MAXLINE);
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                ntohs(cliaddr.sin_port));

        for(i = 0; i<n; i++){
            buf[i] = toupper(buf[i]);
        }
        /*往connfd中写数据*/
        write(connfd, buf, n);
        close(connfd);
    }
}