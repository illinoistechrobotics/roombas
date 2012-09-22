
#ifndef _bmp085_h__
#define _bmp085_h__

#include <avr/io.h>

#ifndef F_I2C
#define F_I2C               100000
#endif

#define TWI_SLA_BMP085      0b11101110    // 0xEE
#define MAX_ITER	        200

#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */
//void setup_i2c();
int bmp085_read_bytes(uint8_t, int, uint8_t*);


#ifdef __cplusplus
} // extern "C"
#endif

#endif


