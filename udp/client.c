/*client.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8181

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int sockfd, n;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    socklen_t servaddr_len;
    /*打开一个网络通讯端口，分配一个文件描述符sockfd*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;//地址采用IPv4地址
	
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); //将“点分十进制” －> “二进制整数”
    servaddr.sin_port = htons(SERV_PORT);//端口号从主机字节顺序转换成网络字节顺序

    while(fgets(buf, MAXLINE, stdin) != NULL){ //输入字符串
        /*发送给服务端*/
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if(n == -1)
            printf("sebdto err\n");
        /*从服务端接收数据*/
        n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0);
        if(n == -1)
            printf("recvfrom err\n");
        /*输出服务器处理后的数据*/
        write(STDOUT_FILENO, buf, n);
    }

    close(sockfd);
    return 0;
}