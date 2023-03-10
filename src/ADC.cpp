#include "ADC.h"

void cfgADC(){ 
ADMUX = (1 << REFS0); // Channel sel - referencia de 5V, right-adj 
// ADCSRA =    _BV(ADEN) | // ADC enable 
//             _BV(ADATE) | // Auto trigger 
//             //_BV(ADIE) | // Interrupt enable no fim de cada conversão 
//             0x6; // prescale de 128 
// ADCSRB = _BV(ADTS1) | _BV(ADTS0); // Timer/Counter0 Compare Match A, auto-trigger acionado pela subida do CLK 
DIDR0 = _BV(0); // Turn off digital input for ADC pin, otimizacao da conversao apenas 
} 
