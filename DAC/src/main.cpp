#include "dac.h"

const uint16_t vetor[29] ={ 403,404,450,500,700,900,1100,1000,900,700,500,409,450,500,1500,
							3000,4095,3000,1200,500,100,0,100,450,500,500,500,550,500 };
uint32_t i = 0;
uint8_t index = 0;

int main(void){

	Dac dac_t;
 
	dac_t.dacInit();

	while(1){
		dac_t.dacWrite(vetor[index++]);
		if(index >= 29)	index = 0;
        for(i = 0; i < 100000; i++);
    }

    return 0;
}
