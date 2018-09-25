/*
*@email 26597925@qq.com
*author wenford.li 
*/

#ifndef VL_AES_H_
#define VL_AES_H_

#include "vl_core.h"

typedef struct {
	unsigned char *key;
	unsigned char *iv;
} vl_aes_t;

vl_aes_t *vl_aes_init(unsigned char *key, unsigned char *iv);

int vl_aes_encrypt(vl_aes_t *va, unsigned char *in, int in_len, unsigned char *out);

int vl_aes_decrypt(vl_aes_t *va, unsigned char *in, int in_len, unsigned char *out);

void vl_aes_destory(vl_aes_t *va);

#endif /*VL_AES_H_*/