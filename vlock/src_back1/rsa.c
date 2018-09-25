#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <math.h>

#include "rsa.h"

RSA *rsa_create(unsigned char *key, rsa_key_type_t key_type)
{
    BIO *bio;
	RSA *rsa = NULL;
	
   // bio = BIO_new_mem_buf(key, -1);
	bio = BIO_new(BIO_s_mem());
    BIO_puts(bio, (const char *)key);
    if (bio==NULL)
        return NULL;
	
    if(key_type == RSA_PUBLIC)
    {
        rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL,NULL, NULL);
    }
    else
    {
        rsa = PEM_read_bio_RSAPrivateKey(bio, NULL,NULL, NULL);
    }
	
	if(rsa == NULL)
		BIO_free_all(bio);
	
    return rsa;
}

int rsa_public_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted)
{
	RSA *rsa = rsa_create(key, RSA_PUBLIC);
	if(rsa == NULL)
		return -1;
	
    return RSA_public_encrypt(data_len, data, encrypted, rsa, RSA_PKCS1_PADDING);
}

int rsa_public_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted)
{
	RSA *rsa = rsa_create(key, RSA_PUBLIC);
	if(rsa == NULL)
		return -1;
	
    return RSA_public_decrypt(data_len, enc_data, decrypted, rsa, RSA_PKCS1_PADDING);
}

int rsa_private_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted)
{
	RSA *rsa = rsa_create(key, RSA_PRIVATE);
	if(rsa == NULL)
		return -1;
	
    return RSA_private_encrypt(data_len, data, encrypted, rsa, RSA_PKCS1_PADDING);
}

int rsa_private_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted)
{
	RSA *rsa = rsa_create(key, RSA_PRIVATE);
	if(rsa == NULL)
		return -1;
	
    return RSA_private_decrypt(data_len, enc_data, decrypted, rsa, RSA_PKCS1_PADDING);
}

static char* substr( const char *src,  int offset, int length) 
{
    int total_length = strlen(src);
    int real_length = ((total_length - offset) >= length ? length : (total_length - offset)) + 1;
	
    char *tmp = (char*) malloc(real_length * sizeof(char));
    strncpy(tmp, src + offset, real_length - 1);
    tmp[real_length - 1] = '\0';
	
    return tmp;
}

char *format_key(char *key, rsa_key_type_t key_type)
{
	int val = 64;
	int len = strlen(key);
	int size = ceil(len/(double)val);
	char **arr = (char **)malloc((size + 2)*val);
	
	for(int i = 0; i < size; i++)
	{
		arr[i+1] = substr(key, val*i, val);
	}
	
	if(key_type == RSA_PUBLIC)
    {
		arr[0] = "-----BEGIN PUBLIC KEY-----\0";
		arr[size + 1] = "-----END PUBLIC KEY-----\0";
	}else
	{
		arr[0] = "-----BEGIN RSA PRIVATE KEY-----\0";
		arr[size + 1] = "-----END RSA PRIVATE KEY-----\0";
	}
	
	char *buffer = (char *)malloc((size + 2)*val);
	for(int i = 0; i < (size + 2); i++)
	{
		if(i == 0){
			sprintf(buffer, "%s\n", arr[i]);
		}else{
			sprintf(buffer, "%s%s\n", buffer, arr[i]);
		}
	}
	free(arr);
	
	printf("%s", buffer);
	
	return buffer;
}
