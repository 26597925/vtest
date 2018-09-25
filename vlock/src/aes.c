#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void printf_buff(char *buff,int size) {
    int i = 0;
    for (i=0;i<size;i ++ ) {
        printf( "%02X ", (unsigned char)buff[i] );
        if ((i+1) % 8 == 0) {
            printf("\n");
        }
    }
}

unsigned char* str2hex(char *str) {
    unsigned char *ret = NULL;
    int str_len = strlen(str);
    int i = 0;
    assert((str_len%2) == 0);
    ret = (unsigned char *)malloc(str_len/2);
    for (i =0;i < str_len; i = i+2 ) {
        sscanf(str+i,"%2hhx",&ret[i/2]);
    }
    return ret;
}
char *padding_buf(char *buf, int size, int *final_size) {
    char *ret = NULL;
    int pidding_size = AES_BLOCK_SIZE - (size % AES_BLOCK_SIZE);
    int i;
    *final_size = size + pidding_size + 1;
    ret = (char *)malloc(*final_size);
    memcpy( ret, buf, size);
    if (pidding_size!=0) {
        for (i =size;i < *final_size; i++ ) {
            ret[i] = pidding_size;
        }
    }
	ret[*final_size - 1] = '\0';
    return ret;
}

void strip_buff(char *decrpy_buf) {
	int len = strlen(decrpy_buf);
	int size = decrpy_buf[len-1];
	
	printf("strip_buff:%d, %02x=== \n", size, size);
	
	char stbuf[len - size + 1];
	strncpy(stbuf, decrpy_buf, len - size);
	stbuf[len - size] = 0;
	printf("strip_buff:%s=== \n", stbuf);
	//return stbuf;
}

void encrpyt_buf(char *raw_buf, char **encrpy_buf, int len ) {
    AES_KEY aes;
    unsigned char key[] = "asdfasdfasdfasdf";//str2hex("8cc72b05705d5c46f412af8cbed55aad");
    unsigned char iv[] = "1234567812345678";//str2hex("667b02a85c61c786def4521b060265e8");
	/*for (int i=0; i < strlen((const char *)key); i++)
	{
		printf("%d ", key[i]);
	}
	printf("\n");
	for (int i=0; i < strlen((const char *)iv); i++)
	{
		printf("%d ", iv[i]);
	}
	printf("\n");*/
		
    AES_set_encrypt_key(key,128,&aes);
    AES_cbc_encrypt((unsigned char *)raw_buf,(unsigned char *)*encrpy_buf, len, &aes, iv, AES_ENCRYPT);
    //free(key);
   // free(iv);
}
void decrpyt_buf(char *raw_buf, char **encrpy_buf, int len ) {
    AES_KEY aes;
    unsigned char key[] = "asdfasdfasdfasdf";//str2hex("8cc72b05705d5c46f412af8cbed55aad");
    unsigned char iv[] = "1234567812345678";//str2hex("667b02a85c61c786def4521b060265e8");
	
    AES_set_decrypt_key(key,128,&aes);
    AES_cbc_encrypt((unsigned char *)raw_buf,(unsigned char *)*encrpy_buf, len, &aes, iv, AES_DECRYPT);
   // free(key);
   // free(iv);
}
int main(int argn, char *argv[] ) {
    char *raw_buf = "as3214324da2435sda456sdasd46456asd1231231sadasd22313145sdf56gfsdw23asxcvcasd235xbfjrre213dadasaddwqaseqws4";
    char *after_padding_buf = NULL;
    int padding_size = 0;
    char *encrypt_buf = NULL;
    char *decrypt_buf = NULL;
    /*raw_buf = (char *)malloc(12);
    memcpy(raw_buf,"asdasdasd12312312313123asdadasdwqeqw",12);
    printf("------------------raw_buf:%s\n", raw_buf);*/
   // printf_buff(raw_buf,17);
    // 2
    after_padding_buf = padding_buf(raw_buf, strlen(raw_buf), &padding_size);
    printf("------------------after_padding_buf\n");
    printf_buff(after_padding_buf, padding_size);
    // 3
	int len = 0;
	if((strlen(after_padding_buf)+1)%AES_BLOCK_SIZE==0)
		len=strlen(after_padding_buf)+1;
	else
		len=((strlen(after_padding_buf)+1)/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;

    encrypt_buf = (char *)malloc(len);
    encrpyt_buf(after_padding_buf, &encrypt_buf, len);
    printf("------------------encrypt_buf\n");
   // printf_buff(encrypt_buf,padding_size);
	/*for (int i=0; i < strlen((const char *)encrypt_buf); i++)
	{
		printf("%d ", encrypt_buf[i]);
	}
	printf("\n");
    */
	
	if((strlen(encrypt_buf)+1)%AES_BLOCK_SIZE==0)
		len=strlen(encrypt_buf)+1;
	else
		len=((strlen(encrypt_buf)+1)/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
	
    decrypt_buf = (char *)malloc(len);
    decrpyt_buf(encrypt_buf, &decrypt_buf, len);
	
	printf("===========\n");
	strip_buff(decrypt_buf);
	
	//free(raw_buf);
    free(after_padding_buf);
    free(encrypt_buf);
    free(decrypt_buf);
    return 0;
}