
#ifndef _lm75b_h__
#define _lm75b_h__

#include <avr/io.h>

#ifndef F_I2C
#define F_I2C               100000
#endif

#define TWI_SLA_LM75B       0b10011110
#define MAX_ITER	        200

#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */
void setup_i2c();
int temp_pointerwrite( void );
int temp_dataread(uint8_t*);
void eighths(uint8_t);




#ifdef __cplusplus
} // extern "C"
#endif

#endif


