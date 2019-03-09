/*
 * gpio.h
 *
 *  Created on: 5 de mar de 2019
 *      Author: Mateus Sousa
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "MKL25Z4.h"

#define set_bit(y,bit) (y |= (1<<bit))
#define clr_bit(y,bit) (y &=~ (1<<bit))
#define cpl_bit(y,bit) (y ^= (1<<bit))
#define tst_bit(y,bit) (y & (1<<bit))

typedef enum gpio_direction_t {
	INPUT = 0,
	OUTPUT
} gpio_direction_t;

typedef enum gpio_value_t {
	LOW = 0,
	HIGH

} gpio_value_t;

class Gpio {

private:

	GPIO_Type *gpio;
	uint8_t pin;

public:
	Gpio(GPIO_Type *gpio, uint8_t pin);
	void setClock();
	void setDirection(gpio_direction_t dir);
	void setValue(gpio_value_t value);
	void setPullUp();
	uint8_t gpioRead();
};

#endif /* GPIO_H_ */
