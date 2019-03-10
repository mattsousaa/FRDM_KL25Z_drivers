/*
 * main.c
 *
 *  Created on: 8 de mar de 2019
 *      Author: Mateus Sousa
 */

#include "pwm.h"
#include "MKL25Z4.h"
//#include "system_MKL25Z4.h"

#define TPM_MODULE 3275
#define DUTY_MIN 165
#define DUTY_MAX 999

uint16_t i = 0;
uint16_t x = 0;



int main(void){

	x = DUTY_MIN;

	Pwm led(TPM2, GPIOB, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM, CHANNEL1);

	/* Initializes TPM */
	led.pwmInit();
	/* Initializes I / O with the PWM signal */
	led.pwmChInit(19, TPM_PWM_H);
	// Set value Duty Cycle
	led.pwmCnV(x);

	while(1){

		for(i=0;i<10000;i++);
		// Set valor Duty Cycle
		led.pwmCnV(x);
		x++;
	}

	return 0;
}
