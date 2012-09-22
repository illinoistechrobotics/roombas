
#ifndef _lis3dh_h__
#define _lis3dh_h__

#include <avr/io.h>

#ifndef F_I2C
#define F_I2C               100000
#endif

#define TWI_SLA_LIS3DH      0b00110010
#define MAX_ITER	        200

#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */
int lis3dh_write_byte(uint8_t, uint8_t);
int lis3dh_read_bytes(uint8_t, int, uint8_t*);

void setup_lis3dh();

#ifdef __cplusplus
} // extern "C"
#endif

#endif


