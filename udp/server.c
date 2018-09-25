/*server.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8181

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int sockfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int i, n;

    /*打开一个网络通讯端口，分配一个文件描述符sockfd*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));//初始化为空
    servaddr.sin_family = AF_INET;//地址采用IPv4地址
	
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//地址从主机字节顺序转换成网络字节顺序
    servaddr.sin_port = htons(SERV_PORT);//端口号从主机字节顺序转换成网络字节顺序


    /*将文件描述符sockfd和服务器地址绑定*/
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("等待连接...\n");
    while(1){
        cliaddr_len = sizeof(cliaddr);
		printf("call %s %s %d\n",__FILE__, __FUNCTION__, __LINE__);
        /*接收client端传过来的的字符串，写入buf*/
        n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
        if(n == -1){
            printf("recvfrom error");
        }
		
		if(inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)) != NULL)
		{
			/*打印客户端IP及端口*/
		    printf("接收到来自地址为 %s 端口号为 %d 的数据\n", 
					str,
					ntohs(cliaddr.sin_port));
					
			/*小写转为大写*/        
			for(i = 0; i<n; i++){
				buf[i] = toupper(buf[i]);
			}
			/*把数据发送给客户端*/
			n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
			if (n == -1){
				printf("sendto error\n");
			}
			
		}
    }

    return 0;
}