/*
*@email 26597925@qq.com
*author wenford.li 
*/

#ifndef VL_RSA_H_
#define VL_RSA_H_

#include "vl_core.h"

typedef enum {
   RSA_PUBLIC = 0,
   RSA_PRIVATE = 1
} rsa_key_type_t;

RSA *rsa_create(byte_t *key, rsa_key_type_t key_type);

int rsa_public_encrypt(byte_t *data, int data_len, byte_t *key, byte_t *encrypted);

int rsa_public_decrypt(byte_t *enc_data, int data_len, byte_t *key, byte_t *decrypted);

int rsa_private_encrypt(byte_t *data, int data_len, byte_t *key, byte_t *encrypted);

int rsa_private_decrypt(byte_t *enc_data, int data_len, byte_t *key, byte_t *decrypted);

char *format_key(char *key, rsa_key_type_t key_type);

#endif /*VL_RSA_H_*/