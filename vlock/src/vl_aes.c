#include "vl_core.h"

static char *vl_padding_buf(char *buf, int size, int *final_size) {
	char *padding_buf = NULL;
	int pidding_size = 0;

	pidding_size = AES_BLOCK_SIZE - (size % AES_BLOCK_SIZE);
	*final_size = size + pidding_size + 1;

	padding_buf = (char *)malloc(*final_size);
	memcpy( padding_buf, buf, size);

	if (pidding_size!=0) {
		for (int i = size; i < *final_size; i++ ) {
			padding_buf[i] = pidding_size;
		}
	}
	padding_buf[*final_size - 1] = '\0';
	return ret;
}

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
	char *padding_buf = NULL;

	padding_buf = vl_padding_buf();
		
	return len;
}

int vl_aes_decrypt(vl_aes_t *va, unsigned char *in, int in_len, unsigned char *out)
{
	
	return len;
}

void vl_aes_destory(vl_aes_t *va)
{
	free(va);
}