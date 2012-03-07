/* adapted from http://www.rocketnumbernine.com/2009/04/26/using-spi-on-an-avr-1
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "at45db.h"
#include "basicserial.h"
  
int main(void)
{
  
  toUSB_init(UBRR57600);
  AT45_init();

  while (1) {
    uint8_t c;
    if (fromUSB_check())     // if serial from USB available
    {
        c = fromUSB_get();               // serial value
        if (c=='d')
        {
            AT45_readdevdata();
        } else if (c=='r')
        {
            AT45_reset();
        } else if (c=='s')
        {
            toUSB_sendhex8(AT45_readstatus());
        } else if (c=='e')
        {
            toUSB_send('e');
            toUSB_send('r');
            toUSB_send('a');
            toUSB_send('s');
            toUSB_send('i');
            toUSB_send('n');
            toUSB_send('g');
            toUSB_send('-');
            //AT45_initsectorerase(0xf);
            AT45_pageerase(TESTPAGE);
            while (!(AT45_readstatus() & 0x80));
            toUSB_send('d');
            toUSB_send('o');
            toUSB_send('n');
            toUSB_send('e');
            toUSB_send('\r');
            toUSB_send('\n');
        } else if (c=='f')
        {
            // fill test page with stuff
            toUSB_send('f');
            toUSB_send('i');
            AT45_initfillbuffer(AT45_WRITE_BUFFER1);
            int i;
            for (i=0;i<512;i++) {
                c = AT45_datatobuffer(i & 0xFF);
            }
            AT45_endfillbuffer();
            AT45_progbuffer(AT45_PROG_BUFFER1,TESTPAGE);
            toUSB_send('l');
            toUSB_send('l');
            toUSB_send('e');
            toUSB_send('d');
            toUSB_send('\r');
            toUSB_send('\n');
        } else if (c=='p')
        {
            // playback data from test page
            AT45_initread(TESTPAGE);
            int i;
            for (i=0;i<64;i++) {
                int j;
                for (j=0;j<8;j++) {
                    toUSB_sendhex8(AT45_dataread());
                    toUSB_send(' ');
                }
                toUSB_send('\r');
                toUSB_send('\n');
            }
            AT45_endread();
        }
            
    }
    _delay_ms(1);
  }  
}