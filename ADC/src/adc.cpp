#include "adc.h"

Adc::Adc(uint16_t adc, bit_resolution_t res){
	this->adc = adc;
	this->res = res;
}

void Adc::adcInit(){
	set_bit(SIM->SCGC6, 27); /* Habilita o Clock em ADC0 */

	 ADC0->CFG1 |= (ADC_CFG1_MODE(this->res) | /* Resolução da conversão */
	             ADC_CFG1_ADICLK(0) | /* Bus Clock */
	             ADC_CFG1_ADIV(1)); /* Divisor de clock 1/2 */

	//ADC0->CFG1 = 0b00011100; /* Divisor de clock 1/2, Resolucao de 16 bits, Bus Clock */

	ADC0->SC1[0] |= 0b11111; /* Desabilita o modulo */
}

uint16_t Adc::adcRead(){
	ADC0->SC1[0] = this->adc; /* Inicia conversao */
	while(tst_bit(ADC0->SC2, 7)); /* Conversao em progresso */
	while(!tst_bit(ADC0->SC1[0], 7)); /* Conversao nao esta completa */
	return ADC0->R[0];
}
