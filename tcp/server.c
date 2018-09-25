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
    /*�����׽��ֵ�ַ�ṹ�� �����servaddr �ͻ���cliaddr*/   
    struct sockaddr_in servaddr, cliaddr; 
    socklen_t cliaddr_len;  
    int listenfd, connfd;   //�����ļ��������������ļ�������
    char buf[MAXLINE];      
    char str[INET_ADDRSTRLEN];//#define INET_ADDRSTRLEN 16  /* for IPv4 dotted-decimal */ 
    int i, n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //��һ������ͨѶ�˿ڣ�����һ���ļ�������listenfd

    bzero(&servaddr, sizeof(servaddr));          //��շ�����׽���
    servaddr.sin_family = AF_INET;               //��ַ����IPv4��ַ 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//��ַ�������ֽ�˳��ת���������ֽ�˳��
    servaddr.sin_port = htons(SERV_PORT);        //�˿ںŴ������ֽ�˳��ת���������ֽ�˳��

    /*���ļ�������listenfd�ͷ�������ַ����һ��*/
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    /*����listenfd���ڼ���״̬���������������20���ͻ��˴��ڴ�����״̬*/
    listen(listenfd, 20);

    printf("�ȴ�������...\n");
    while(1){
        cliaddr_len = sizeof(cliaddr);
        /*connfd�ļ����������ںͿͻ���ͨ�ţ�����������accept()��������*/
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
        /*��connfd�ж�ȡ����*/
        n = read(connfd, buf, MAXLINE);
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                ntohs(cliaddr.sin_port));

        for(i = 0; i<n; i++){
            buf[i] = toupper(buf[i]);
        }
        /*��connfd��д����*/
        write(connfd, buf, n);
        close(connfd);
    }
}