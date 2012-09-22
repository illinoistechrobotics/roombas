
#ifndef _hmc5883_h__
#define _hmc5883_h__

#include <avr/io.h>

#ifndef F_I2C
#define F_I2C               100000
#endif

#define TWI_SLA_HMC5883     0b00111100    // 0x3C
#define MAX_ITER	        200

#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */
//void setup_i2c();
int hmc5883_setpointer(uint8_t);
int hmc5883_read_bytes(uint8_t, int, uint8_t*);



#ifdef __cplusplus
} // extern "C"
#endif

#endif


