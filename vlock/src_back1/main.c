/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
 
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
//#include <openssl/x509.h>

#include "rsa.h"
#include "byte_buffer.h"
 
typedef unsigned char byte;

#define BUFSIZE 666
#define SERV_PORT 3000
#define OPEN_MAX 1024
 
/*typedef struct HandshakeMessage {
	
	char *vender;
	
	char *imei;
	
	char *tel;
	
	char *ver;
	
	byte iv[16];
	
	byte clientKey[16];
	
	int heartbeat;
	
	long timestamp;
	
} HandshakeMessage_t;
 
static void handshake()
{
	HandshakeMessage_t* handshakeMessage = (HandshakeMessage_t*)malloc(sizeof(HandshakeMessage_t));
	handshakeMessage->vender = "CS";
	handshakeMessage->imei = "a2sd2rsd5ers32s";
	handshakeMessage->tel = "198293891839";
	handshakeMessage->ver = "V1.0";
}*/
/*
length	int	4	表示body的长度
cmd	byte	1	表示消息协议类型
checkcode	short	2	是根据body生成的一个校验码
flags	byte	1	表示当前包启用的特性，比如是否启用加密，是否启用压缩
sessionId	int	4	消息会话标识用于消息响应
lrc	byte	1	纵向冗余校验，用于校验header
*/
//{  vender='CS', imei='a2sd2rsd5ers32s', tel='198293891839', ver='V1.0', iv=[121, 80, 34, 109, -116, 93, 18, 20, -111, -90, -60, -106, -93, -89, 50, -34], clientKey=[120, 67, 81, 53, 85, -60, -78, -58, 11, 75, 40, 86, 34, 26, 4, -70], heartbeat=0, timestamp=1505553851134, 
//packet={cmd=2, cc=0, flags=1, sessionId=1, lrc=0, body=0}}

int getpub_rsakey(const char *key, RSA **prsa)
{
	BIO *bio = NULL;
	if (NULL == (bio = BIO_new_mem_buf(key, -1))) {
		printf("BIO_new_membuf() fail!\n");
		return -1;
	}
	//*prsa = d2i_RSAPublicKey_bio(bio, prsa);
	*prsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
	if (!(*prsa)) {
		printf("PEM_readbio_RSA_PUBKEY() fali!\n");
		BIO_free_all(bio);
		return -1;
	}
	return 0;
}

int getpri_rsakey(const char *key, RSA **prsa)
{
	BIO *bio = NULL;
	if (NULL == (bio = BIO_new_mem_buf(key, -1))) {
		printf("BIO_new_membuf() fail!\n");
		return -1;
	}
	//*prsa = d2i_RSAPrivateKey_bio(bio, prsa);
	 *prsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
	if (!(*prsa)) {
		printf("PEM_read_bio_RSAPrivateKey() fail!\n");
		BIO_free_all(bio);
		return -1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int ret = 0;
	/*ret = request("http://vedio.yunos-tv.com/?r=api/index/loadBackgroud");
	if(ret < 1) return ret; 
	set_follow_location(0);
	char *result = response();
	printf("%s", result);
		
	//{cmd=2, cc=0, flags=1, sessionId=1, lrc=0, body=0}

	//ret = getpri_rsakey(daily_privateKey, &dailyPrivateKey);
	//printf("%p \n", dailyPrivateKey);
	
	byte_buffer_t *out = bb_create(1024);
	bb_putInt(out, 0);
	bb_put(out, 2);
	bb_putShort(out, 0);
	bb_put(out, 1);
	bb_putInt(out, 1);
	bb_put(out, 0);

	struct sockaddr_in servaddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,0x00,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.16.9", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	ret = write(sockfd, bb_array(out), bb_arrayOffset(out));
	sleep(10000000);
	
	close(sockfd);*/
		
	char *publicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQApfc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoVPpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUywQIDAQAB";
	publicKey = format_key(publicKey, RSA_PUBLIC);
	
	char *privateKey = "MIIEowIBAAKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQApfc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoVPpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUywQIDAQABAoIBADhg1u1Mv1hAAlX8omz1Gn2f4AAW2aos2cM5UDCNw1SYmj+9SRIkaxjRsE/C4o9sw1oxrg1/z6kajV0eN/t008FdlVKHXAIYWF93JMoVvIpMmT8jft6AN/y3NMpivgt2inmmEJZYNioFJKZGX+/vKYvsVISZm2fw8NfnKvAQK55yu+GRWBZGOeS9K+LbYvOwcrjKhHz66m4bedKdgVAix6NE5iwmjNXktSQlJMCjbtdNXg/xo1/G4kG2p/MO1HLcKfe1N5FgBiXj3QjlvgvjJZkh1as2KTgaPOBqZaP03738VnYg23ISyvfT/teArVGtxrmFP7939EvJFKpF1wTxuDkCgYEA7t0DR37zt+dEJy+5vm7zSmN97VenwQJFWMiulkHGa0yU3lLasxxum0oUtndIjenIvSx6t3Y+agK2F3EPbb0AZ5wZ1p1IXs4vktgeQwSSBdqcM8LZFDvZuPboQnJoRdIkd62XnP5ekIEIBAfOp8v2wFpSfE7nNH2u4CpAXNSF9HsCgYEA2l8DJrDE5m9Kkn+J4l+AdGfeBL1igPF3DnuPoV67BpgiaAgI4h25UJzXiDKKoa706S0D4XB74zOLX11MaGPMIdhlG+SgeQfNoC5lE4ZWXNyESJH1SVgRGT9nBC2vtL6bxCVVWBkTeC5D6c/QXcai6yw6OYyNNdp0uznKURe1xvMCgYBVYYcEjWqMuAvyferFGV+5nWqr5gM+yJMFM2bEqupD/HHSLoeiMm2O8KIKvwSeRYzNohKTdZ7FwgZYxr8fGMoGPxQ1VK9DxCvZL4tRpVaU5Rmknud9hg9DQG6xIbgIDR+f79sb8QjYWmcFGc1SyWOASkjlykZ2yt4xnqi3BfiD9QKBgGqLgRYXmXp1QoVIBRaWUi55nzHg1XbkWZqPXvz1I3uMLv1jLjJlHk3euKqTPmC05HoApKwSHeA0/gOBmg404xyAYJTDcCidTg6hlF96ZBja3xApZuxqM62F6dV4FQqzFX0WWhWp5n301N33r0qR6FumMKJzmVJ1TA8tmzEFyINRAoGBAJqioYs8rK6eXzA8ywYLjqTLu/yQSLBn/4ta36K8DyCoLNlNxSuox+A5w6z2vEfRVQDq4Hm4vBzjdi3QfYLNkTiTqLcvgWZ+eX44ogXtdTDO7c+GeMKWz4XXuJSUVL5+CVjKLjZEJ6Qc2WZLl94xSwL71E41H4YciVnSCQxVc4Jw";
	privateKey = format_key(privateKey, RSA_PRIVATE);

	char aa[] = {90, 34, -123, 66, -42, -52, -55, -79, -56, -26, -112, 1, -16, -24, -98, -124, 26, -34, -124, -24, 3, -109, -88, -56, -60, 40, 1, 5, -114, -107, 61, 122, -43, 109, 92, 4, 83, -86, 123, -106, -36, -80, 52, 77, 65, 20, 1, -21, -77, 49, -46, -86, 4, 43, 78, 52, -99, -90, 57, 31, 23, -90, 121, 73, -85, 63, -109, 127, -28, -98, -19, -58, -8, -56, -46, 65, -104, -2, -104, 37, 28, -17, 100, -9, -124, -54, 10, 24, 87, -48, -54, -111, -109, -10, 69, 93, -56, -38, -117, -35, -105, 86, -86, 54, -56, 61, -93, -56, -119, -68, 36, -41, 34, -15, -113, 90, -32, -100, -94, -102, -44, 81, 101, -112, 84, -48, -103, 73, -14, 7, -33, 118, 42, 97, 124, 76, -102, -79, -23, 73, -32, -63, -119, -77, -49, -85, 126, 9, -31, 33, -59, -67, -84, -56, 51, 36, -78, -51, -125, 6, 67, 57, 86, -123, -26, -128, -75, 77, -57, -126, -41, 15, -52, 10, 119, 50, 114, 117, -30, 1, -128, 125, -32, 51, 58, 122, -73, 112, -76, 0, -50, 99, -115, -11, 44, -3, 107, -38, 80, -33, 84, -122, 122, -49, 1, 126, -36, 77, -104, 22, 94, 99, 32, 114, 79, 103, -22, -9, -105, -110, -22, -81, -64, 95, 6, 49, -94, 6, 126, 119, 6, -122, -91, -21, 60, 76, 7, 103, 89, 48, -22, -6, 30, -24, 98, 11, -71, 51, -49, -69, 21, 57, -100, -4, 74, -31};
	char cc[1024];
	/*char bb[1024];
	char cc[1024];
	
	printf("==len:%d=== \n", (int)strlen(aa));
	int decrypted_length =  rsa_public_encrypt((unsigned char *)aa, strlen(aa), (unsigned char *)publicKey, (unsigned char *)bb);
	printf("==ret:%d=== \n", decrypted_length);
	//printf("==ret:%s=== \n", bb);*/
	
	ret = rsa_private_decrypt((unsigned char *)aa, sizeof(aa), (unsigned char *)privateKey, (unsigned char *)cc);
	printf("==ret:%d=== \n", ret);
	printf("==ret:%p=== \n", cc);
	
	byte_buffer_t *out = bb_wrap(cc, 0, ret);
	int fieldLength = bb_getShort(out);
	printf("==ret:%d=== \n", fieldLength);
	char rr[256];
	bb_get_buffer(out, rr, 0, fieldLength);
	printf("==ret:%s=== \n", rr);
	fieldLength = bb_getShort(out);
	printf("==ret:%d=== \n", fieldLength);
	bb_get_buffer(out, rr, 0, fieldLength);
	printf("==ret:%s=== \n", rr);
       /* if (fieldLength == 0) return null;
        if (fieldLength == Short.MAX_VALUE) {
            fieldLength += body.readInt();
        }*/
	
	return ret;
}
