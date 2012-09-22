
#ifndef _basicserial_h__
#define _basicserial_h__

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

#include <avr/io.h>

#ifdef __cplusplus
extern "C"{
#endif


uint8_t toASCII(uint8_t) ;

void send_serial_USB( uint8_t ) ;
void send_serial_Roomba( uint8_t ) ;


uint8_t fromUSB_check(void) ;
uint8_t fromRoomba_check(void) ;


void send_serial_hex_USB( uint8_t ) ;

void setup_serial_USB( unsigned int );
void setup_serial_Roomba( unsigned int );

void uint2ASCII(uint8_t, uint8_t*);
void send_serial_uint_USB(uint8_t);


#ifdef __cplusplus
} // extern "C"
#endif

#endif


