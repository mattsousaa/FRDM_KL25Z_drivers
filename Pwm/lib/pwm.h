/*
 * pwm.h
 *
 *  Created on: 6 de mar de 2019
 *      Author: Mateus Sousa
 */

#ifndef PWM_H_
#define PWM_H_

#include "MKL25Z4.h"

/* Macros for Bitwise */
#define set_bit(y,bit) (y |= (1<<bit))
#define clr_bit(y,bit) (y &=~ (1<<bit))
#define cpl_bit(y,bit) (y ^= (1<<bit))
#define tst_bit(y,bit) (y & (1<<bit))

/* MSB and LSB for PWM module */
#define TPM_PWM_H 		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK
#define TPM_PWM_L 		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK

/* TPM clock source select */
/* Selects the clock source for the TPM counter clock */
typedef enum clk_src_t {
	TPM_CLK_DIS = 0,	/* Clock disabled */
	TPM_PLLFLL,			/* MCGFLLCLK clock or MCGPLLCLK/2 clock */
	TPM_OSCERCLK,		/* OSCERCLK clock */
	TPM_MCGIRCLK,		/* MCGIRCLK clock */
} clk_src_t;

/* PWM counter clock */
typedef enum clk_count_t {
	TPM_CNT_DIS = 0,	/* Counter is disabled */
	TPM_CLK,			/* counter increments on every LPTPM counter clock */
	TPM_EXT_CLK,		/* counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock */
} clk_count_t;

/* Pre scale Factor Selection */
typedef enum pre_scale_t {
	PS_1 = 0,
	PS_2,
	PS_4,
	PS_8,
	PS_16,
	PS_32,
	PS_64,
	PS_128,
} pre_scale_t;

/* Pre scale Factor Selection */
typedef enum count_mode_t {
	EDGE_PWM = 0,
	CENTER_PWM,
} count_mode_t;

/* Channel selection */
typedef enum channel_selection_t {
	CHANNEL0 = 0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
} channel_selection_t;

class Pwm {
private:
	TPM_Type *tpm;
	GPIO_Type *gpio;
	clk_src_t clk;
	clk_count_t clock_mode;
	pre_scale_t ps;
	count_mode_t ct_mode;
	uint16_t module;
	uint16_t channel;

public:
	Pwm(TPM_Type *tpm, GPIO_Type *gpio, clk_src_t clk, uint16_t module, clk_count_t clock_mode, pre_scale_t ps, count_mode_t ct_mode,
		channel_selection_t channel);
	bool pwmInit();
	bool pwm_tpm_Ch_Init(uint8_t pin, uint8_t mode);
	void pwm_tpm_CnV(uint16_t value);
};

#endif /* PWM_H_ */
