/*
 *
 * Copyright (c) wenford.li
 * wenford.li <26597925@qq.com>
 *
 */

#include "vl_core.h"

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
	*/
	
	/*byte_t cc[1024];
	char aa[] = {90, 34, -123, 66, -42, -52, -55, -79, -56, -26, -112, 1, -16, -24, -98, -124, 26, -34, -124, -24, 3, -109, -88, -56, -60, 40, 1, 5, -114, -107, 61, 122, -43, 109, 92, 4, 83, -86, 123, -106, -36, -80, 52, 77, 65, 20, 1, -21, -77, 49, -46, -86, 4, 43, 78, 52, -99, -90, 57, 31, 23, -90, 121, 73, -85, 63, -109, 127, -28, -98, -19, -58, -8, -56, -46, 65, -104, -2, -104, 37, 28, -17, 100, -9, -124, -54, 10, 24, 87, -48, -54, -111, -109, -10, 69, 93, -56, -38, -117, -35, -105, 86, -86, 54, -56, 61, -93, -56, -119, -68, 36, -41, 34, -15, -113, 90, -32, -100, -94, -102, -44, 81, 101, -112, 84, -48, -103, 73, -14, 7, -33, 118, 42, 97, 124, 76, -102, -79, -23, 73, -32, -63, -119, -77, -49, -85, 126, 9, -31, 33, -59, -67, -84, -56, 51, 36, -78, -51, -125, 6, 67, 57, 86, -123, -26, -128, -75, 77, -57, -126, -41, 15, -52, 10, 119, 50, 114, 117, -30, 1, -128, 125, -32, 51, 58, 122, -73, 112, -76, 0, -50, 99, -115, -11, 44, -3, 107, -38, 80, -33, 84, -122, 122, -49, 1, 126, -36, 77, -104, 22, 94, 99, 32, 114, 79, 103, -22, -9, -105, -110, -22, -81, -64, 95, 6, 49, -94, 6, 126, 119, 6, -122, -91, -21, 60, 76, 7, 103, 89, 48, -22, -6, 30, -24, 98, 11, -71, 51, -49, -69, 21, 57, -100, -4, 74, -31};
	char *privateKey = format_key(PRIVATEKEY, RSA_PRIVATE);
	ret = rsa_private_decrypt((byte_t *)aa, sizeof(aa), (byte_t *)privateKey, cc);
	printf("==ret:%d=== \n", ret);
	printf("==ret:%p=== \n", cc);

	
	char bb[1024];
	char cc[1024];
	
	printf("==len:%d=== \n", (int)strlen(aa));
	int decrypted_length =  rsa_public_encrypt((unsigned char *)aa, strlen(aa), (unsigned char *)publicKey, (unsigned char *)bb);
	printf("==ret:%d=== \n", decrypted_length);
	//printf("==ret:%s=== \n", bb);
	
	printf("===%s=== \n", vbb_read_string(vbb));
	
	printf("===%s=== \n", vbb_read_string(vbb));
		
	vl_byte_buffer_t *vbb = vbb_wrap(cc, ret);
	vbb_print_hex(vbb_array(vbb), vbb_get_len(vbb));*/
		
	char *value = "1.1.0";
	vl_byte_buffer_t *put_vbb = vbb_create(100);
	vbb_write_string(put_vbb, (byte_t *)value, 0);
	value = "asdasdasdsad";
	vbb_write_string(put_vbb, (byte_t *)value, 0);
	
	vl_byte_buffer_t *get_vbb = vbb_wrap(vbb_array(put_vbb), vbb_get_len(put_vbb));
	printf("===%s=== \n", vbb_read_string(get_vbb));
	printf("===%s=== \n", vbb_read_string(get_vbb));
		
	vbb_print_number(vbb_array(get_vbb), vbb_get_len(get_vbb));
	/*
	byte_t dd[1024];
	char *publicKey = format_key(PUBLICKEY, RSA_PUBLIC);
	int decrypted_length =  rsa_public_encrypt(vbb_array(put_vbb), vbb_get_len(put_vbb), (byte_t *)publicKey, dd);
	printf("==ret:%d=== \n", decrypted_length);
	vbb_print_number(dd, decrypted_length);*/
	
	byte_t clientKey[] = {-41, 92, 63, -7, -117, -70, 54, 112, 62, -7, -102, -115, 15, -44, 64, -26};
	byte_t iv[] = {77, -33, -11, 59, -114, -8, -36, -108, -10, 84, 122, 41, 122, -104, -93, 77};
		
	vl_byte_buffer_t *body = vbb_create(256);
	value = "CS";//vender
	vbb_write_string(body, (byte_t *)value, 0);
	value = "a2sd2rsd5ers32s";//imei
	vbb_write_string(body, (byte_t *)value, 0);
	value = "198293891839";//tel
	vbb_write_string(body, (byte_t *)value, 0);
	value = "V1.0";//ver
	vbb_write_string(body, (byte_t *)value, 0);
	vbb_write_string(body, iv, 16);
	vbb_write_string(body, clientKey, 16);
	vbb_write_int(body, 1000);
	vbb_write_long(body, 1231433445454);
	//vbb_print_number(vbb_array(body), vbb_get_len(body));
	
	byte_t data[1024];
	char *publicKey = format_key(PUBLICKEY, RSA_PUBLIC);
	int decrypted_length =  rsa_public_encrypt(vbb_array(body), vbb_get_len(body), (byte_t *)publicKey, data);
	
	//vbb_print_number(data, decrypted_length);
	
	vl_packet_t *vp = vp_create(HANDSHAKE);
	vp_add_session_id(vp, 1);
	vp_set_body(vp, data, decrypted_length);
	vp_set_calc_check_code(vp);
	vp_set_calc_lrc(vp);
	
	vl_byte_buffer_t *content = vbb_create(1024);
	vp_encode_packet(vp, content);
	
	//vbb_print_number(vbb_array(content), vbb_get_len(content));
	
	struct sockaddr_in servaddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,0x00,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.16.9", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	ret = write(sockfd, vbb_array(content), vbb_get_len(content));
	//sleep(10000000);
	
	byte_t buf[1024];
	
	ret = read(sockfd, buf, 1024);
	
	vbb_print_number(buf, ret);
	
	vl_byte_buffer_t *rvbb = vbb_wrap(buf, ret);
	vl_packet_t *rvp = vp_create(HANDSHAKE);
	vp_decode_packet(rvp, rvbb);
	
	vbb_print_number(vp_get_body(rvp), vp_get_body_length(rvp));
	
	unsigned char* decrypt_string;
	decrypt_string = (unsigned char *)malloc(sizeof(unsigned char));
	
	
	vl_aes_t *va = vl_aes_init(clientKey, iv);
	ret = vl_aes_decrypt(va, vp_get_body(rvp), vp_get_body_length(rvp), decrypt_string);
	vbb_print_number(decrypt_string, ret);
	
	vl_byte_buffer_t *vbb = vbb_wrap(decrypt_string, ret);
	vbb_read_string(vbb);
	printf("==ret:%d=== \n", vbb_read_int(vbb));
	printf("==ret:%s=== \n", vbb_read_string(vbb));
	
	
	/*byte_t cc[1024];
	char *privateKey = format_key(PRIVATEKEY, RSA_PRIVATE);
	printf("==ret:%ld=== \n", vp_get_body_length(rvp));
	ret = rsa_private_decrypt(vp_get_body(rvp), vp_get_body_length(rvp), (byte_t *)privateKey, cc);
	printf("==ret:%d=== \n", ret);
	
	unsigned char* decrypt_string;
	decrypt_string = (unsigned char *)malloc(sizeof(unsigned char));
	
	byte_t clientKey[] = {-41, 92, 63, -7, -117, -70, 54, 112, 62, -7, -102, -115, 15, -44, 64, -26};
	byte_t iv[] = {77, -33, -11, 59, -114, -8, -36, -108, -10, 84, 122, 41, 122, -104, -93, 77};
	byte_t aa[] = {227,130,227,71,151,224,75,226,223,26,233,248,74,63,144,220,153,141,15,146,211,235,113,226,254,144,149,139,240,190,170,223,131,228,85,137,213,210,169,240,42,178,22,152,56,128,24,46,213,38,125,106,182,253,43,2,129,254,171,40,30,134,242,113,246,181,200,199,102,79,208,120,235,133,5,203,232,211,174,239};
	vl_aes_t *va = vl_aes_init(clientKey, iv);

	ret = vl_aes_decrypt(va, aa,  strlen((const char*)aa), decrypt_string);
	
	printf("============%d\n", ret);
	vbb_print_number(decrypt_string, ret);
	
	vl_byte_buffer_t *vbb = vbb_wrap(decrypt_string, ret);
	vbb_read_string(vbb);
	printf("==ret:%d=== \n", vbb_read_int(vbb));
	printf("==ret:%s=== \n", vbb_read_string(vbb));*/
		
	close(sockfd);
	
	return ret;
}
