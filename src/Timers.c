#include "Timers.h"

/* aqui usamos o timer1 (16-bit) para gerar o SI no pino 9 (OC1A) */
void cfgTimerSI(int tINT)
{
    TCCR1A = (1 << COM1A0); // modo CTC toggle
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS12); // Set prescaler to 256, T = 16us
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);

    TCCR1C = (1 << FOC1A);  // forca o valor logico no pino 9
    
    OCR1A = 6250;           // tempo maximo entre pulsos SI (100ms/16us)
                            // ToDo: alterar esse valor de acordo com tINT

    TCNT1 = 0;              // reseta timer1
    TIMSK1 = (1 << OCIE1A); // habilita a interrup
}

/* aqui usamos o timer2 para gerar o CLK no pino 3 (OC2B)
o compare interrupt fara com que o ADC comece uma nova conversao*/
void cfgTimerCLK()
{
    TCCR2A = (1 << COM2A0) | (1 << COM2B0) | (1 << WGM21); // modo CTC toggle

    TCCR2B = 1 << FOC2B; // forca o valor logico no pino de saida 3

    // parte de calibracao do CLK, os valores atuais setam um prescale de 8
    TCCR2B &= ~(1 << CS12);
    TCCR2B |= (1 << CS11);
    TCCR2B &= ~(1 << CS10);
    OCR2B = 128; // 128 -> 7.375kHz? <- ajustar esse valor para calibrar a freq de CLK
    OCR2A = 128; // idem, valor de comparacao de 8-bit

    TCNT2 = 0; // reset timer2

    TIMSK2 = (1 << OCIE2B); // habilita a interrup. para a borda do CLK dar trigger no ADC
}