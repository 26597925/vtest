/*
*@email 26597925@qq.com
*author wenford.li 
*/

#ifndef VL_BYTE_BUFFER_H_
#define VL_BYTE_BUFFER_H_

#include "vl_core.h"

typedef enum {
    BYTE_ORDER_BIG_ENDIAN = 0,
    BYTE_ORDER_LITTLE_ENDIAN = 1
} vl_byte_order_t;

typedef struct {
    size_t limit;
    size_t position;
    size_t capacity;
	size_t length;
    byte_t *buffer;
    vl_byte_order_t order;
} vl_byte_buffer_t;

vl_byte_buffer_t *vbb_create(size_t max);

vl_byte_buffer_t *vbb_wrap(byte_t *value, size_t length);

void vbb_destroy(vl_byte_buffer_t *vbb);

byte_t *vbb_array(vl_byte_buffer_t *vbb);

size_t vbb_get_len(vl_byte_buffer_t *vbb);

size_t vbb_capacity(vl_byte_buffer_t *vbb);

vl_byte_order_t vbb_order(vl_byte_buffer_t *vbb);

void vbb_order_set(vl_byte_buffer_t *vbb, vl_byte_order_t order);

byte_t vbb_read_byte(vl_byte_buffer_t *vbb);

int16_t vbb_read_short(vl_byte_buffer_t *vbb);

int32_t vbb_read_int(vl_byte_buffer_t *vbb);

int64_t vbb_read_long(vl_byte_buffer_t *vbb);

void vbb_read_bytes(vl_byte_buffer_t *vbb, byte_t *value, size_t length);

byte_t *vbb_read_string(vl_byte_buffer_t *vbb);

size_t vbb_readable_bytes(vl_byte_buffer_t *vbb);

void vbb_write_byte(vl_byte_buffer_t *vbb, byte_t value);

void vbb_write_short(vl_byte_buffer_t *vbb, int16_t value);

void vbb_write_int(vl_byte_buffer_t *vbb, int32_t value);

void vbb_write_long(vl_byte_buffer_t *vbb, int64_t value);

void vbb_write_bytes(vl_byte_buffer_t *vbb, byte_t *value, size_t length);

void vbb_write_string(vl_byte_buffer_t *vbb, byte_t *value, size_t length);

void vbb_print_number(byte_t *buffer, size_t length);

void vbb_print_hex(byte_t *buffer, size_t length);

void vbb_print_ascii(byte_t *buffer, size_t length);

#endif /*VL_BYTE_BUFFER_H_*/