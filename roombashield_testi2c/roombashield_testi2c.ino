

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "roombashield.h"
#include "basicserial.h"
  
int main(void)
{
  
  setup_standard();
  
  while (1) {
    uint8_t c;
    if (fromUSB_check())     // if serial from USB available
    {
        c = fromUSB_get();               // serial value
        if (c=='r')
        {
            led_red_flip();
            set_RGB_LED(0xFFFF,0x0000,0x0000);
        } else if (c=='g') {
            led_green_flip();
            set_RGB_LED(0x0000,0xFFFF,0x0000);
        } else if (c=='b') {
            led_blue_flip();
            set_RGB_LED(0x0000,0x0000,0xFFFF);
        } else if (c=='s') {
            sleep_Roomba();
        } else if (c=='t') {
            read_sensor_temp();
        } else if (c=='p') {
            read_bmp085_eeprom();
        } else if (c=='m') {
            //read_hmc5883_registers();
        } else if (c=='l') {
            read_lis3dh_registers();
        } else if (c=='a') {
            read_lis3dh_data();
        } else if (c=='h') {
            read_l3g4200d_registers();
        } else if (c=='y') {
            read_l3g4200d_data();
        }
    }
    //read_lis3dh_data();
    _delay_ms(20);
  }  
}