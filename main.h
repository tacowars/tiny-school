/*
 * main.h
 *
 *  Created on: Jul 22, 2012
 *      Author: patrick
 */

#ifndef MAIN_H_
#define MAIN_H_

char temp1[18];
void dbg_putstring(char[]);
void chipTempRaw(void);
int chipTemp(int);
uint8_t i2cReadFromRegister(uint8_t);
void i2cWriteToRegister(uint8_t, uint8_t);

#endif /* MAIN_H_ */
