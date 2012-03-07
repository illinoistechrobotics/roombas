
#define SELECT_FLASH PORTB &= ~(1<<PB0)
#define DESELECT_FLASH PORTB |= (1<<PB0)
#define RESET_FLASH PORTC &= ~(1<<PC6)
#define RESET_FLASH_OFF PORTC |= (1<<PC6)

#define AT45_WRITE_BUFFER1 0x84
#define AT45_WRITE_BUFFER2 0x87
#define AT45_PROG_BUFFER1 0x88
#define AT45_PROG_BUFFER2 0x89
#define AT45_PROGERASE_BUFFER1 0x83
#define AT45_PROGERASE_BUFFER1 0x86

#define nop() asm("nop")

#define TESTPAGE 0x0f01

#ifndef _at45db_h__
#define _at45db_h__

#include <avr/io.h>

#ifdef __cplusplus
extern "C"{
#endif

void AT45_init(void);

uint8_t AT45_datatobuffer(uint8_t ) ;

uint8_t AT45_dataread(void) ;

void AT45_readdevdata(void);

uint8_t AT45_readstatus(void) ;

void AT45_initsectorerase(uint8_t ) ;

void AT45_pageerase(uint16_t ) ;

void AT45_initfillbuffer(uint8_t ) ;

void AT45_endfillbuffer(void) ;

void AT45_progbuffer(uint8_t , uint16_t ) ;

void AT45_initread(uint16_t ) ;

void AT45_endread(void) ;

void AT45_reset(void) ;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
