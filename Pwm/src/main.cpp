/*
 * main.c
 *
 *  Created on: 8 de mar de 2019
 *      Author: Mateus Sousa
 */

#include "pwm.h"
//#include "system_MKL25Z4.h"

#define TPM_MODULE 3276
#define DUTY_MIN 1
#define DUTY_MAX 325

uint16_t i = 0;
uint32_t x = 0;

int main(void){

	x = DUTY_MIN;

	Pwm ledred(TPM2, GPIOB, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM, CHANNEL0);

	/* Initializes TPM */
	ledred.pwmInit();
	/* Initializes I / O with the PWM signal */
	ledred.setMod(18, TPM_PWM_H);
	// Set value Duty Cycle
	ledred.setDuty(x);

	while(1){

		for(i = 0; i < 2000; i++);
		ledred.setDuty(x);
		x++;

		if(x >= TPM_MODULE){
			x = DUTY_MIN;
		}
	}

	return 0;
}
