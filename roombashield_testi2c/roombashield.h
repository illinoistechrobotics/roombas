
#ifndef _roombashield_h__
#define _roombashield_h__

#include <avr/io.h>

#define SCI_START_PASSIVE       128
#define SCI_BAUD                129
#define SCI_BAUD_19200          7
#define SCI_PASSIVE_TO_SAFE     130
#define SCI_FULL_TO_SAFE        131
#define SCI_SAFE_TO_FULL        132
#define SCI_PASSIVE_SLEEP       133


// use macros masquerading as functions
// debug LEDs
#define led_red_off()  PORTL &= ~(1<<PL2)
#define led_red_on()   PORTL |=  (1<<PL2)
#define led_red_flip() PORTL ^=  (1<<PL2)
#define led_green_off()  PORTL &= ~(1<<PL1)
#define led_green_on()   PORTL |=  (1<<PL1)
#define led_green_flip() PORTL ^=  (1<<PL1)
#define led_blue_off()  PORTL &= ~(1<<PL0)
#define led_blue_on()   PORTL |=  (1<<PL0)
#define led_blue_flip() PORTL ^=  (1<<PL0)
// Roomba detect line
#define Roomba_engage()    PORTE |= (1<<PE4)
#define Roomba_disengage() PORTE &= ~(1<<PE4)
// shorthand



#ifdef __cplusplus
extern "C"{
#endif


/* prototypes here */

void setup_debug_LEDs() ;
void setup_RGB_LED() ;
void set_RGB_LED(uint16_t, uint16_t, uint16_t);

void wakeup_Roomba();
void sleep_Roomba();

void setup_sensor_temp();
void read_sensor_temp();

void read_bmp085_eeprom();

void read_hmc5883_registers();

void read_lis3dh_registers();
void read_lis3dh_data();

void read_l3g4200d_registers();
void read_l3g4200d_data();

void setup_standard();

#ifdef __cplusplus
} // extern "C"
#endif

#endif


