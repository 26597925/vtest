/*
*@email 26597925@qq.com
*author wenford.li 
*/

#include "vl_core.h"

/*
length	int	4	表示body的长度
cmd	byte	1	表示消息协议类型
checkcode	short	2	是根据body生成的一个校验码
flags	byte	1	表示当前包启用的特性，比如是否启用加密，是否启用压缩
sessionId	int	4	消息会话标识用于消息响应
lrc	byte	1	纵向冗余校验，用于校验header
*/
//{  vender='CS', imei='a2sd2rsd5ers32s', tel='198293891839', ver='V1.0', iv=[121, 80, 34, 109, -116, 93, 18, 20, -111, -90, -60, -106, -93, -89, 50, -34], clientKey=[120, 67, 81, 53, 85, -60, -78, -58, 11, 75, 40, 86, 34, 26, 4, -70], heartbeat=0, timestamp=1505553851134, 
//packet={cmd=2, body=0, cc=0, flags=1, sessionId=1, lrc=0}}

vl_packet_t *vp_create(byte_t cmd)
{
	vl_packet_t *vp = (vl_packet_t *)malloc(sizeof(vl_packet_t));
    memset(vp, 0, sizeof(vl_packet_t));
	vp->cmd = cmd;
	vp->body = NULL;
	vp->body_length = 0;
	vp->cc = 0;
	vp->flags = 1;
	vp->session_id = 0;
	vp->lrc = 0;
	return vp;
}

void vp_add_session_id(vl_packet_t *vp, int session_id)
{
	vp->session_id = session_id;
}

void vp_add_flags(vl_packet_t *vp, byte_t flag)
{
	vp->flags |= flag;
}

int vp_has_flag(vl_packet_t *vp, byte_t flag)
{
	return (vp->flags & flag) != 0 ? 1 : 0;
}

byte_t *vp_get_body(vl_packet_t *vp)
{
	return vp->body;
}

size_t vp_get_body_length(vl_packet_t *vp)
{
	return vp->body_length;
}

void vp_set_body(vl_packet_t *vp, byte_t *body, size_t body_length)
{
	assert(body != NULL);
	
	if(body_length <= 0)
		body_length = strlen((const char*)body);
	
	vp->body = body;
	vp->body_length = body_length;
}

short vp_calc_check_code(vl_packet_t *vp)
{
	short check_code = 0;
	for (int i = 0; i < vp->body_length; i++) {
		check_code += (vp->body[i] & 0x0ff);
	}
	return check_code;
}

void vp_set_calc_check_code(vl_packet_t *vp)
{
	vp->cc = vp_calc_check_code(vp);
}

byte_t vp_calc_lrc(vl_packet_t *vp)
{
	vl_byte_buffer_t *vbb = vbb_create(HEADER_LEN - 1);
	vbb_write_int(vbb, vp->body_length);
	vbb_write_byte(vbb, vp->cmd);
	vbb_write_short(vbb, vp->cc);
	vbb_write_byte(vbb, vp->flags);
	vbb_write_int(vbb, vp->session_id);
	
	byte_t *buffer = vbb_array(vbb);
	byte_t lrc = 0;
	for (int i = 0; i < vbb_get_len(vbb); i++) {
		lrc ^= buffer[i];
	}
	return lrc;
}

void vp_set_calc_lrc(vl_packet_t *vp)
{
	vp->lrc = vp_calc_lrc(vp);
}

int vp_valid_check_code(vl_packet_t *vp)
{
	return vp_calc_check_code(vp) == vp->cc;
}

int vp_valid_lrc(vl_packet_t *vp)
{
	return (vp->lrc ^ vp_calc_lrc(vp)) == 0;
}

void vp_decode_packet(vl_packet_t *vp, vl_byte_buffer_t *in_buffer)
{
	size_t body_length = vbb_read_int(in_buffer);
	
	byte_t cmd = vbb_read_byte(in_buffer);
	
	/*size_t readable_bytes = vbb_readable_bytes(in_buffer);
	
	if (readable_bytes < (body_length + HEADER_LEN)) {
		return;
	}*/
	
	vp->cmd = cmd;
	vp->body_length = body_length;
	vp->cc = vbb_read_short(in_buffer);
	vp->flags = vbb_read_byte(in_buffer);
	vp->session_id = vbb_read_int(in_buffer);
	vp->lrc = vbb_read_byte(in_buffer);
	
	if (body_length > 0) {
		if(vp->body == NULL)
			vp->body = (byte_t *)malloc(sizeof(byte_t));
		
		vbb_read_bytes(in_buffer, vp->body, body_length);
	}
}

void vp_encode_packet(vl_packet_t *vp, vl_byte_buffer_t *out_buffer)
{
	if (vp->cmd == HEARTBEAT) {
		vbb_write_byte(out_buffer, HB_PACKET_BYTE);
	} else {
		vbb_write_int(out_buffer, vp->body_length);
		vbb_write_byte(out_buffer, vp->cmd);
		vbb_write_short(out_buffer, vp->cc);
		vbb_write_byte(out_buffer, vp->flags);
		vbb_write_int(out_buffer, vp->session_id);
		vbb_write_byte(out_buffer, vp->lrc);
		if (vp->body_length > 0) {
			vbb_write_bytes(out_buffer, vp->body, vp->body_length);
		}
	}
}