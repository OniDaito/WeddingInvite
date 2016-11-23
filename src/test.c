/**
* @brief A really basic test program 
* @file test.c
* @author Benjamin Blundell <oni@section9.co.uk>
* @date 21/11/2016
*
*/

#include <avr/io.h>
#define F_CPU 120000
#include <util/delay.h>

int main(void) {
    DDRB |= _BV( PB3 );
    while( 1 ) {
        PORTB |=  _BV( PB3 );
        _delay_ms(200);
        PORTB &=~ _BV( PB3 );
        _delay_ms(200);
    }
}
