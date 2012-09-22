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

uint8_t fromRoomba_check(void) {
    return (UCSR1A & (1<<RXC1));
}

void send_serial_USB( uint8_t tosend) {
    while ( ! (UCSR0A & (1<<UDRE0)) )
            /*nothing*/;
    UDR0 = tosend;
}

void send_serial_Roomba( uint8_t tosend) {
    while ( ! (UCSR1A & (1<<UDRE1)) )
            /*nothing*/;
    UDR1 = tosend;
}

void send_serial_hex_USB( uint8_t value) {
    send_serial_USB('0');
    send_serial_USB('x');
    send_serial_USB(toASCII(value >> 4));
    send_serial_USB(toASCII(value & 0x0f));
}

void setup_serial_USB( unsigned int ubrr){
    /* Set baud rate */
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void setup_serial_Roomba( unsigned int ubrr){
    /* Set baud rate */
    UBRR1H = (unsigned char) (ubrr>>8);
    UBRR1L = (unsigned char) ubrr;
    /* Enable receiver and transmitter */
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);
    /* Set frame format: 8data, 1stop bit */
    UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
}

void uint2ASCII(uint8_t value, uint8_t *buf) {
    uint8_t tens, hundreds = 0;
    while (value >= 100) {
        hundreds++;
        value = value - 100;
    }
    *buf = hundreds+48;
    *buf++;
    while (value >= 10) {
        tens++;
        value = value - 10;
    }
    *buf = tens+48;
    *buf++;
    *buf = value+48;   // remaining is ones place
}

void send_serial_uint_USB(uint8_t value) {
    uint8_t buckets[3];
    uint2ASCII(value,buckets);
    send_serial_USB(buckets[0]);
    send_serial_USB(buckets[1]);
    send_serial_USB(buckets[2]);
}

//eof
