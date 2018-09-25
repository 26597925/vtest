/*
*@email 26597925@qq.com
*author wenford.li 
*/

#include "vl_core.h"

vl_byte_buffer_t *vbb_create(size_t max)
{
	vl_byte_buffer_t *vbb = (vl_byte_buffer_t *)malloc(sizeof(vl_byte_buffer_t));
    memset(vbb, 0, sizeof(vl_byte_buffer_t));
    vbb->capacity = max;
	vbb->length = 0;
    vbb->position = 0;
    vbb->limit = max;
    vbb->buffer = (byte_t*)malloc(vbb->capacity);
    vbb->order = BYTE_ORDER_BIG_ENDIAN;
    return vbb;
}

vl_byte_buffer_t *vbb_wrap(byte_t *value, size_t length)
{
	vl_byte_buffer_t *vbb = (vl_byte_buffer_t *)malloc(sizeof(vl_byte_buffer_t));
    memset(vbb, 0, sizeof(vl_byte_buffer_t));
	vbb->position = 0;
	vbb->length = length;
    vbb->buffer = value;
    vbb->limit = vbb->capacity = length;
    vbb->order = BYTE_ORDER_BIG_ENDIAN;
	return vbb;
}

void vbb_destroy(vl_byte_buffer_t *vbb)
{
	if(vbb->buffer != NULL)
	{
		free(vbb->buffer);
    }
    free(vbb);
}

byte_t *vbb_array(vl_byte_buffer_t *vbb)
{
	return vbb->buffer;
}

size_t vbb_get_len(vl_byte_buffer_t *vbb)
{
	return vbb->length;
}

size_t vbb_capacity(vl_byte_buffer_t *vbb)
{
	return vbb->capacity;
}

vl_byte_order_t vbb_order(vl_byte_buffer_t *vbb)
{
	return vbb->order;
}

void vbb_order_set(vl_byte_buffer_t *vbb, vl_byte_order_t order)
{
	vbb->order = order;
}

byte_t vbb_read_byte(vl_byte_buffer_t *vbb)
{
	size_t pos = vbb->position;
    vbb->position++;
    return vbb->buffer[pos];
}

int16_t vbb_read_short(vl_byte_buffer_t *vbb)
{
	size_t pos = vbb->position;
	assert(pos + 2 <= vbb->limit);
	
	int16_t value;
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        value = (vbb->buffer[pos] & 0xFF) << 8;
        value |= (vbb->buffer[pos + 1] & 0xFF);
    }
    else {
        value = (vbb->buffer[pos + 1] & 0xFF) << 8;
        value |= (vbb->buffer[pos] & 0xFF);
    }
	
    vbb->position += 2;
    return value;
}

int32_t vbb_read_int(vl_byte_buffer_t *vbb)
{
	size_t pos = vbb->position;
	assert((pos + 4) <= vbb->limit);
    
    int32_t value;
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        value = (vbb->buffer[pos] & 0xFF) << 24;
        value |= (vbb->buffer[pos + 1] & 0xFF) << 16;
        value |= (vbb->buffer[pos + 2] & 0xFF) << 8;
        value |= vbb->buffer[pos + 3] & 0xFF;
    }
    else {
        value = (vbb->buffer[pos + 3] & 0xFF) << 24;
        value |= (vbb->buffer[pos + 2] & 0xFF) << 16;
        value |= (vbb->buffer[pos + 1] & 0xFF) << 8;
        value |= vbb->buffer[pos] & 0xFF;
    }
	
    vbb->position += 4;
    return value;
}

int64_t vbb_read_long(vl_byte_buffer_t *vbb)
{
	size_t pos = vbb->position;
	assert((pos + 8) <= vbb->limit);
    
    int64_t value;
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        value = ((int64_t)vbb->buffer[pos] & 0xFF) << 56;
        value |= ((int64_t)vbb->buffer[pos + 1] & 0xFF) << 48;
        value |= ((int64_t)vbb->buffer[pos + 2] & 0xFF) << 40;
        value |= ((int64_t)vbb->buffer[pos + 3] & 0xFF) << 32;
        value |= (vbb->buffer[pos + 4] & 0xFF) << 24;
        value |= (vbb->buffer[pos + 5] & 0xFF) << 16;
        value |= (vbb->buffer[pos + 6] & 0xFF) << 8;
        value |= (vbb->buffer[pos + 7] & 0xFF);
    }
    else {
        value = ((int64_t)vbb->buffer[pos + 7] & 0xFF) << 56;
        value |= ((int64_t)vbb->buffer[pos + 6] & 0xFF) << 48;
        value |= ((int64_t)vbb->buffer[pos + 5] & 0xFF) << 40;
        value |= ((int64_t)vbb->buffer[pos + 4] & 0xFF) << 32;
        value |= (vbb->buffer[pos + 3] & 0xFF) << 24;
        value |= (vbb->buffer[pos + 2] & 0xFF) << 16;
        value |= (vbb->buffer[pos + 1] & 0xFF) << 8;
        value |= (vbb->buffer[pos] & 0xFF);
    }
	
    vbb->position += 8;
	
	return value;
}

void vbb_read_bytes(vl_byte_buffer_t *vbb, byte_t *value, size_t length)
{
	if(length <= 0)
		length = strlen((const char*)value);		
	
    assert((vbb->limit - vbb->position) >= length);
	
    memcpy(value, vbb->buffer + vbb->position, length);
	value[length] = '\0';
	
    vbb->position += length;
}

byte_t *vbb_read_string(vl_byte_buffer_t *vbb)
{
	size_t length = vbb_read_short(vbb);
	
    if (length == 0) 
		return NULL;
	
	if (length == MAX_VALUE) {
		length += vbb_read_int(vbb);
	}
	
	byte_t *value = (byte_t *)malloc(sizeof(byte_t));
	
    vbb_read_bytes(vbb, value, length);
	
	return value;
}

size_t vbb_readable_bytes(vl_byte_buffer_t *vbb)
{
	return vbb->length - vbb->position;
}

void vbb_write_byte(vl_byte_buffer_t *vbb, byte_t value)
{
	assert(vbb->position < vbb->limit);
	
    vbb->buffer[vbb->position] = value;
    vbb->position++;
	vbb->length = vbb->position;
	
    if (vbb->position > vbb->limit) vbb->limit = vbb->position;
}

void vbb_write_short(vl_byte_buffer_t *vbb, int16_t value)
{
	size_t pos = vbb->position;
	assert((pos + 2) <= vbb->limit);
	
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        vbb->buffer[pos] = (value >> 8) & 0xFF;
        vbb->buffer[pos + 1] = value & 0xFF;
    }
    else {
        vbb->buffer[pos + 1] = (value >> 8) & 0xFF;
        vbb->buffer[pos] = value & 0xFF;
    }
	
    vbb->position += 2;
	vbb->length = vbb->position;
}

void vbb_write_int(vl_byte_buffer_t *vbb, int32_t value)
{
	size_t pos = vbb->position;
	assert((pos + 4) <= vbb->limit);
    
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        vbb->buffer[pos] = (value >> 24) & 0xFF;
        vbb->buffer[pos + 1] = (value >> 16) & 0xFF;
        vbb->buffer[pos + 2] = (value >> 8) & 0xFF;
        vbb->buffer[pos + 3] = value & 0xFF;
    }
    else {
        vbb->buffer[pos + 3] = (value >> 24) & 0xFF;
        vbb->buffer[pos + 2] = (value >> 16) & 0xFF;
        vbb->buffer[pos + 1] = (value >> 8) & 0xFF;
        vbb->buffer[pos] = value & 0xFF;
    }
	
	vbb->position += 4;
	vbb->length = vbb->position;
}

void vbb_write_long(vl_byte_buffer_t *vbb, int64_t value)
{
	size_t pos = vbb->position;
	assert((pos + 8) <= vbb->limit);
    
    if (vbb->order == BYTE_ORDER_BIG_ENDIAN) {
        vbb->buffer[pos] = (value >> 56) & 0xFF;
        vbb->buffer[pos + 1] = (value >> 48) & 0xFF;
        vbb->buffer[pos + 2] = (value >> 40) & 0xFF;
        vbb->buffer[pos + 3] = (value >> 32) & 0xFF;
        vbb->buffer[pos + 4] = (value >> 24) & 0xFF;
        vbb->buffer[pos + 5] = (value >> 16) & 0xFF;
        vbb->buffer[pos + 6] = (value >> 8) & 0xFF;
        vbb->buffer[pos + 7] = value & 0xFF;
    }
    else {
        vbb->buffer[pos + 7] = (value >> 56) & 0xFF;
        vbb->buffer[pos + 6] = (value >> 48) & 0xFF;
        vbb->buffer[pos + 5] = (value >> 40) & 0xFF;
        vbb->buffer[pos + 4] = (value >> 32) & 0xFF;
        vbb->buffer[pos + 3] = (value >> 24) & 0xFF;
        vbb->buffer[pos + 2] = (value >> 16) & 0xFF;
        vbb->buffer[pos + 1] = (value >> 8) & 0xFF;
        vbb->buffer[pos] = value & 0xFF;
    }
	
	vbb->position += 8;
	vbb->length = vbb->position;
}

void vbb_write_bytes(vl_byte_buffer_t *vbb, byte_t *value, size_t length)
{		
	if(length <= 0)
		length = strlen((const char*)value);
	
	assert((vbb->position + length) < vbb->limit);
	
    memcpy(vbb->buffer + vbb->position, value, length);
    vbb->position += length;
	vbb->length = vbb->position;
	
    if (vbb->position > vbb->limit) 
		vbb->limit = vbb->position;
}

void vbb_write_string(vl_byte_buffer_t *vbb, byte_t *value, size_t length)
{
	if(length <= 0 && value != NULL)
		length = strlen((const char*)value);
	
	assert((vbb->position + length) < vbb->limit);
	
	if(length == 0 || value == NULL)
	{
		vbb_write_short(vbb, 0x00);
	}else if(length < MAX_VALUE)
	{
		vbb_write_short(vbb, length);
		vbb_write_bytes(vbb, value, length);
	}else
	{
		 vbb_write_short(vbb, MAX_VALUE);
		 vbb_write_int(vbb, length - MAX_VALUE);
		 vbb_write_bytes(vbb, value, length);
	}
}

void vbb_print_number(byte_t *buffer, size_t length)
{
	for(uint32_t i = 0; i < length; i++) {
		printf("%d,", buffer[i]);
	}
	printf("\n");
}

void vbb_print_hex(byte_t *buffer, size_t length)
{
	for(uint32_t i = 0; i < length; i++) {
		printf("0x%02x,", buffer[i]);
	}
	printf("\n");
}

void vbb_print_ascii(byte_t *buffer, size_t length) 
{
	for(uint32_t i = 0; i < length; i++) {
		printf("%c", buffer[i]);
	}
	printf("\n");
}