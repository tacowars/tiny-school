/*
 * main.c - attiny85 school
 *
 *  Created on: Jul 12, 2012
 *      Author: patrick
 */

#define F_CPU 8000000UL  // 8 MHz
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include "libs/usiTwiSlave.h"
#include "libs/dbg_putchar.h"
#include "main.h"

char temp1[18];
char writemsg[] = "-- write callback fired --";

// Somewhere to store the values the master writes to i2c register 2 and 3.
//static volatile uint8_t i2cReg2 = 0;
//static volatile uint8_t i2cReg3 = 0;

int main(void)
{
	char bootmsg[] = "-- Tiny85 Boot --";
//	int rawTemp;
//	char temp1[4];

	DDRB  |= 0x00; // set PORTB to all inputs
	dbg_tx_init();
	dbg_putstring(bootmsg);
	DDRB |= (1 << LED); // set LED as output

	usiTwiSlaveInit(I2C_SLAVE_ADDR, i2cReadFromRegister, i2cWriteToRegister);
	sei(); // Enables interrupts by setting the global interrupt mask
	while(1) {
		//rawTemp = chipTempRaw();
		//dbg_putstring(itoa(rawTemp, temp1, 10));
		//dbg_putstring(itoa(rawTemp -262, temp1, 10));
	}
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
  //dbg_putstring(itoa(ADC, temp1, 10));
  //return ADC;										 //( ADCL | ( ADCH << 8 ));
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
//	switch (reg)
//	{
//		case 2:
//			i2cReg2 = value;
//			break;
//		case 3:
//			i2cReg3 = value;
//			break;
//
//	}
}
void dbg_putstring(char string[])
{
   int i=0;
   while (string[i] != '\0')
   {
      dbg_putchar(string[i]);
      i++;
   }
   dbg_putchar(13); // Newline
   dbg_putchar(10);
}

void chipTempRaw(void) {
  while (( ADCSRA & _BV( ADSC )));                   // Wait for any ongoing conversion to complete
  ADMUX &= ~( _BV( REFS0 )) | ~(_BV( REFS2 ));  //     // ref voltage to 1.1V
  ADMUX = _BV(REFS1) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);   // Set internal 1.1V reference, temperature reading
  _delay_ms(10);									 // Some time to settle voltage REF change
  ADCSRA &= ~(_BV( ADATE ) | _BV( ADIE ));			 // Clear auto trigger and interrupt enable
  ADCSRA |= 1 << ADPS2;							   	// Set the prescaler for 16x for 8Mhz
  ADCSRA |= _BV( ADEN ) | _BV( ADSC );               // Enable AD and start conversion
  while (( ADCSRA & _BV( ADSC )));                   // Wait until conversion is finished
  //dbg_putstring(itoa(ADC, temp1, 10));
  //return ADC;										 //( ADCL | ( ADCH << 8 ));
}

