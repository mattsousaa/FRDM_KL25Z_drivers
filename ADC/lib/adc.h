/*
 * adc.h
 *
 *  Created on: 11 de mar de 2019
 *      Author: Mateus Sousa
 */

#ifndef ADC_H_
#define ADC_H_

#include "MKL25Z4.h"

#define set_bit(y,bit) (y |= (1<<bit))
#define clr_bit(y,bit) (y &=~ (1<<bit))
#define cpl_bit(y,bit) (y ^= (1<<bit))
#define tst_bit(y,bit) (y & (1<<bit))

#define ADC_0	0	//  PTE20
#define ADC_1	4	//  PTE21
#define ADC_2	3	//  PTE22
#define ADC_3	7	//  PTE23
#define ADC_4	8	//  PTB0
#define ADC_5	9	//  PTB1
#define ADC_6	12	//  PTB2
#define ADC_7	13	//  PTB3
#define ADC_8	14	//  PTC0
#define ADC_9	15	//  PTC1
#define ADC_10  11	//  PTC2
#define ADC_11  5	//  PTD1   LED AZUL FRDM-KL25Z
#define ADC_12  6	//  PTD5
#define ADC_13  7	//  PTD6

typedef enum bit_resolution_t {
	_8BIT = 0,
	_10BIT,
	_12BIT,
	_16BIT
} bit_resolution_t;

class Adc {

private:
	uint16_t adc;
	uint8_t res;

public:
	Adc(uint16_t adc, bit_resolution_t res);
	void adcInit();
	uint16_t adcRead();
};


#endif /* ADC_H_ */
