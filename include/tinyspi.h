#ifndef tinySPI_h
#define tinySPI_h

#include <stdint.h>
#include <avr/io.h>
#include <util/atomic.h>

//USI ports and pins
#if defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
#define SPI_DDR_PORT DDRA
#define USCK_DD_PIN DDA4
#define DO_DD_PIN DDA5
#define DI_DD_PIN DDA6
#elif defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define SPI_DDR_PORT DDRB
#define USCK_DD_PIN DDB2
#define DO_DD_PIN DDB1
#define DI_DD_PIN DDB0
#endif

//SPI data modes
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04

extern void tspi_begin(void);
extern void tspi_setDataMode(uint8_t);
extern uint8_t tspi_transfer(uint8_t);
extern void tspi_end(void);

#endif
