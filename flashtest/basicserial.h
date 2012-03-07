/* MYUBRR is the baud rate setting.
   For 16 MHz,  baud    -> UBRR     error
                9600    -> 103      0.2%
                19200   -> 51       0.2%
                57600   -> 16       2.1%
                115200  -> 8        -3.5%   */
#define UBRR9600 103
#define UBRR19200 51
#define UBRR57600 16
#define UBRR115200 8

#define fromUSB_get() UDR0

#ifndef _basicserial_h__
#define _basicserial_h__

#include <avr/io.h>

#ifdef __cplusplus
extern "C"{
#endif


uint8_t toASCII(uint8_t) ;

void toUSB_send( uint8_t ) ;

uint8_t fromUSB_check(void) ;

void toUSB_sendhex8( uint8_t ) ;

void toUSB_init( unsigned int );

#ifdef __cplusplus
} // extern "C"
#endif

#endif


