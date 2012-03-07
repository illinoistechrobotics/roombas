/*  bare-bones serial library for AVR
    written for 16 MHz (see defines in basicserial.h)
*/
#include "basicserial.h"

uint8_t toASCII(uint8_t nibble) {
    // returns hex char for nibble
    if (nibble < 10) {
        return (nibble + 48);     // numbers < 10
    } else {
        return (nibble + 55);     // ABCDEF
    }
}

uint8_t fromUSB_check(void) {
    return (UCSR0A & (1<<RXC0));
}

void toUSB_send( uint8_t tosend) {
    while ( ! (UCSR0A & (1<<UDRE0)) )
            /*nothing*/;
    UDR0 = tosend;
}

void toUSB_sendhex8( uint8_t value) {
    toUSB_send('0');
    toUSB_send('x');
    toUSB_send(toASCII(value >> 4));
    toUSB_send(toASCII(value & 0x0f));
}

void toUSB_init( unsigned int ubrr){
    /* Set baud rate */
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}