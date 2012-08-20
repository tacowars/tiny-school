/*
 * main.c - attiny85 school
 *
 *  Created on: Jul 12, 2012
 */

//#define F_CPU 16000000UL  // 16 MHz
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include "libs/usiTwiSlave.h"
#include "libs/trace.h"
#include "main.h"
char temp1[18];
char writemsg[] = "-- write callback fired --";


int main(void)
{
	char bootmsg[] = "-- Tiny85 Boot --";

	DDRB  |= 0x00; // set PORTB to all inputs
	dbg_tx_init();
	dbg_putstring(bootmsg);
	DDRB |= (1 << LED); // set LED as output

	usiTwiSlaveInit(I2C_SLAVE_ADDR, i2cReadFromRegister, i2cWriteToRegister);
	sei(); // Enables interrupts by setting the global interrupt mask
	while(1) {

	}
}

// A callback triggered when the i2c master attempts to read from a register.
uint8_t i2cReadFromRegister(uint8_t reg)
{
	dbg_putstring(itoa(reg, temp1, 10));
	switch (reg)
	{
		case 255: 			// no register set
			return 0xF0;
		case 1:
			potRead();
			return ADCL;
		case 2:
			return ADCH;
		case 3:
			PORTB ^= (1 << LED); //LED TOGGLE
			return 3;
		case 4:
			chipTempRaw();
			return ADCL;
		case 5:
			return ADCH;
		default:
			return 0;
	}
}

// A callback triggered when the i2c master attempts to write to a register.
void i2cWriteToRegister(uint8_t reg, uint8_t value)
{
	dbg_putstring(writemsg);
}


void chipTempRaw(void) {
  while (( ADCSRA & _BV( ADSC )));                   // Wait for any ongoing conversion to complete
  //
  ADMUX = 0x8F; // 10001111 - MUX = 1111, REFS = 010, ADLAR = default for internal temp sensor
  // or _BV(REFS1) | ~(_BV(REFS0)) | ~(_BV( ADLAR)) | ~(_BV(REFS2)) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0) ;
  _delay_ms(10);									 // Some time to settle voltage REF change
  ADCSRA &= ~(_BV( ADATE ) | _BV( ADIE ));			 // Clear auto trigger and interrupt enable
  ADCSRA |= 1 << ADPS2;							   	 // Set the prescaler for 16x for 8Mhz
  ADCSRA |= _BV( ADEN ) | _BV( ADSC );               // Enable AD and start conversion
  while (( ADCSRA & _BV( ADSC )));                   // Wait until conversion is finished
}

void potRead(void) {
  while (( ADCSRA & _BV( ADSC )));                   // Wait for any ongoing conversion to complete
  ADMUX &= _BV( REFS2 );  						     // ref voltage to Vcc
  ADMUX = _BV(MUX1);   								 // Set mux to PB4/ADC2
  _delay_ms(10);									 // Some time to settle voltage REF change
  ADCSRA &= ~(_BV( ADATE ) | _BV( ADIE ));			 // Clear auto trigger and interrupt enable
  ADCSRA |= 1 << ADPS2;							   	// Set the prescaler for 16x for 8Mhz
  ADCSRA |= _BV( ADEN ) | _BV( ADSC );               // Enable AD and start conversion
  while (( ADCSRA & _BV( ADSC )));                   // Wait until conversion is finished
  // ( ADCL | ( ADCH << 8 )) = ADCW
}
