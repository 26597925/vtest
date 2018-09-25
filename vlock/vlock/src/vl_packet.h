/*
*@email 26597925@qq.com
*author wenford.li 
*/

#ifndef VL_PACKET_H_
#define VL_PACKET_H_

#include "vl_core.h"

#define FLAG_CRYPTO 1
#define FLAG_COMPRESS 2
#define FLAG_BIZ_ACK 4
#define FLAG_AUTO_ACK 8
#define FLAG_JSON_BODY 16

#define HEADER_LEN 13
#define HB_PACKET_BYTE -33

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

typedef enum {
	HEARTBEAT = 1,
	HANDSHAKE = 2,
	FAST_CONNECT = 3,
	OPEN_DOOR = 4,
	OK = 5,
	ERROR = 6,
	ACK = 7
} vp_command_t;

typedef struct {
	byte_t cmd;
	byte_t *body;
	size_t body_length;
	short cc;
	byte_t flags;
	int session_id;
	byte_t lrc;
} vl_packet_t;

vl_packet_t *vp_create(byte_t cmd);

void vp_add_session_id(vl_packet_t *vp, int session_id);

void vp_add_flags(vl_packet_t *vp, byte_t flags);

int  vp_has_flag(vl_packet_t *vp, byte_t flag);

byte_t *vp_get_body(vl_packet_t *vp);

size_t vp_get_body_length(vl_packet_t *vp);

void vp_set_body(vl_packet_t *vp, byte_t *body, size_t body_length);

short vp_calc_check_code(vl_packet_t *vp);

void vp_set_calc_check_code(vl_packet_t *vp);

int vp_valid_check_code(vl_packet_t *vp);

byte_t vp_calc_lrc(vl_packet_t *vp);

void vp_set_calc_lrc(vl_packet_t *vp);

int vp_valid_lrc(vl_packet_t *vp);

void vp_decode_packet(vl_packet_t *vp, vl_byte_buffer_t *in_buffer);

void vp_encode_packet(vl_packet_t *vp, vl_byte_buffer_t *out_buffer);

#endif /*VL_PACKET_H_*/