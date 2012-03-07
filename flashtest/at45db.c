/* library for accessing AT45DB161D flash on Ardupilot

 */
 
#include <util/delay.h>

#include "spi.h"
#include "at45db.h"

void AT45_init(void) {
  DDRB |= (1<<PB0); // chip select for Flash
  DDRC |= (1<<PC6); // reset for Flash
  // make sure Flash is unselected and setup spi
  DESELECT_FLASH;
  setup_spi(SPI_MODE_0, SPI_MSB, SPI_NO_INTERRUPT, SPI_MSTR_CLK16);
  AT45_reset();
}

uint8_t AT45_datatobuffer(uint8_t byte) {
  return send_spi(byte);
}

uint8_t AT45_dataread(void) {
  return send_spi(0xFF);
}

void AT45_readdevdata(void)
{
  SELECT_FLASH;
  
  uint8_t one, two, three, four;
  one = send_spi(0x9F); // dummy store
  one = send_spi(0xFF);
  two = send_spi(0xFF);
  three = send_spi(0xFF);
  four = send_spi(0xFF);
  DESELECT_FLASH;
  
  toUSB_sendhex8(one);
  toUSB_send(' ');
  toUSB_sendhex8(two);
  toUSB_send(' ');
  toUSB_sendhex8(three);
  toUSB_send(' ');
  toUSB_sendhex8(four);
  toUSB_send('\r');
  toUSB_send('\n');
}

uint8_t AT45_readstatus(void) {
  uint8_t byte;
  SELECT_FLASH;

  byte = send_spi(0xD7);  // dummy
  byte = send_spi(0xFF);
  DESELECT_FLASH;
  return byte;
}

void AT45_initsectorerase(uint8_t sector) {
  uint8_t byte;
  SELECT_FLASH;
  byte = send_spi(0x7C);
  // 528-byte mode, 2 bits DC, 4 bits PA11:PA8, 18 DC
  byte = send_spi((sector << 2));
  byte = send_spi(0xFF);
  byte = send_spi(0xFF);
  DESELECT_FLASH;
}

void AT45_pageerase(uint16_t pageaddress) {
  uint8_t byte;
  SELECT_FLASH;
  byte = send_spi(0x81);
  byte = send_spi((pageaddress >> 6) & 0xFF);
  byte = send_spi((pageaddress << 2) & 0xFF);
  byte = send_spi(0xFF);
  DESELECT_FLASH;
}

void AT45_initfillbuffer(uint8_t opcode) {
  uint8_t byte;
  SELECT_FLASH;
  byte = send_spi(opcode);
  byte = send_spi(0x00);
  byte = send_spi(0x00);
  byte = send_spi(0x00);    // start at address 0
}

void AT45_endfillbuffer(void) {
  DESELECT_FLASH;
  nop();            // min CS high time is 50ns
}

void AT45_progbuffer(uint8_t opcode, uint16_t pageaddress) {
  uint8_t byte;
  SELECT_FLASH;
  byte = send_spi(opcode);
  byte = send_spi((pageaddress >> 6) & 0xFF);
  byte = send_spi((pageaddress << 2) & 0xFF);
  byte = send_spi(0xFF);
  DESELECT_FLASH;
  nop();
}

void AT45_initread(uint16_t pageaddress) {
  uint8_t byte;
  SELECT_FLASH;
  byte = send_spi(0x03);    // continuous array read, low freq (<33MHz)
  //byte = send_spi(0x0B);    // continuous array read
  byte = send_spi((pageaddress >> 6) & 0xFF);
  byte = send_spi((pageaddress << 2) & 0xFF);
  byte = send_spi(0x00);
  //byte = send_spi(0x00);
}

void AT45_endread(void) {
  DESELECT_FLASH;
  nop();
}

void AT45_reset(void) {
  RESET_FLASH;
  _delay_ms(1);
  RESET_FLASH_OFF;
}
