#include "Timers.h"

/* aqui usamos o timer1 (16-bit) para gerar o SI no pino 9 (OC1A) */ 

void cfgTimerSI(int tINT){ 
    TCCR1A = (1 << COM1A1); // Clear OC1A/OC1B on compare match when up-counting. Set  
                            // OC1A/OC1B on compare match when down counting 
    TCCR1B = (1 << WGM13); // modo 8 da tabela 15-5 

    int TempoTotal = tINT + 3; // esse 3ms vem de dos 18 ciclos de clock que precedem o tempo de integracao  
    ICR1 = uint16_t((TempoTotal / 0.008) + 1); // definindo o valor de topo com base em tINT 

    TCCR1B &= ~(1 << CS12); // Set prescaler to 64 
    TCCR1B |= (1 << CS11); 
    TCCR1B |= (1 << CS10); 

    OCR1A = 3; // periodo de high de 24us 

    TIMSK1 = (1 << TOIE1); // habilita a interrup p/ ativar CLK 
} 

/* aqui usamos o timer0 para gerar o CLK no pino 6 (OC0B)*/ 

void cfgTimerCLK(){ 
    TCCR0A = (1 << COM0B0) | (1 << WGM01); // modo CTC toggle 

    OCR0B = 50; //  <- ajustar esse valor para calibrar a freq de CLK 
    OCR0A = 150; // idem, valor de comparacao de 8-bit 
    
    TCNT0 = 49; // reset timer0 

    TIMSK0 = (1 << OCIE0A);
} 