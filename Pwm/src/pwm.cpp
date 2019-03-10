/*
 * pwm.h
 *
 *  Created on: 6 de mar de 2019
 *      Author: Mateus Sousa
 */

#include <stdio.h>
#include "pwm.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*
 * f_pwm = PWM signal frequency
 * f_core = Frequency assigned to the peripheral by the SIM_SOPT2 register
 * TPMxMOD = Value assigned to TPMxMOD
 * Prescale = Prescale Factor Selection
 *
 * f_pwm = (f_core/TPMxMOD)/prescale
 *
 * TPMxMOD = (f_core*(1/prescale))/f_pwm
 *
 * Example of application
 *
 * Desired signal frequency - 50 Hz
 * Clock source used - MCGFLLCLK with clock 20971520U
 * Prescale - 128
 *
 * TPMxMOD = (20971520*(1/128))/50 = 3276
 *
 * 50 Hz signal has 20ms period
 * Minimum duty cycle of 1ms - 3276/20 = 163
 * Maximum duty cycle of 2ms - 327
 *
 * */

Pwm::Pwm(TPM_Type *tpm, GPIO_Type *gpio, clk_src_t clk, uint16_t module, clk_count_t clock_mode,
		pre_scale_t ps, count_mode_t ct_mode, channel_selection_t channel){
	this->tpm = tpm;
	this->gpio = gpio;
	this->clk = clk;
	this->module = module;
	this->clock_mode = clock_mode;
	this->ps = ps;
	this->ct_mode = ct_mode;
	this->channel = channel;
}

bool Pwm::pwmInit(){

	if(this->tpm == TPM0){
		SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
		this->tpm->MOD = this->module;
		this->tpm->SC |= TPM_SC_CMOD(this->clock_mode) | TPM_SC_PS(this->ps);
	} else if(this->tpm == TPM1){
		SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
		this->tpm->MOD = this->module;
		this->tpm->SC |= TPM_SC_CMOD(this->clock_mode) | TPM_SC_PS(this->ps);
	} else if(this->tpm == TPM2){
		SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
		this->tpm->MOD = this->module;
		this->tpm->SC |= TPM_SC_CMOD(this->clock_mode) | TPM_SC_PS(this->ps);
	} else{
		return false;
	}

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(this->clk);

	if(this->ct_mode == CENTER_PWM){

		if(this->tpm == TPM0)
			this->tpm->SC |= TPM_SC_CPWMS_MASK;
		else if(this->tpm == TPM1)
			this->tpm->SC |= TPM_SC_CPWMS_MASK;
		else if(this->tpm == TPM2)
			this->tpm->SC |= TPM_SC_CPWMS_MASK;
		}

	else if(this->ct_mode == EDGE_PWM){

		if(this->tpm == TPM0)
			this->tpm->SC &= ~TPM_SC_CPWMS_MASK;
		else if(this->tpm == TPM1)
			this->tpm->SC &= ~TPM_SC_CPWMS_MASK;
		else if(this->tpm == TPM2)
			this->tpm->SC &= ~TPM_SC_CPWMS_MASK;
	}

	else {
		return false;
	}

	return true;

}

bool Pwm::pwmChInit(uint8_t pin, uint8_t mode){

	if(this->tpm == TPM0){
	/*
	* PTA3 - CH0
	* PTA4 - CH1
	* PTA5 - CH2
	* PTA0 - CH5
	*/
		if(this->gpio == GPIOA){
			if((this->channel <= 2) || (this->channel == 5)){
				if((pin >= 3) || (pin <= 5)){
					SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORTA->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		}

		/*
		 * PTC1 - CH0
		 * PTC2 - CH1
		 * PTC3 - CH2
		 * PTC4 - CH3
		 * PTC8 - CH4
		 * PTC9 - CH5
		 *
		 * */

		else if(this->gpio == GPIOC){
			if(this->channel <= 5){
				if((pin >= 1 || pin <= 4) || (pin == 8) || (pin == 9)){
					SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
					PORTC->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		}

		/*
		 * PTD0 - CH0
		 * PTD1 - CH1
		 * PTD2 - CH2
		 * PTD3 - CH3
		 * PTD4 - CH4
		 * PTD5 - CH5
		 *
		 * */

		else if(this->gpio == GPIOD){
			if(this->channel <= 5){
				if(pin <= 5){
					SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
					SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
					PORTD->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		}

		/*
		 * PTE24 - CH0
		 * PTE25 - CH1
		 * PTE29 - CH2
		 * PTE30 - CH3
		 * PTE31 - CH4
		 *
		 * */

		else if(this->gpio == GPIOE){
			if(this->channel<=4){
				if((pin >= 24 || pin <= 25) || (pin >= 29 || pin <= 31)){
					SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORTE->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		} else return false;
	}

	else if(this->tpm == TPM1){
		if(this->channel <= 1){
			/*
			 * PTA12 - CH0
			 * PTA13 - CH1
			 * */
			if(this->gpio == GPIOA){
				if(pin >= 12 || pin <= 13){
					SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORTA->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			}

			/*
			 * PTB0 - CH0
			 * PTB1 - CH1
			 * */

			else if(this->gpio == GPIOB){
				if(pin <= 1){
					SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORTB->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			}

			/*
			 * PTE20 - CH0
			 * PTE21 - CH1
			 * */

			else if(this->gpio == GPIOE){
				if(pin >= 20 || pin <= 21){
					SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORTE->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		} else return false;
	}

	else if(this->tpm == TPM2){
		if(this->channel <= 1){
			/*
			 * PTA1 - CH0
			 * PTA2 - CH1
			 * */
			if(this->gpio == GPIOA){
				if(pin >= 1 || pin <= 2){
					SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORTA->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			}

			/*
			 * PTB2 - CH0
			 * PTB3 - CH1
			 * PTB18 - CH0
			 * PTB19 - CH1
			 *
			 * */

			else if(this->gpio == GPIOB){
				if((pin >= 2||pin <= 3) || (pin >= 18||pin < 19)){
					SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORTB->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			}

			/*
			 * PTE22 - CH0
			 * PTE23 - CH1
			 *
			 * */

			else if(this->gpio == GPIOE){
				if(pin >= 22 || pin <= 23){
					SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORTE->PCR[pin] = PORT_PCR_MUX(3);
				} else return false;
			} else return false;
		} else return false;
	} else return false;

	if(this->tpm == TPM0)	  this->tpm->CONTROLS[channel].CnSC |= mode;
	else if(this->tpm == TPM1) this->tpm->CONTROLS[channel].CnSC |= mode;
	else if(this->tpm == TPM2) this->tpm->CONTROLS[channel].CnSC |= mode;

	return true;

}

void Pwm::pwmCnV(uint16_t value){

	if(this->tpm == TPM0){
		this->tpm->CONTROLS[this->channel].CnV = value;
	} else if(this->tpm == TPM1){
		this->tpm->CONTROLS[this->channel].CnV = value;
	} else if(this->tpm == TPM2){
		this->tpm->CONTROLS[this->channel].CnV = value;
	}

}
