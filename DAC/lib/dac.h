/*
 * dac.h
 *
 *  Created on: 13 de mar de 2019
 *      Author: Mateus Sousa
 */


#include <MKL25Z4.h>

#ifndef DAC_H
#define DAC_H

/* Macros for Bitwise */
#define set_bit(y,bit) (y |= (1<<bit))
#define clr_bit(y,bit) (y &=~ (1<<bit))
#define cpl_bit(y,bit) (y ^= (1<<bit))
#define tst_bit(y,bit) (y & (1<<bit))

class Dac {

public:
	Dac();
	void dacInit();
	void dacWrite(uint16_t value);
};

#endif
