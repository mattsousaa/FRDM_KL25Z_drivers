#include "adc.h"
#include "gpio.h"

uint16_t adc = 0;

int main(void){

	Adc adc_t(ADC_5, _16BIT);
	Gpio ledRed(GPIOB, 18);
	Gpio ledGreen(GPIOB, 19);

	ledRed.setDirection(OUTPUT);
	ledGreen.setDirection(OUTPUT);

	ledRed.setValue(LOW);
	ledGreen.setValue(LOW);

    adc_t.adcInit(); // Inicializa ADC

    while(1){

    	adc = adc_t.adcRead(); // Le ADC ~ PTB1
 
    	if(adc > 10000){
    		ledRed.setValue(HIGH);
    		ledGreen.setValue(LOW);
    	} else{
    		ledGreen.setValue(HIGH);
    		ledRed.setValue(LOW);
    	}
    }
}
