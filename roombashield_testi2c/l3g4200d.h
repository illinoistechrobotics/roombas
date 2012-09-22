
#ifndef _l3g4200d_h__
#define _l3g4200d_h__

#include <avr/io.h>

#ifndef F_I2C
#define F_I2C               100000
#endif

#define TWI_SLA_L3G4200D    0b11010010
#define MAX_ITER	        200

#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */
int l3g4200d_write_byte(uint8_t, uint8_t);
int l3g4200d_read_bytes(uint8_t, int, uint8_t*);

void setup_l3g4200d();

#ifdef __cplusplus
} // extern "C"
#endif

#endif


