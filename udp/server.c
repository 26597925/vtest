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

    /*��һ������ͨѶ�˿ڣ�����һ���ļ�������sockfd*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));//��ʼ��Ϊ��
    servaddr.sin_family = AF_INET;//��ַ����IPv4��ַ
	
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//��ַ�������ֽ�˳��ת���������ֽ�˳��
    servaddr.sin_port = htons(SERV_PORT);//�˿ںŴ������ֽ�˳��ת���������ֽ�˳��


    /*���ļ�������sockfd�ͷ�������ַ��*/
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("�ȴ�����...\n");
    while(1){
        cliaddr_len = sizeof(cliaddr);
		printf("call %s %s %d\n",__FILE__, __FUNCTION__, __LINE__);
        /*����client�˴������ĵ��ַ�����д��buf*/
        n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &cliaddr_len);
        if(n == -1){
            printf("recvfrom error");
        }
		
		if(inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)) != NULL)
		{
			/*��ӡ�ͻ���IP���˿�*/
		    printf("���յ����Ե�ַΪ %s �˿ں�Ϊ %d ������\n", 
					str,
					ntohs(cliaddr.sin_port));
					
			/*СдתΪ��д*/        
			for(i = 0; i<n; i++){
				buf[i] = toupper(buf[i]);
			}
			/*�����ݷ��͸��ͻ���*/
			n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
			if (n == -1){
				printf("sendto error\n");
			}
			
		}
    }

    return 0;
}