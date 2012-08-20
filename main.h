/*
 * main.h
 *
 *  Created on: Jul 22, 2012
 */

#ifndef MAIN_H_
#define MAIN_H_

#define I2C_SLAVE_ADDR  0x2
#define LED PB3

void chipTempRaw(void);
void potRead(void);
int chipTemp(int);
uint8_t i2cReadFromRegister(uint8_t);
void i2cWriteToRegister(uint8_t, uint8_t);

#endif /* MAIN_H_ */
