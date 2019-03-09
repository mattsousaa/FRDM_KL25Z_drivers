/*
 * gpio.h
 *
 *  Created on: 5 de mar de 2019
 *      Author: Mateus Sousa
 */

#include "gpio.h"

Gpio::Gpio(GPIO_Type *gpio, uint8_t pin){
	this->gpio = gpio;
	this->pin = pin;
}

void Gpio::setClock(){

	if(this->gpio == GPIOA)  	set_bit(SIM -> SCGC5, 9); /* Habilita o clock gate no gpioA */

	else if(this->gpio == GPIOB)  	set_bit(SIM -> SCGC5, 10); /* Habilita o clock gate no gpioB */

	else if(this->gpio == GPIOC)	set_bit(SIM -> SCGC5, 11); /* Habilita o clock gate no gpioC */

	else if(this->gpio == GPIOD)	set_bit(SIM -> SCGC5, 12); /* Habilita o clock gate no gpioD */

	else if(this->gpio == GPIOE)	set_bit(SIM -> SCGC5, 13); /* Habilita o clock gate no gpioE */

}

void Gpio::setDirection(gpio_direction_t dir){

	if(this->gpio == GPIOA){
		set_bit(PORTA->PCR[this->pin], 8); /* Configura o pino como GPIO */
		if(dir == INPUT) /* INPUT */
			clr_bit(this->gpio->PDDR, this->pin);
		else /* OUTPUT */
			set_bit(this->gpio->PDDR, this->pin);
	}

	else if(this->gpio == GPIOB){
		set_bit(PORTB->PCR[this->pin], 8); /* Configura o pino como GPIO */
		if(dir == INPUT) /* INPUT */
			clr_bit(this->gpio->PDDR, this->pin);
		else /* OUTPUT */
			set_bit(this->gpio->PDDR, this->pin);
	}

	else if(this->gpio == GPIOC){
		set_bit(PORTC->PCR[this->pin], 8); /* Configura o pino como GPIO */
		if(dir == INPUT) /* INPUT */
			clr_bit(this->gpio->PDDR, this->pin);
		else /* OUTPUT */
			set_bit(this->gpio->PDDR, this->pin);
	}

	else if(this->gpio == GPIOD){
		set_bit(PORTD->PCR[this->pin], 8); /* Configura o pino como GPIO */
		if(dir == INPUT) /* INPUT */
			clr_bit(this->gpio->PDDR, this->pin);
		else /* OUTPUT */
			set_bit(this->gpio->PDDR, this->pin);
	}

	else if(this->gpio == GPIOE){
		set_bit(PORTE->PCR[this->pin], 8); /* Configura o pino como GPIO */
		if(dir == INPUT) /* INPUT */
			clr_bit(this->gpio->PDDR, this->pin);
		else /* OUTPUT */
			set_bit(this->gpio->PDDR, this->pin);
	}

}

void Gpio::setValue(gpio_value_t value){

	if(this->gpio == GPIOA){
		if(value == HIGH){ /* HIGH */
			this->gpio->PCOR = 1<<(this->pin);
			this->gpio->PCOR = 0;
		} else{ /* LOW */
			this->gpio->PSOR = 1<<(this->pin);
			this->gpio->PSOR = 0;
		}
	}

	else if(this->gpio == GPIOB){
		if(value == HIGH){ /* HIGH */
			this->gpio->PCOR = 1<<(this->pin);
			this->gpio->PCOR = 0;
		} else{ /* LOW */
			this->gpio->PSOR = 1<<(this->pin);
			this->gpio->PSOR = 0;
		}
	}

	else if(this->gpio == GPIOC){
		if(value == HIGH){ /* HIGH */
			this->gpio->PCOR = 1<<(this->pin);
			this->gpio->PCOR = 0;
		} else{ /* LOW */
			this->gpio->PSOR = 1<<(this->pin);
			this->gpio->PSOR = 0;
		}
	}

	else if(this->gpio == GPIOD){
		if(value == HIGH){ /* HIGH */
			this->gpio->PCOR = 1<<(this->pin);
			this->gpio->PCOR = 0;
		} else{ /* LOW */
			this->gpio->PSOR = 1<<(this->pin);
			this->gpio->PSOR = 0;

		}
	}

	else if(this->gpio == GPIOE){
		if(value == HIGH){ /* HIGH */
			this->gpio->PCOR = 1<<(this->pin);
			this->gpio->PCOR = 0;
		} else{ /* LOW */
			this->gpio->PSOR = 1<<(this->pin);
			this->gpio->PSOR = 0;
		}
	}
}


void Gpio::setPullUp(){

	if(this->gpio == GPIOA){
		set_bit(PORTA->PCR[this->pin], 1); /* Pull Enable */
		set_bit(PORTA->PCR[this->pin], 0); /* Pull Up */
	}

	else if(this->gpio == GPIOB){
		set_bit(PORTB->PCR[this->pin], 1); /* Pull Enable */
		set_bit(PORTB->PCR[this->pin], 0); /* Pull Up */
	}

	else if(this->gpio == GPIOC){
		set_bit(PORTC->PCR[this->pin], 1); /* Pull Enable */
		set_bit(PORTC->PCR[this->pin], 0); /* Pull Up */
	}

	else if(this->gpio == GPIOD){
		set_bit(PORTD->PCR[this->pin], 1); /* Pull Enable */
		set_bit(PORTD->PCR[this->pin], 0); /* Pull Up */
	}

	else if(this->gpio == GPIOE){
		set_bit(PORTE->PCR[this->pin], 1); /* Pull Enable */
		set_bit(PORTE->PCR[this->pin], 0); /* Pull Up */
	}
}


uint8_t Gpio::gpioRead(){

	if(this->gpio == GPIOA)  		return (tst_bit(this->gpio->PDIR, this->pin));

	else if(this->gpio == GPIOB)  	return (tst_bit(this->gpio->PDIR, this->pin));

	else if(this->gpio == GPIOC)	return (tst_bit(this->gpio->PDIR, this->pin));

	else if(this->gpio == GPIOD)	return (tst_bit(this->gpio->PDIR, this->pin));

	else if(this->gpio == GPIOE)	return (tst_bit(this->gpio->PDIR, this->pin));

}
