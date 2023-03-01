#include <Arduino.h>
#include "Timers.h"
#include "ADC.h"
#define SIZE 128  // buffer circular 128 pixels
#define fCLK 9600 // frequencia do ADC
#define SERIAL_TX_BUFFER_SIZE 128

/* armazenamento dos dados, ToDo: tratamento dos dados */
uint16_t amostras[SIZE];
volatile uint16_t amostraIndex = 0;

/* bloco de interrupcoes ------------------------------------------- */
ISR(TIMER1_OVF_vect){ 
TCCR0B = 0x2; // calibra o prescale (ativa o timer0 -> CLK) 
} 

ISR(ADC_vect){ 
    amostras[amostraIndex] = ADC; 
    amostraIndex++; 
    if (amostraIndex > 127) {  
        TCCR0B = 0; // desabilida o timer0 (CLK) 
        amostraIndex = 0; 
    } 
} 

void setup(){ 
    TCCR0B = 0; // desativa o timer 
    pinMode(9, OUTPUT); 
    pinMode(6, OUTPUT); 

    cfgADC(); 
    cfgTimerCLK(); 
    cfgTimerSI(50); 
} 

void loop(){} 
