#include "ADC.h"

void cfgADC()
{
    ADMUX = (1 << REFS0); // Channel sel, right-adj
    ADCSRA = _BV(ADEN) |  // ADC enable
             _BV(ADSC) |  // ADC start
             _BV(ADATE) | // Auto trigger
             _BV(ADIE) |  // Interrupt enable
             0x07;        // prescale de 128 -> ADC de 9600Hz
    ADCSRB = _BV(ADTS2) |
             _BV(ADTS0); // Timer/Counter1 Compare Match B, auto-trigger acionado pelo timer1
    DIDR0 = _BV(0);      // Turn off digital input for ADC pin, otimizacao da conversao apenas
}
