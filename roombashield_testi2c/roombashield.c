/* roombashield library

*/

#include <avr/io.h>
#include <util/delay.h>
#include "roombashield.h"
#include "basicserial.h"
#include "lm75b.h"
#include "bmp085.h"
#include "hmc5883.h"
#include "lis3dh.h"
#include "l3g4200d.h"



void setup_debug_LEDs() {
    PORTL &= ~( (1<<PL2) | (1<<PL1) | (1<<PL0)); // set outputs to zero just in case
    DDRL  |=  ( (1<<PL2) | (1<<PL1) | (1<<PL0)); // set direction
}

void setup_RGB_LED() {
    //set up Timer 5 for RBG LED
    // Fast PWM (mode 14), inverting
    TCCR5A |= ( (1<<COM5A1) | (1<<COM5A0) | (1<<COM5B1) | (1<<COM5B0) | 
                (1<<COM5C1) | (1<<COM5C0) | (1<<WGM51) );
    // Fast PWM, no prescale
    TCCR5B |= ( (1<<WGM53)  | (1<<WGM52)  | (1<<CS50));
    // set TOP
    ICR5 = 0xFFFF;
    // set initial LED PWM values
    OCR5A = 0x000F; //green
    OCR5B = 0x000F; //blue
    OCR5C = 0x000F; //red
    // set pins to output
    DDRL |= ( (1<<PL5) | (1<<PL4) | (1<<PL3));
}

void set_RGB_LED(uint16_t red, uint16_t green, uint16_t blue) {
    OCR5C = red;
    OCR5A = green;
    OCR5B = blue;
}

void wakeup_Roomba() {
    DDRE |= (1<<PE4);
    Roomba_engage();
    _delay_ms(500);
    Roomba_disengage();
}

void sleep_Roomba() {
    send_serial_Roomba(SCI_PASSIVE_SLEEP);
}

void setup_sensor_temp() {
    setup_i2c();
    temp_pointerwrite();
}

void read_sensor_temp() {
    uint8_t tempdata[2];
    temp_dataread(tempdata); //data placed into array
    if (tempdata[0] & 0x80) {  //check if negative
        send_serial_USB('-');
        send_serial_uint_USB((~tempdata[0]+1));     // 2's compl
        send_serial_USB('.');
    } else {
        send_serial_uint_USB(tempdata[0]);
    }
    send_serial_USB('d');
    send_serial_USB('C');
    send_serial_USB('\r');
    send_serial_USB('\n');
    //send_serial_hex_USB(tempdata[0]); 
    //send_serial_hex_USB(tempdata[1]);
}

void read_bmp085_eeprom() {
    int i;
    uint8_t coolarraybro[22];
    bmp085_read_bytes(0xAA,22,coolarraybro);
    for (i=0;i<11;i++) {
        send_serial_hex_USB(coolarraybro[2*i]);
        send_serial_USB(' ');
        send_serial_hex_USB(coolarraybro[2*i+1]);
        if (i==10) send_serial_USB('.');
        send_serial_USB('\r');
        send_serial_USB('\n');
    }
}

/*
void read_hmc5883_registers() {
    hmc5883_setpointer(0x00);
    int i;
    uint8_t coolarraybro[6];
    hmc5883_read_bytes(0x06,6,coolarraybro);
    for (i=0;i<6;i++) {
        send_serial_hex_USB(coolarraybro[i]);
        send_serial_USB('\r');
        send_serial_USB('\n');
    }
    send_serial_USB('.');
    send_serial_USB('\r');
    send_serial_USB('\n');
}
/*/

void read_lis3dh_registers() {
    int i,j=0;
    uint8_t coolarraybro[64];
    lis3dh_read_bytes(0x80,64,coolarraybro);    // addr 0x00 | 0x80 for autoincr
    for (i=0;i<64;i=i+8) {
        for (j=0;j<8;j++) {
            send_serial_hex_USB(coolarraybro[i+j]);
            send_serial_USB(' ');
        }
        if (i==56) send_serial_USB('.');
        send_serial_USB('\r');
        send_serial_USB('\n');
    }
}

void read_lis3dh_data() {
    int i;
    uint8_t coolarraybro[6];
    lis3dh_read_bytes((0x28|0x80),6,coolarraybro);
    for (i=0;i<6;i++) {
        send_serial_hex_USB(coolarraybro[i]);
        send_serial_USB(' ');
    }
    send_serial_USB('.');
    send_serial_USB('\r');
    send_serial_USB('\n');
}

void read_l3g4200d_registers() {
    int i,j=0;
    uint8_t coolarraybro[64];
    l3g4200d_read_bytes(0x80,64,coolarraybro);    // addr 0x00 | 0x80 for autoincr
    for (i=0;i<64;i=i+8) {
        for (j=0;j<8;j++) {
            send_serial_hex_USB(coolarraybro[i+j]);
            send_serial_USB(' ');
        }
        if (i==56) send_serial_USB('.');
        send_serial_USB('\r');
        send_serial_USB('\n');
    }
}

void read_l3g4200d_data() {
    int i;
    uint8_t coolarraybro[6];
    l3g4200d_read_bytes((0x28|0x80),6,coolarraybro);
    for (i=0;i<6;i++) {
        send_serial_hex_USB(coolarraybro[i]);
        send_serial_USB(' ');
    }
    send_serial_USB('.');
    send_serial_USB('\r');
    send_serial_USB('\n');
}

void setup_standard() {
    setup_serial_USB(UBRR57600);
    
    //Roomba baud rate reduction
    setup_serial_Roomba(UBRR57600);
    wakeup_Roomba();
    send_serial_Roomba(SCI_START_PASSIVE);
    _delay_ms(20);
    send_serial_Roomba(SCI_BAUD);
    send_serial_Roomba(SCI_BAUD_19200);
    _delay_ms(100);
    setup_serial_Roomba(UBRR19200);
    
    //Roomba to full control
    send_serial_Roomba(SCI_PASSIVE_TO_SAFE);
    _delay_ms(20);
    send_serial_Roomba(SCI_SAFE_TO_FULL);
    _delay_ms(20);
    
    //setup_sensor_temp();
    TWBR = 72;   //for i2c
    
    setup_lis3dh();
    setup_l3g4200d();
    
    //leave for last
    setup_debug_LEDs();
    setup_RGB_LED();
}
  