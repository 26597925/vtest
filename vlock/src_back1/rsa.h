typedef enum {
   RSA_PUBLIC = 0,
   RSA_PRIVATE = 1
} rsa_key_type_t;

RSA *rsa_create(unsigned char *key, rsa_key_type_t key_type);

int rsa_public_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted);

int rsa_public_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted);

int rsa_private_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted);

int rsa_private_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted);

char *format_key(char *key, rsa_key_type_t key_type);
