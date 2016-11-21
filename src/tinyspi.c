#include "tinyspi.h"

void tspi_begin(void) {
    USICR &= ~(_BV(USISIE) | _BV(USIOIE) | _BV(USIWM1));
    USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);
    SPI_DDR_PORT |= _BV(USCK_DD_PIN);   //set the USCK pin as output
    SPI_DDR_PORT |= _BV(DO_DD_PIN);     //set the DO pin as output
    SPI_DDR_PORT &= ~_BV(DI_DD_PIN);    //set the DI pin as input
}

void tspi_setDataMode(uint8_t spiDataMode) {
    if (spiDataMode == SPI_MODE1)
        USICR |= _BV(USICS0);
    else
        USICR &= ~_BV(USICS0);
}

uint8_t tspi_transfer(uint8_t spiData) {
    USIDR = spiData;
    USISR = _BV(USIOIF);                //clear counter and counter overflow interrupt flag
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { //ensure a consistent clock period
        while ( !(USISR & _BV(USIOIF)) ) USICR |= _BV(USITC);
    }
    return USIDR;
}

void tspi_end(void) {
    USICR &= ~(_BV(USIWM1) | _BV(USIWM0));
}
