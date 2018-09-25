#include "vl_core.h"

vl_aes_t *vl_aes_init(unsigned char *key, unsigned char *iv)
{	
	vl_aes_t *va = (vl_aes_t *)malloc(sizeof(vl_aes_t));
    memset(va, 0, sizeof(vl_aes_t));
	va->key = key;
	va->iv = iv;
	
	return va;
}

int vl_aes_encrypt(vl_aes_t *va, unsigned char *in, int in_len, unsigned char *out)
{
	int len = 0;
	int out_len = 0;
	
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, va->key, va->iv);
	EVP_EncryptUpdate(&ctx, out + len, &out_len, in + len, in_len);
	
    len += out_len;
	int test = in_len>>4;  
    if(in_len != test<<4){  
        EVP_EncryptFinal_ex(&ctx, out + len, &out_len);    
        len += out_len;  
    }
	
    //EVP_CIPHER_CTX_cleanup(&ctx);
		
	return len;
}

int vl_aes_decrypt(vl_aes_t *va, unsigned char *in, int in_len, unsigned char *out)
{
	EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
	
	EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, va->key, va->iv);   
    int len = 0; 
    int out_len = 0;

	printf(" ");
    EVP_DecryptUpdate(&ctx, out+len, &out_len, in + len, in_len);  
    len += out_len;  
       
    EVP_DecryptFinal_ex(&ctx, out + len, &out_len);    
    len += out_len;  
    out[len] = 0;
	
   // EVP_CIPHER_CTX_cleanup(&ctx);

	return len;
}

void vl_aes_destory(vl_aes_t *va)
{
	free(va);
}