#include "dac.h"

Dac::Dac(){}

void Dac::dacInit(){
	set_bit(SIM->SCGC6, 31); /* Habilita o Clock em DAC0 */
	DAC0->SR = 0;
	DAC0->C0 = 0x80; /* Habilita o conversor DA */
}

void Dac::dacWrite(uint16_t value){
	if(value < 4096){
		DAC0->DAT->DATL = (uint8_t)(value & 0x00FF);
		DAC0->DAT->DATH = (uint8_t)((value >> 8) & 0x000F);
	}
}
